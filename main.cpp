#include "obse/PluginAPI.h"
#include "obse/CommandTable.h"
#include "obse/GameAPI.h"
#include "obse_common/SafeWrite.h"
#include "obse/ParamInfos.h"
#include "nodes/NiDX9Renderer.h"

#include "Commands_Misc.h"
#include "Commands_HUD.h"
#include "Commands_Shaders.h"
#include "Commands_Textures.h"

#include "OBSEShaderInterface.h"
#include "Rendering.h"
#include "DepthBufferHook.h"
#include "RenderStateManagerHooks.h"
#include "GlobalSettings.h"

#include <stdlib.h>
#include "delayimp.h"

#define EXTRACTARGS paramInfo, arg1, opcodeOffsetPtr, thisObj, arg3, scriptObj, eventList

#define VERSION 2

IDebugLog	gLog("OBGEv2.log");

PluginHandle				g_pluginHandle = kPluginHandle_Invalid;
OBSESerializationInterface	* g_serialization = NULL;


int *PixelShaderVersion = (int *)0x00B42F48;
int *UseHDR = (int *)0x00B43070;
int *UsePS3Shaders = (int *)0x00B42EA5;

#pragma optimize ("",on)

void (*RecreateImageSpaceShaders)(void) = (void(*)(void))0x007BA2F0;

char hexup[17]="0123456789ABCDEF";
char hexlo[17]="0123456789abcdef";

UInt32	HexToUInt32(char *hexstr)
{
	int n;
	UInt32 total=0;

	while (hexstr[0])
	{
		total=total*16;
		for (n=0;n<16;n++)
		{
			if ((hexup[n]==hexstr[0])||(hexlo[n]==hexstr[0]))
				break;
		}
		if (n==16)
		{
			Console_Print("Invalid hex string.");
			return(0);
		}
		total=total+n;
		hexstr++;
	}

	return(total);
}

void _cdecl ReleaseShader(void)
{
	if (OBSEShaderInterface::Singleton)
	{
		OBSEShaderInterface *pSpoofShader = OBSEShaderInterface::GetSingleton();
		pSpoofShader->DeviceRelease();
		delete(pSpoofShader);
		pSpoofShader=NULL;
	}
}

bool Cmd_Alpha2Coverage(COMMAND_ARGS)
{
	*result=0;
	int enable=1;

	if(!ExtractArgs(EXTRACTARGS, &enable)) return true;

	if(enable>0)
		GetD3DDevice()->SetRenderState(D3DRS_POINTSIZE,MAKEFOURCC('A','2','M','1'));
	else
		GetD3DDevice()->SetRenderState(D3DRS_POINTSIZE,MAKEFOURCC('A','2','M','0'));

	return true;
}

bool Cmd_ShowMemoryDump(COMMAND_ARGS)
{
	*result=0;
	int enable=1;

	if(!ExtractArgs(EXTRACTARGS, &enable)) return true;

	if(enable>0)
		OBSEShaderInterface::GetSingleton()->ActivateShader=true;
	else
		OBSEShaderInterface::GetSingleton()->ActivateShader=false;

	return true;
}

bool Cmd_ShowDebugInfo(COMMAND_ARGS)
{
	*result=0;
	int enable=0;

	if(!ExtractArgs(EXTRACTARGS, &enable)) return true;

	if(enable>0)
		OBSEShaderInterface::GetSingleton()->DebugOn=true;
	else
		OBSEShaderInterface::GetSingleton()->DebugOn=false;

	return true;
}

static void SaveCallback(void * reserved)
{
	_MESSAGE("Saving a game.");
	OBSEShaderInterface::GetSingleton()->SaveGame(g_serialization);
}

static void LoadCallback(void * reserved)
{
	_MESSAGE("Loading a game.");
	OBSEShaderInterface::GetSingleton()->LoadGame(g_serialization);
}

static void NewGameCallback(void * reserved)
{
	_MESSAGE("Starting a new game.");
	if(!OBSEShaderInterface::Singleton)
		OBSEShaderInterface::GetSingleton()->ActivateShader=true;
	else
		OBSEShaderInterface::GetSingleton()->NewGame();
}

void MessageHandler(OBSEMessagingInterface::Message* msg)
{
	switch (msg->type)
	{
	case OBSEMessagingInterface::kMessage_ExitGame:
		_MESSAGE("Received ExitGame message.");
		INIList::GetSingleton()->WriteAllToINI();
		ReleaseShader();
		LostDepthBuffer(true,NULL);
		break;
	case OBSEMessagingInterface::kMessage_LoadGame:
		_MESSAGE("Received load game message.");
		break;
	case OBSEMessagingInterface::kMessage_SaveGame:
		_MESSAGE("Received save game message.");
	default:
		_MESSAGE("Ingnoring message.");
		break;
	}
}

static ParamInfo kParams_OneIntOneOptInt[2] =
{
	{	"int", kParamType_Integer, 0 },
	{	"int", kParamType_Integer, 1 },
};

static CommandInfo kAlpha2Coverage =
{
	"Alpha2Coverage",
	"",
	0,
	"1 = on, 0 = off.",
	0,		// doesn't require parent obj
	1,		// has 1 param
	kParams_OneOptionalInt,	// one optional int
	Cmd_Alpha2Coverage
};

static CommandInfo kShowDebugInfo =
{
	"ShowShaderDebugInfo",
	"",
	0,
	"1 = show, 0 - don't show.",
	0,		// doesn't require parent obj
	1,		// has 1 param
	kParams_OneOptionalInt,	// one optional int
	Cmd_ShowDebugInfo
};


static CommandInfo kShowMemoryDump =
{
	"ShowTestShader",
	"",
	0,
	"1 = show, 0 - don't show.",
	0,		// doesn't require parent obj
	1,		// has 1 param
	kParams_OneOptionalInt,	// one optional int
	Cmd_ShowMemoryDump
};


extern "C" {

bool OBSEPlugin_Query(const OBSEInterface * obse, PluginInfo * info)
{

	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "OBGEv2";
	info->version = VERSION;

	// version checks
	if(!obse->isEditor)
	{
		if(obse->obseVersion < OBSE_VERSION_INTEGER)
		{
			_ERROR("OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, 17); // Serialization started in obse 17 I think.
			return false;
		}

		if(obse->oblivionVersion != OBLIVION_VERSION)
		{
			_ERROR("incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}

		g_serialization = (OBSESerializationInterface *)obse->QueryInterface(kInterface_Serialization);
		if(!g_serialization)
		{
			_ERROR("serialization interface not found");
			return false;
		}

		if(g_serialization->version < OBSESerializationInterface::kVersion)
		{
			_ERROR("incorrect serialization version found (got %08X need %08X)", g_serialization->version, OBSESerializationInterface::kVersion);
			return false;
		}

// Delay loading d3dx9_41.dll file so I can check that it exists on the system.
// Set linker options DELAYLOAD:d3dx9_41.dll & DELAY:NOBIND (No binding in case someone
// is using a proxy dll).

		if (FAILED(__HrLoadAllImportsForDll("d3dx9_41.dll"))) 
		{
			_ERROR ( "ERROR - can't find d3dx9_41.dll file. Please update DirectX." );
			return false;
		}

	}
	else
	{
		
	}

	// version checks pass

	return true;
}

bool OBSEPlugin_Load(const OBSEInterface * obse)
{

	g_pluginHandle = obse->GetPluginHandle();

	obse->SetOpcodeBase(0x2100);

	// Shader range 2100 to 21FF

	obse->RegisterCommand(&kCommandInfo_GetAvailableGraphicsMemory);	// 2100
	obse->RegisterCommand(&kCommandInfo_GetScreenWidth);				// 2101
	obse->RegisterCommand(&kCommandInfo_GetScreenHeight);				// 2102
	obse->RegisterCommand(&kCommandInfo_LoadShader);					// 2103
	obse->RegisterCommand(&kCommandInfo_ApplyFullscreenShader);			// 2104
	obse->RegisterCommand(&kCommandInfo_RemoveFullscreenShader);		// 2105
	obse->RegisterCommand(&kCommandInfo_SetShaderInt);					// 2106
	obse->RegisterCommand(&kCommandInfo_SetShaderFloat);				// 2107
	obse->RegisterCommand(&kCommandInfo_SetShaderVector);				// 2108
	obse->RegisterCommand(&kCommandInfo_SetShaderTexture);				// 2109
	obse->RegisterCommand(&kCommandInfo_ForceGraphicsReset);			// 210A
	obse->RegisterCommand(&kCommandInfo_LoadTexture);					// 210B
	obse->RegisterCommand(&kCommandInfo_FreeTexture);					// 210C
	obse->RegisterCommand(&kCommandInfo_CreateHUDElement);				// 210D
	obse->RegisterCommand(&kCommandInfo_SetHUDElementTexture);			// 210E
	obse->RegisterCommand(&kCommandInfo_SetHUDElementColour);			// 210F
	obse->RegisterCommand(&kCommandInfo_SetHUDElementPosition);			// 2110
	obse->RegisterCommand(&kCommandInfo_SetHUDElementScale);			// 2111
	obse->RegisterCommand(&kCommandInfo_SetHUDElementRotation);			// 2112
	obse->RegisterCommand(&kCommandInfo_PurgeManagedTextures);			// 2113
	obse->RegisterCommand(&kCommandInfo_IsShaderEnabled);				// 2114
	
// We don't want to hook the construction set.

	if (!obse->isEditor)
	{
		// Initialise global INI settings.

		INIList::GetSingleton()->ReadAllFromINI();

		if (IsEnabled())
		{
			// register to receive messages from OBSE
			OBSEMessagingInterface* msgIntfc = (OBSEMessagingInterface*)obse->QueryInterface(kInterface_Messaging);
			SetMessaging(msgIntfc,g_pluginHandle);
			msgIntfc->RegisterListener(g_pluginHandle, "OBSE", MessageHandler);

			g_serialization->SetSaveCallback(g_pluginHandle, SaveCallback);
			g_serialization->SetLoadCallback(g_pluginHandle, LoadCallback);
			g_serialization->SetNewGameCallback(g_pluginHandle, NewGameCallback);

			CreateDepthBufferHook();
			//v1_2_416::NiDX9RenderStateEx::HookRenderStateManager();
		}
		else
			g_serialization->SetLoadCallback(g_pluginHandle, LoadCallback);
			// must register callback or game will crash.
	}

	return true;
}

};