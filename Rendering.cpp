#include "Rendering.h"
#include "nodes\NiDX9Renderer.h"

#pragma optimize ("",off)
_declspec(naked) IDirect3DDevice9 *GetD3DDevice(void)
{
	_asm
	{
		mov eax,0x00B3F928
		mov eax,[eax]
		mov eax,[eax+0x280]
		retn
	}
}
#pragma optimize("",on)

IDirect3DDevice9 *GetD3DDeviceNew(void)
{
	v1_2_416::NiDX9Renderer *pRenderer = NULL;

	pRenderer = v1_2_416::GetRenderer();
	//_MESSAGE("Renderer = %x",pRenderer);
	//_MESSAGE("Renderer Debug Info = %s",pRenderer->GetDeviceDebugInfo());

	return(pRenderer->pDirect3DDevice);
}

void D3DClearTest()
{
	GetD3DDevice()->Clear(0,NULL,D3DCLEAR_TARGET,0x00FF0000,0.0,0);
}

void CopyScreen(IDirect3DSurface9 *SourceSurface)
{
	IDirect3DSurface9 *RenderTarget;

	GetD3DDevice()->GetRenderTarget(0,&RenderTarget);	// Adds ref need to release when finished with.
	GetD3DDevice()->StretchRect(SourceSurface,NULL,RenderTarget,NULL,D3DTEXF_POINT);
	RenderTarget->Release();
}