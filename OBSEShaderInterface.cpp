#include "OBSEShaderInterface.h"
#include "nodes/NiDX9Renderer.h"
#include "nodes/NiCamera.h"
#include "Rendering.h"
#include "DepthBufferHook.h"
#include "OBGE fork/Sky.h"
#include "nodes/NiBillboardNode.h"
#include "nodes/NiVector4.h"
#include "ScreenElements.h"
#include "TextureManager.h"
#include "GlobalSettings.h"

#pragma warning(disable : 4996)

static global<bool> UseSave(true,NULL,"Serialization","bSaveData");
static global<bool> UseLoad(true,NULL,"Serialization","bLoadData");
static global<bool> EnableInterOp(false,NULL,"PluginInterOp","bEnableInterOp");
static global<bool> SaveFix(false,NULL,"Shaders","bNoShadersInMenus");
static global<bool> Enabled(true,NULL,"General","bEnabled");

// Uses code from OBGE by Timeslip.

OBSEShaderInterface *OBSEShaderInterface::Singleton = NULL;

// TO DO : Needs tidying.

bool LostDevice(bool stage,void *parameters)
{
	NiTListBase<SpoofShader>::Node *CurrentNode;

	_MESSAGE("Lost device handler:");
	if (OBSEShaderInterface::Singleton)
	{
		CurrentNode=obImageSpaceShaderList->p->ShaderList.start;
		while(CurrentNode)
		{
			if(CurrentNode->data->IsSpoofShader())
			{
				if (stage)
					CurrentNode->data->DeviceLost();
				else
					CurrentNode->data->DeviceReset();
			}
			CurrentNode=CurrentNode->next;
		}
	}

	return true;
}

OBSEShaderInterface	*OBSEShaderInterface::GetSingleton()
{
	if (!Singleton)
	{
		Singleton = new(OBSEShaderInterface);
		
		v1_2_416::GetRenderer()->RegisterLostDeviceCallback(LostDevice,NULL);
		
		// Need to increase the ref count of the spoof shader otherwise the game engine will try to delete it. Of course
		// as I haven't written a destructor it will fail.
		Singleton->RefCount++;	
	
		obImageSpaceShaderList->p->AddShader(Singleton);
	
		Singleton->InitialiseShader();
		Singleton->ActivateShader=true;
		_MESSAGE("Added to list OK.");
	}
	return(Singleton);
}


void OBSEShaderInterface::ShaderCode(IDirect3DDevice9 *D3DDevice,IDirect3DSurface9 *RenderTo, IDirect3DSurface9 *RenderFrom, DeviceInfo *Info)
{

	
	if(Info->AltRenderTarget)
		_MESSAGE("Alt Render target - width = %i, height = %i",Info->Width,Info->Height);
	
	if(Info->AltRenderTarget && (SaveFix.data || (Info->Height==256 && Info->Width==256)))
	{
		D3DDevice->StretchRect(RenderFrom,0,RenderTo,0,D3DTEXF_NONE);
		return;
	}
	
	ShaderManager* ShaderMan=ShaderManager::GetSingleton();
	ShaderMan->UpdateFrameConstants();
	ShaderMan->Render(D3DDevice,RenderTo,RenderFrom);

	HUDManager::GetSingleton()->Render();
/*	
	if(EnableInterOp.data)
	{
		struct INTEROP {
			UInt32		version;
			IDirect3DDevice9 *D3DDevice;
			IDirect3DSurface9 *RenderTo;
			UInt32		width;
			UInt32		height;
			D3DCAPS9	*DeviceCaps;
		} InterOp;
		
		InterOp.version=1;
		InterOp.D3DDevice=D3DDevice;
		InterOp.RenderTo=RenderTo;
		InterOp.width=Info->Width;
		InterOp.height=Info->Height;
		InterOp.DeviceCaps=Info->Caps;

		GetMessaging()->Dispatch(GetHandle(),'REND',(void *)&InterOp,sizeof(InterOp),NULL);
	}
*/

// I'll keep the font stuff in as I might need it later for debugging purposes.

/*
	if (!pFont)
	{
		hr=D3DXCreateFontIndirectA(D3DDevice,&FontDescription,&pFont);
		if (hr!=S_OK || !pFont)
		{
			_MESSAGE("ERROR CREATING FONT");
			return;
		}
	}

	if (!pFont2)
	{
		hr=D3DXCreateFontIndirectA(D3DDevice,&FontDescription2,&pFont2);
		if (hr!=S_OK || !pFont2)
		{
			_MESSAGE("ERROR CREATING FONT");
			return;
		}
	}
*/
	return;
}

void OBSEShaderInterface::DeviceLost()
{
	_MESSAGE("Calling Lost Device");

	if (pFont)
	{
		pFont->OnLostDevice();
	}

	if(pFont2)
	{
		pFont2->OnLostDevice();
	}

	TextureManager::GetSingleton()->DeviceRelease();
	ShaderManager::GetSingleton()->OnLostDevice();
}

void OBSEShaderInterface::DeviceReset()
{
	_MESSAGE("Calling Reset Device");

	if (pFont)
	{
		pFont->OnResetDevice();
	}

	if (pFont2)
	{
		pFont2->OnResetDevice();
	}

	TextureManager::GetSingleton()->InitialiseFrameTextures();
	ShaderManager::GetSingleton()->OnResetDevice();
}

void OBSEShaderInterface::DeviceRelease()
{
	_MESSAGE("Calling Release Device");

	if (pFont)
	{
		while(pFont->Release()){}
		pFont=NULL;
	}
	
	if(pFont2)
	{
		while(pFont2->Release()){}
		pFont2=NULL;
	}

	TextureManager::GetSingleton()->DeviceRelease();
	ShaderManager::GetSingleton()->DeviceRelease();
	//LostDepthBuffer(true,NULL);

	delete(TextureManager::GetSingleton());
	delete(ShaderManager::GetSingleton());

	//delete MemoryDumpString;
}

void OBSEShaderInterface::InitialiseShader(void)
{
	DebugOn=false;

	pFont=NULL;
	pFont2=NULL;

	FontRect.top=10;
	FontRect.bottom=490;
	FontRect.left=10;
	FontRect.right=790;

	FontDescription.Height=-16;
	FontDescription.Width=0;
	FontDescription.Weight=FW_NORMAL;
	FontDescription.MipLevels=1;
	FontDescription.Italic=false;
	FontDescription.CharSet=ANSI_CHARSET;
	FontDescription.OutputPrecision=OUT_DEFAULT_PRECIS;
	FontDescription.Quality=ANTIALIASED_QUALITY;
	FontDescription.PitchAndFamily=FF_DONTCARE|FIXED_PITCH;
	strcpy(FontDescription.FaceName,"Courier New");

	FontDescription2.Height=-16;
	FontDescription2.Width=0;
	FontDescription2.Weight=FW_HEAVY;
	FontDescription2.MipLevels=1;
	FontDescription2.Italic=false;
	FontDescription2.CharSet=ANSI_CHARSET;
	FontDescription2.OutputPrecision=OUT_DEFAULT_PRECIS;
	FontDescription2.Quality=ANTIALIASED_QUALITY;
	FontDescription2.PitchAndFamily=FF_DONTCARE|FIXED_PITCH;
	strcpy(FontDescription2.FaceName,"Courier New");

	FontColor=D3DCOLOR_RGBA(255,255,255,255);
	FontColor2=D3DCOLOR_RGBA(0,0,0,255);

	ShaderManager::GetSingleton()->InitialiseBuffers();
	TextureManager::GetSingleton()->InitialiseFrameTextures();
	ShaderManager::GetSingleton()->LoadShaderList();

	//MemoryDumpString=new TextBuffer(10000);

	return;
}

void OBSEShaderInterface::NewGame()
{
	TextureManager::GetSingleton()->NewGame();
	ShaderManager::GetSingleton()->NewGame();
	ShaderManager::GetSingleton()->LoadShaderList();	
}

void OBSEShaderInterface::LoadGame(OBSESerializationInterface *Interface)
{
	if(IsEnabled())
	{
		NewGame();
		if(UseLoad.data)
		{
			TextureManager::GetSingleton()->LoadGame(Interface);
			ShaderManager::GetSingleton()->LoadGame(Interface);
		}
		else
		{
			_MESSAGE("Loading disabled in INI file.");
		}
	}
}

void OBSEShaderInterface::SaveGame(OBSESerializationInterface *Interface)
{
	if(UseSave.data)
	{
		TextureManager::GetSingleton()->SaveGame(Interface);
		ShaderManager::GetSingleton()->SaveGame(Interface);
	}
	else
	{
		_MESSAGE("Saving disabled in INI file.");
	}
}

void SetMessaging(OBSEMessagingInterface *Interface,PluginHandle Handle)
{
	messanger=Interface;
	handle=Handle;
	return;
}

OBSEMessagingInterface	*GetMessaging(void)
{
	return(messanger);
}

PluginHandle GetHandle(void)
{
	return(handle);
}

bool IsEnabled()
{
	return(Enabled.data);
}