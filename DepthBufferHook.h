#pragma once

#include "D3D9.h"
#include "Nodes\NiDX9ImplicitDepthStencilBufferData.h"
#include "GlobalSettings.h"

namespace v1_2_416
{
	class NiDX9ImplicitDepthStencilBufferDataEx: public NiDX9ImplicitDepthStencilBufferData
	{
	public:
		NiDX9ImplicitDepthStencilBufferDataEx();
		virtual ~NiDX9ImplicitDepthStencilBufferDataEx();

		bool GetBufferDataHook(IDirect3DDevice9 *D3DDevice);
		bool jGetBufferData(IDirect3DDevice9 *D3DDevice);
	};
}

void static _cdecl DepthBufferHook(IDirect3DDevice9 *Device,UInt32 u2);
UInt32 static _cdecl TextureSanityCheckHook(D3DFORMAT TextureFormat, UInt32 u2);
void CreateDepthBufferHook(void);
IDirect3DTexture9 *GetDepthBufferTexture(void);
bool LostDepthBuffer(bool stage,void *parameters);
bool HasDepth(void);
bool IsRAWZ(void);
