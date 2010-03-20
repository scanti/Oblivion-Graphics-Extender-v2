/*	Name:			NiD3DRenderState
**	Description:	Render state manager. As renderer is a pure device, this keeps track of the render states.
**	Inheritance:	NiRefObject
**	Size:			1000 ?
**	vTable:			00A8B2AC
**	vTable size:	43
**	Constructor:	007802D0
**	Includes:		NiAlphaProperty, NiDitherProperty, NiFogProperty, NiShadeProperty, NiSpecularProperty, NiStencilProperty,
**					NiWireframeProperty, NiZBufferProperty, NiPointer
*/	

#pragma once

#include "NiRefObject.h"
#include "NiPointer.h"
#include "NiFogProperty.h"
#include "D3D9.h"

namespace v1_2_416
{
	class NiAlphaProperty;
	class NiDX9ShaderConstantManager;

	class NiD3DRenderState: public NiRefObject
	{
	public:
		NiD3DRenderState();
		virtual ~NiD3DRenderState();
		
		virtual void				 	func_01(void *u1);								// 01
		virtual void					SetAlpha(void *AlphaProperty);					// 02
		virtual void					SetDither(void *DitherProperty);				// 03
		virtual void					SetFog(NiFogProperty *FogProperty);				// 04
		virtual void					SetMaterial(void *u1);							// 05
		virtual void					SetShadeMode(void *ShadeProperty);				// 06
		virtual void					SetSpecular(void *SpecularProperty);			// 07
		virtual void					SetStencil(void *StencilProperty);				// 08
		virtual void					SetWireframe(void *WireframeProperty);			// 09
		virtual void 					SetZBuffer(void *ZBufferProperty);				// 0A
		virtual void					RestoreAlpha(void);								// 0B
		virtual void					SetVertexBlending(UInt16 u1);					// 0C
		virtual void					SetNormalization(void *u1);						// 0D
		virtual void					func_0E(UInt32 u1);								// 0E - doesn't do anything
		virtual float					GetVar088(void);								// 0F
		virtual void					func_10(float u1);								// 10
		virtual void					func_11(float u1, float u2);					// 11
		virtual BOOL					func_12(void);									// 12
		virtual void					func_13(BOOL u1);								// 13
		virtual void					func_14(UInt32 u1);								// 14
		virtual void					InitializeRenderStates(void);					// 15
		virtual void					BackUpAllStates(void);							// 16
		virtual void 					RestoreRenderState(D3DRENDERSTATETYPE state);	// 17
		virtual void					RestoreAllRenderStates(void);					// 18
		virtual void 					SetRenderState(D3DRENDERSTATETYPE state, UInt32 value, BOOL BackUp);	// 19
		virtual UInt32					GetRenderState(D3DRENDERSTATETYPE state);		// 1A
		virtual void					ClearPixelShaders(void);						// 1B
		virtual void					BackUpPixelShader(void);						// 1C
		virtual void					func_1D(void);									// 1D
		virtual void					SetPixelShader(IDirect3DPixelShader9* PixelShader, BOOL BackUp);		// 1E
		virtual IDirect3DPixelShader9*	GetPixelShader(void);							// 1F
		virtual	void					RestorePixelShader(void);						// 20
		virtual void					RemovePixelShader(IDirect3DPixelShader9* PixelShader);					// 21
		virtual void					SetVertexShader(IDirect3DVertexShader9* pShader, BOOL BackUp);			// 22 = 0
		virtual IDirect3DVertexShader9*	GetVertexShader(void);							// 23 = 0
		virtual void					RestoreVertexShader(void);						// 24 = 0
		virtual void					RemoveVertexShader(IDirect3DVertexShader9* pShader);						// 25 = 0
		virtual void					SetFVF(DWORD FVF, BOOL BackUp);					// 26 = 0
		virtual DWORD					GetFVF(void);									// 27 = 0
		virtual void					RestoreFVF(void);								// 28 = 0
		virtual void					RemoveFVF(DWORD FVF);							// 29 = 0
		virtual void					SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl, BOOL BackUp);	// 2A = 0
		virtual IDirect3DVertexDeclaration9*	GetVertexDeclaration(void);				// 2B = 0
		virtual void					RestoreVertexDeclaration(void);					// 2C = 0
		virtual void					RemoveVertexDeclatation(IDirect3DVertexDeclaration9* pDecl);			// 2D = 0
		virtual void					func_2E(void);									// 2E
		virtual void					func_2F(void);									// 2F
		virtual void					func_30(UInt32 u1, UInt32 u2);					// 30
		virtual void					func_31(void);									// 31
		virtual void 					SetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type, UInt32 Value, UInt32 BackUp);	// 32
		virtual UInt32					func_33(UInt32 u1, UInt32 u2);					// 33
		virtual void					SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value, BOOL BackUp);				// 34 = 0
		virtual DWORD 					GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type);				// 35 = 0
		virtual void					RestoreSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type);			// 36 = 0
		virtual void					ClearTextureList(void);							// 37
		virtual void					SetTexture(DWORD Sampler, IDirect3DBaseTexture9* pTexture);	// 38
		virtual IDirect3DBaseTexture9*	GetTexture(DWORD Sampler);						// 39
		virtual void					RemoveTexture(IDirect3DBaseTexture9* pTexture);	// 3A
		virtual void					SetSoftwareVertexProcessing(BOOL bSoftware);	// 3B
		virtual BOOL					GetSoftwareVertexProcessing(void);				// 3C
		virtual void					SetVar_0FF4(UInt8 u1);							// 3D
		virtual UInt8					GetVar_0FF4(void);								// 3E
		virtual void					SetVar_0FF5(UInt8 u1);							// 3F
		virtual UInt8					GetVar_0FF5(void);								// 40
		virtual void					Reset(void);									// 41
		virtual void					func_042(void);									// 42 = 0
			
		struct RenderState
		{
			UInt32	CurrentState;
			UInt32	BackUpState;
		};
		
		struct UnkStr01
		{
			UInt32	CurrentState;
			UInt32	BackUpState;
		};
		
		UInt32				var_0008;				// 0008
		UInt32				var_000C;				// 000C
		UInt32				var_0010;				// 0010
		UInt32				var_0014;				// 0014
		UInt32				var_0018;				// 0018
		UInt32				var_001C;				// 001C
		UInt32				var_0020;				// 0020
		UInt32				var_0024;				// 0024
		UInt32				var_0028;				// 0028
		UInt32				var_002C;				// 002C
		UInt32				var_0030;				// 0030
		UInt32				var_0034;				// 0034
		UInt32				var_0038;				// 0038
		UInt32				var_003C;				// 003C
		UInt32				var_0040;				// 0040
		UInt32				var_0044;				// 0044
		UInt32				var_0048;				// 0048
		UInt32				var_004C;				// 004C
		UInt32				var_0050;				// 0050
		UInt32				var_0054;				// 0054
		UInt32				var_0058;				// 0058
		UInt32				var_005C;				// 005C
		UInt32				var_0060;				// 0060
		UInt32				var_0064;				// 0064
		UInt32				var_0068;				// 0068
		UInt32				var_006C;				// 006C
		UInt32				var_0070;				// 0070
		NiAlphaProperty*	AlphaProperty;			// 0074
		float				var_0078;				// 0078
		float				var_007C;				// 007C
		float				var_0080;				// 0080
		float				var_0084;				// 0084
		float				var_0088;				// 0088
		float				var_008C;				// 008C
		float				var_0090;				// 0090
		float				var_0094;				// 0094
		UInt32				var_0098;				// 0098
		UInt32				var_009C;				// 009C
		UInt32				var_00A0;				// 00A0
		UInt32				var_00A4;				// 00A4
		UInt32				var_00A8;				// 00A8
		UInt32				var_00AC;				// 00AC
		UInt32				var_00B0;				// 00B0
		UInt32				var_00B4;				// 00B4
		UInt32				var_00B8;				// 00B8
		UInt32				var_00BC;				// 00BC
		UInt32				var_00C0;				// 00C0
		UInt32				var_00C4;				// 00C4
		UInt32				var_00C8;				// 00C8
		UInt32				var_00CC;				// 00CC
		UInt32				var_00D0;				// 00D0
		UInt32				var_00D4;				// 00D4
		UInt32				var_00D8;				// 00D8
		UInt32				var_00DC;				// 00DC
		UInt32				var_00E0;				// 00E0
		UInt32				var_00E4;				// 00E4
		UInt32				var_00E8;				// 00E8
		UInt32				var_00EC;				// 00EC
		UInt32				var_00F0;				// 00F0
		UInt32				var_00F4;				// 00F4
		UInt32				var_00F8;				// 00F8 - To do with materials?
		UInt32				var_00FC;				// 00FC
		UInt32				var_0100;				// 0100
		UInt32				var_0104;				// 0104
		UInt32				var_0108;				// 0108
		UInt32				var_010C;				// 010C
		UInt32				var_0110;				// 0110
		UInt32				var_0114;				// 0114
		UInt32				var_0118;				// 0118
		UInt32				var_011C;				// 011C
		RenderState			RenderStateList[256];	// 0120
		UnkStr01			TextureStageList[128];	// 0920
		UnkStr01			UnkList02[80];			// 0D20 - SamplerStateList ?
		IDirect3DBaseTexture9*	TextureList[16];		// 0FA0
		IDirect3DVertexShader9*	CurrentVertexShader;	// 0FE0
		IDirect3DVertexShader9*	VertexShaderBackUp;		// 0FE4
		IDirect3DPixelShader9*	CurrentPixelShader;		// 0FE8
		IDirect3DPixelShader9*	PixelShaderBackUp;		// 0FEC
		NiPointer<NiDX9ShaderConstantManager>	var_0FF0;	// 0FF0
		UInt8				var_0FF4;				// 0FF4
		UInt8				var_0FF5;				// 0FF5
		UInt16				pad_0FF6;				// 0FF6
		IDirect3DDevice9*	D3DDevice;				// 0FF8
		UInt32				var_0FFC;				// 0FFC
	};
}
		
		