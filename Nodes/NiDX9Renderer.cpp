#pragma once

#include "nodes\NiDX9Renderer.h"

namespace v1_2_416
{
	#pragma optimize ("",off)
	_declspec(naked) NiDX9Renderer *GetRenderer(void)
	{
		_asm
		{
			mov eax,0x00B3F928
			mov eax,[eax]
			retn
		}
	}
	#pragma optimize ("",on)

	void _declspec(naked) *NiDX9Renderer::RegisterLostDeviceCallback(bool function(bool, void *), void *functiondata)
	{
		_asm
		{
			mov eax,0x0040C1B0
			jmp eax
		}
	}

	void _declspec(naked) NiDX9Renderer::SetCameraViewProj(NiCamera *Camera)
	{
		_asm
		{
			mov eax,0x00701970
			jmp eax
		}
	}
}