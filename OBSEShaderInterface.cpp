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

#pragma warning(disable : 4996)

// Uses code from OBGE by Timeslip.

OBSEShaderInterface *OBSEShaderInterface::Singleton = NULL;

// TO DO : Needs tidying.

bool LostDevice(bool stage,void *parameters)
{
	NiTListBase<SpoofShader>::Node *CurrentNode;

	_MESSAGE("Lost device callback.");
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

	HRESULT	hr;

	ShaderManager* ShaderMan=ShaderManager::GetSingleton();
	ShaderMan->UpdateFrameConstants();
	ShaderMan->Render(D3DDevice,RenderTo,RenderFrom);

	HUDManager::GetSingleton()->Render();

// I'll keep the font stuff in as I might need it later for debugging purposes.

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

	TextureManager::GetSingleton()->DeviceRelease();
	ShaderManager::GetSingleton()->DeviceRelease();

	delete(TextureManager::GetSingleton());
	delete(ShaderManager::GetSingleton());

	if(pFont2)
	{
		while(pFont2->Release()){}
		pFont2=NULL;
	}

	delete MemoryDumpString;
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

	DumpType=0;

	MemoryAddr=0x00B02000;

	ShaderManager::GetSingleton()->InitialiseBuffers();
	TextureManager::GetSingleton()->InitialiseFrameTextures();
	ShaderManager::GetSingleton()->LoadShaderList();

	MemoryDumpString=new TextBuffer(10000);

	return;
}

void OBSEShaderInterface::NewGame()
{
	TextureManager::GetSingleton()->NewGame();
	ShaderManager::GetSingleton()->NewGame();
	ShaderManager::GetSingleton()->LoadShaderList();	
}