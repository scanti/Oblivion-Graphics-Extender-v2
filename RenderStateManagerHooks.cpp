#include "RenderStateManagerHooks.h"
#include "obse_common/SafeWrite.h"

bool v1_2_416::NiDX9RenderStateEx::DisableFogOverride=false;

#pragma optimize ("",off)
void _declspec(naked) v1_2_416::NiDX9RenderStateEx::SetRenderStateOld(D3DRENDERSTATETYPE state, UInt32 value, BOOL BackUp)
{
	_asm
	{
		mov eax,0x0077B000
		jmp eax
	}
}
#pragma optimize ("",on)

void v1_2_416::NiDX9RenderStateEx::SetRenderStateNew(D3DRENDERSTATETYPE state, UInt32 value, BOOL BackUp)
{
	if(state==D3DRS_FILLMODE)
	{
		//_MESSAGE("Fog override.");
		if(DisableFogOverride)
		{
			value=D3DFILL_WIREFRAME;
		}
	}
	SetRenderStateOld(state,value,BackUp);
}

void v1_2_416::NiDX9RenderStateEx::HookRenderStateManager()
{
// Hook SetFog
	void (v1_2_416::NiDX9RenderStateEx::*temp)(D3DRENDERSTATETYPE, UInt32, BOOL)=&v1_2_416::NiDX9RenderStateEx::SetRenderStateNew;
	UInt32	*temp2=(UInt32 *)&temp;
	_MESSAGE("Hooking set render state.");

	SafeWrite32(0x00A8AA58,*temp2);
}