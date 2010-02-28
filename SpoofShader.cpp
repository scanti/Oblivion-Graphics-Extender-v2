#include "SpoofShader.h"
#include "Rendering.h"
#include "nodes/NiRenderTargetGroup.h"
#include "nodes/NiDX9Renderer.h"

void SpoofShader::Deconstructor(UInt32 u1)
{
	_MESSAGE("Calling Deconstructor");
	// Do nowt
};

NiRTTI *SpoofShader::GetType(void)
{
	//_MESSAGE("Calling GetType");
	return(&SpoofShaderRTTI);
}

UInt32 SpoofShader::Unk_02(void)
{
	_MESSAGE("Calling Unk_02");
	return(0);
}

UInt32 SpoofShader::Unk_03(void)
{
	_MESSAGE("Calling Unk_03");
	return(0);
}

UInt32 SpoofShader::Unk_04(void)
{
	_MESSAGE("Calling Unk_04");
	return(0);
}

UInt32 SpoofShader::Unk_05(void)
{
	_MESSAGE("Calling Unk_05");
	return(0);
}

UInt32 SpoofShader::UpdateInternalVars(UInt32 Unk01)
{
	//_MESSAGE("Calling Unk_06");
	return(0);
}

UInt32 SpoofShader::Unk_07(void)
{
	_MESSAGE("Calling Unk_07");
	return(0x0A);
}

UInt8 SpoofShader::Unk_08(void)
{
	_MESSAGE("Calling Unk_08");
	return(0);
}

void SpoofShader::Unk_09(UInt32 Unk01)
{
	_MESSAGE("Calling Unk_09");
	return;
}

UInt32 SpoofShader::Unk_0A(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7)
{
	_MESSAGE("Calling Unk_0A");
	return(0);
}

UInt32 SpoofShader::Unk_0B(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7)
{
	_MESSAGE("Calling Unk_0B");
	return(0);
}

UInt32 SpoofShader::Unk_0C(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7)
{
	_MESSAGE("Calling Unk_0C");
	return(0);
}

UInt32 SpoofShader::Unk_0D(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7, UInt32 u8)
{
	_MESSAGE("Calling Unk_0D");
	return(0);
}

UInt32 SpoofShader::Unk_0E(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7, UInt32 u8)
{
	_MESSAGE("Calling Unk_0E");
	return(0);
}

UInt32 SpoofShader::Unk_0F(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4)
{
	_MESSAGE("Calling Unk_0F");
	return(0);
}

UInt32 SpoofShader::Unk_10(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7,UInt32 u8)
{
	_MESSAGE("Calling Unk_10");
	return(0);
}

UInt32 SpoofShader::Unk_11(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7)
{
	_MESSAGE("Calling Unk_11");
	return(0);
}

void SpoofShader::Unk_12(void)
{
	_MESSAGE("Calling Unk_12");
	return;
}

void SpoofShader::Unk_13(void)
{
	_MESSAGE("Calling Unk_13");
	return;
}

void SpoofShader::Unk_14(void)
{
	_MESSAGE("Calling Unk_14");
	return;
}

void SpoofShader::Unk_15(UInt32 u1)
{
	_MESSAGE("Calling Unk_15");
	return;
}

void SpoofShader::Unk_16(void)
{
	_MESSAGE("Calling Unk_16");
	return;
}

void SpoofShader::Unk_17(void)
{
	_MESSAGE("Calling Unk_17");
	return;
}

void SpoofShader::Unk_18(void)
{
	_MESSAGE("Calling Unk_18");
	return;
}

void SpoofShader::Unk_19(void)
{
	_MESSAGE("Calling Unk_19");
	return;
}

void SpoofShader::Unk_1A(void)
{
	_MESSAGE("Calling Unk_1A");
	return;
}

void SpoofShader::Unk_1B(void)
{
	_MESSAGE("Calling Unk_1B");
	return;
}

void SpoofShader::Unk_1C(void)
{
	_MESSAGE("Calling Unk_1C");
	return;
}

void SpoofShader::Unk_1D(void)
{
	_MESSAGE("Calling Unk_1D");
	return;
}

UInt8 SpoofShader::Unk_1E(void)
{
	_MESSAGE("Calling Unk_1E");
	return(0);
}

void SpoofShader::Unk_1F(UInt8 value)
{
	_MESSAGE("Calling Unk_1F");
	return;
}

void SpoofShader::Unk_20(void)
{
	_MESSAGE("Calling Unk_20");
	return;
}

bool SpoofShader::Unk_21(void)
{
	_MESSAGE("Calling Unk_21");
	return(false);
}

void SpoofShader::Unk_22(void)
{
	_MESSAGE("Calling Unk_22");
	return;
}

void SpoofShader::Unk_23(void)
{
	_MESSAGE("Calling Unk_23");
	return;
}

void SpoofShader::Unk_24(void)
{
	_MESSAGE("Calling Unk_24");
	return;
}

void SpoofShader::Unk_25(UInt32 u1)
{
	_MESSAGE("Calling Unk_25");
	return;
}

bool SpoofShader::Unk_26(void)
{
	_MESSAGE("Calling Unk_26");
	return(false);
}

void SpoofShader::Unk_27(void)
{
	_MESSAGE("Calling Unk_27");
	return;
}

bool SpoofShader::Unk_28(void)
{
	_MESSAGE("Calling Unk_28");
	return(false);
}

void SpoofShader::Unk_29(UInt32 u1, UInt8 u2)
{
	_MESSAGE("Calling Unk_29");
	return;
}

void SpoofShader::RenderShader(void *ScreenElements, TextureLink *RenderedTexture, TextureLink *AltRenderTarget, UInt8 u4)
{
	void (_cdecl *BeginScene1)(int, void *)=(void(*)(int, void *))0x007D7280;
	void (_cdecl *BeginScene2)(int, void *)=(void(*)(int, void *))0x007D71C0;
	void (_cdecl *EndScene)(void)=(void(*)(void))0x007D72D0;
	
	IDirect3DSurface9	*RenderTarget;
	IDirect3DSurface9	*SourceTexture;
	IDirect3DDevice9	*D3DDevice;
	bool UseAltRenderTarget;

	DeviceInfo			Info;

	//_MESSAGE("Calling RenderShader");
	
	D3DDevice=GetD3DDeviceNew();

	if (D3DDevice->TestCooperativeLevel()==D3D_OK)	// Just being paranoid.
	{
		
		// If an alternative render target is set that means that you are about to enter a menu where the game time is
		// frozen.

		if (AltRenderTarget->RenderedTexture)
		{
			UseAltRenderTarget=true;
			BeginScene1(1,AltRenderTarget->RenderedTexture->RenderTargets);
		}
		else
		{
			UseAltRenderTarget=false;
			BeginScene2(1,NULL);
		}

		// Adds ref. Need to release before leaving function otherwise Oblivion can't reset the device if lost.
		D3DDevice->GetRenderTarget(0,&RenderTarget);

		SourceTexture=RenderedTexture->RenderedTexture->RenderTargets->GetRenderTargetData(0)->surface;
		if(UseAltRenderTarget)
		{
			Info.Height=AltRenderTarget->RenderedTexture->RenderTargets->GetHeight(0);
			Info.Width=AltRenderTarget->RenderedTexture->RenderTargets->GetWidth(0);
		}
		else
		{
			Info.Height=RenderedTexture->RenderedTexture->RenderTargets->GetHeight(0);
			Info.Width=RenderedTexture->RenderedTexture->RenderTargets->GetWidth(0);
		}
		Info.AltRenderTarget=UseAltRenderTarget;
		Info.Caps=&v1_2_416::GetRenderer()->DeviceCaps;

		ShaderCode(D3DDevice,RenderTarget,SourceTexture,&Info);

		RenderTarget->Release();

		if (UseAltRenderTarget)
			EndScene();
	}
	return;
}

bool SpoofShader::IsShaderActive(void)
{
	//_MESSAGE("Calling IsShaderActive");
	return(this->ActivateShader);
}


void SpoofShader::ShaderCode(IDirect3DDevice9 *D3DDevice,IDirect3DSurface9 *RenderTo, IDirect3DSurface9 *RenderFrom, DeviceInfo *Info)
{
	D3DDevice->StretchRect(RenderFrom,NULL,RenderTo,NULL,D3DTEXF_POINT);

	return;
}

void SpoofShader::InitialiseShader(void)
{
	return;
}

void SpoofShader::SetName(char *name)
{
	int i = 0;

	while(name[i])
	{
		this->Name[i]=name[i];
		i++;
	}
	return;
}

char *SpoofShader::GetName(void)
{
	return(&this->Name[0]);
}

bool SpoofShader::IsSpoofShader(void)
{
	return(this->GetType()==&SpoofShaderRTTI);
}

void SpoofShader::DeviceLost(void)
{
	return;
}

void SpoofShader::DeviceReset()
{
	return;
}

SpoofShader::SpoofShader()
{
	this->ActivateShader=false;
	this->RefCount=0;
	for (int i=0;i<0x8c;i++)
		this->Padding[i]=0;
	this->Serialization=SpoofShaderSerializationCounter++;
	this->Name[0]=0;
}

#pragma optimize ("",off)
void _declspec(naked) SpoofShaderList::AddShader(SpoofShader *shader)
{
	_asm
	{
		mov eax,0x00803790
		jmp eax
	}
}
#pragma optimize ("",on)