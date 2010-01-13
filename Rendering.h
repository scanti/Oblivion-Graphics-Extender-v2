#pragma once

#include "D3D9.h"
#include "D3dx9.h"

IDirect3DDevice9 *GetD3DDevice(void);
IDirect3DDevice9 *GetD3DDeviceNew(void);

void D3DClearTest(void);
void CopyScreen(IDirect3DSurface9 *SourceSurface);