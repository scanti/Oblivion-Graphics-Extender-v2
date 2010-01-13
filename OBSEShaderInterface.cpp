#include "OBSEShaderInterface.h"
#include "nodes/NiDX9Renderer.h"
#include "nodes/NiCamera.h"
#include "Rendering.h"
#include "DepthBufferHook.h"
#include "OBGE fork/Sky.h"
#include "nodes/NiBillboardNode.h"
#include "nodes/NiVector4.h"
#include "ScreenElements.h"

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

/*
	if(D3D_ShaderBuffer)
	{
		_MESSAGE("Releasing shader vertex buffer.");
		while(D3D_ShaderBuffer->Release()){}
		D3D_ShaderBuffer=NULL;
	}

	if (Effect)
	{
		Effect->OnLostDevice();
	}
*/

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

	/*
	D3D_sShaderVertex ShaderVertices[] = {
		{-0.5,-0.5,0,1,0,0},
		{-0.5,+5.0,0,1,0,1},
		{+5.0,-0.5,0,1,1,0},
		{+5.0,+5.0,0,1,1,1}
	};

	_MESSAGE("Recreating vertex buffers.");
	GetD3DDevice()->CreateVertexBuffer(4*sizeof(D3D_sShaderVertex),D3DUSAGE_WRITEONLY,MYVERTEXFORMAT,D3DPOOL_DEFAULT,&D3D_ShaderBuffer,0);
	void* VertexPointer;
	ShaderVertices[3].x=ShaderVertices[2].x=(float)(v1_2_416::GetRenderer()->SizeWidth)-.5f;
	ShaderVertices[3].y=ShaderVertices[1].y=(float)(v1_2_416::GetRenderer()->SizeHeight)-.5f;
	D3D_ShaderBuffer->Lock(0,0,&VertexPointer,0);
	CopyMemory(VertexPointer,ShaderVertices,sizeof(ShaderVertices));
	D3D_ShaderBuffer->Unlock();

	_MESSAGE("Recreating screen texture.");
	_MESSAGE("Width = %i, Height = %i",v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight);
	GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&D3D_ShaderTex1,0);
	GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&D3D_ShaderTex2,0);
	GetD3DDevice()->CreateTexture(v1_2_416::GetRenderer()->SizeWidth,v1_2_416::GetRenderer()->SizeHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&D3D_lastframeTex,0);
	
	_MESSAGE("Setting screen surface.");
	D3D_ShaderTex1->GetSurfaceLevel(0,&D3D_ShaderSurf1);
	D3D_ShaderTex2->GetSurfaceLevel(0,&D3D_ShaderSurf2);
	D3D_lastframeTex->GetSurfaceLevel(0,&D3D_lastframeSurf);

	if(Effect)
	{
		Effect->OnResetDevice();
	}

	_MESSAGE("Resetting effects screen texture.");
	Effect->SetTexture("thisframe",D3D_ShaderTex1);
	Effect->SetTexture("lastpass",D3D_ShaderTex2);
	Effect->SetTexture("lastframe",D3D_lastframeTex);

	rcpres[0]=1.0f/(float)v1_2_416::GetRenderer()->SizeWidth;
	rcpres[1]=1.0f/(float)v1_2_416::GetRenderer()->SizeHeight;
	Effect->SetFloatArray("rcpres",(float*)&rcpres,2);

	Effect->SetBool("bHasDepth",HasDepth());
	Effect->SetTexture("Depth",GetDepthBufferTexture());
	*/
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