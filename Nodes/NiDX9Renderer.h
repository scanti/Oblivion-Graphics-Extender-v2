/*	Name:			NiDX9Renderer
**	Description:	DirectX 9 renderer.
**	Inheritance:	NiRefObject::NiObject::NiRenderer::
**	Size:			0xB00
**	vTable:			0x00A88EA4
**	vTable size:	0x62
**	Constructor:	0x00769BE0
**	Includes:		D3D9, GameTypes, NiRenderTargetGroup, NiPixelData, NiDX9RenderState
*/	

#pragma once

#include "nodes\NiRenderer.h"
#include "D3D9.h"
#include "GameTypes.h"
#include "nodes\NiRenderTargetGroup.h"
#include "nodes\NiPoint3.h"
#include "nodes\NiRect.h"
#include "nodes\NiDX9RenderState.h"
#include "nodes\NiCamera.h"

namespace v1_2_416
{
	class	NiPixelData;
	class	NiD3DGeometryGroupManager;		
	class	NiUnsharedGeometryGroup;	
	class	NiDynamicGeometryGroup;			
	class	NiDX9VertexBufferManager;		
	class	NiDX9IndexBufferManager;	
	class	NiDX9TextureManager;			
	class	NiDX9LightManager;	
	class	NiDX9RenderedTextureData;
	class	NiDX9RenderedCubeMapData;
	class	NiDX9DynamicTextureData;
	class	NiSourceTexture;
	class	NiDX92DBufferData;
	class	NiD3DShaderInterface;
	class	NiD3DDefaultShader;
	class	NiTransformInterpolator;

	class NiDX9Renderer: public NiRenderer
	{
	public:
	
		NiDX9Renderer();
		virtual ~NiDX9Renderer();
		
		virtual void func_5F(void);
		virtual void func_60(void);
		virtual void func_61(void);

		void SetCameraViewProj(NiCamera *Camera);

		// Registers a function that gets called whenever the graphics card device is lost. The function format is
		// function (bool stage, void *FunctionData). stage is set to true when the device is being reset and false
		// when the device is being recreated. You can optionally specify a pointer to a structure that contains data
		// to be passed into the function.

		void *RegisterLostDeviceCallback(bool function(bool,void *),void *functiondata);
		
		UInt32									var210;						// 210
		UInt32									var214;						// 214
		UInt32									var218;						// 218
		UInt32									var21C;						// 21C
		UInt32									var220;						// 220
		UInt32									var224;						// 224
		UInt32									var228;						// 228
		UInt32									var22C;						// 22C
		UInt32									var230;						// 230
		UInt32									var234;						// 234
		UInt32									var238;						// 238
		UInt32									var23C;						// 23C
		UInt32									var240;						// 240
		UInt32									var244;						// 244
		UInt32									var248;						// 248
		UInt32									var24C;						// 24C
		UInt32									var250;						// 250
		UInt32									var254;						// 254
		UInt32									var258;						// 258
		UInt32									var25C;						// 25C
		UInt32									var260;						// 260
		UInt32									var264;						// 264
		UInt32									var268;						// 268
		UInt32									var26C;						// 26C
		UInt32									var270;						// 260
		UInt32									var274;						// 274
		UInt32									var278;						// 278
		UInt32									var27C;						// 27C
		IDirect3DDevice9						*pDirect3DDevice;			// 280
		D3DCAPS9								DeviceCaps;					// 284
		HWND									var3B4;						// 3B4
		HWND									FocusWindow;				// 3B8
		char									RendererDebugBuffer[512];	// 3BC
		UINT									D3DAdapter;					// 5BC
		D3DDEVTYPE								D3DDeviceType;				// 5C0
		DWORD									BehaviorFlags;				// 5C4
		UInt32									var5C8;						// 5C8
		UInt32									var5CC;						// 5CC
		UInt32									var5D0;						// 5D0
		D3DCOLOR								ClearColor;					// 5D4
		float									ClearZ;						// 5D8
		UInt32									ClearStencil;				// 5DC
		UInt32									var5E0;						// 5E0
		char									RendererDebugBuffer2[32];	// 5E4
		NiTPointerMap<UInt32>					PrePackObjects;				// 604 (NiVBBlock*, NiDX9Renderer::PrePackObjects)
		UInt32									var614;						// 614
		UInt32									var618;						// 618
		UInt32									var61C;						// 61C
		UInt32									var620;						// 620
		UInt32									var624;						// 624
		NiPoint3								var628;						// 628
		NiPoint3								var634;						// 634
		NiPoint3								var640;						// 640
		NiPoint3								var64C;						// 64C
		float									var658;						// 658
		float									var65C;						// 65C
		float									var660;						// 660
		float									var664;						// 664
		float									var668;						// 668
		float									var66C;						// 66C
		float									var670;						// 670
		float									var674;						// 674
		float									var678;						// 678
		float									var67C;						// 67C
		D3DMATRIX								IdentityMatrix;				// 680
		D3DVIEWPORT9							Viewport;					// 6C0
		UInt32									MaxVertexBlendMatrices;		// 6D8
		UInt32									MaxStreams;					// 6DC
		UInt32									MaxPixelShaderVersion;		// 6E0
		UInt32									MaxVertexShaderVersion;		// 6E4
		UInt8									var6E8;						// 6E8
		UInt8									var6E9;						// 6E9
		UInt16									pad6EA;						// 6EA
		UInt32									var6EC;						// 6EC
		UInt8									DeviceLost;					// 6F0
		UInt8									pad6F1;						// 6F1
		UInt16									pad6F2;						// 6F2
		UInt32									var6F4;						// 6F4
		UInt32									var6F8;						// 6F8
		UInt32									var6FC;						// 6FC
		UInt32									var700;						// 700
		UInt32									var704;						// 704
		UInt32									var708;						// 708
		UInt32									var70C;							// 70C
		UInt32									var710;						// 710
		UInt32									var714;						// 714
		UInt32									var718;						// 718
		UInt32									var71C;						// 71C
		UInt32									var720;						// 720
		UInt32									var724;						// 724
		UInt32									var728;						// 728
		UInt32									var72C;						// 72C
		UInt32									var730;						// 730
		UInt32									var734;						// 734
		UInt32									var738;						// 738
		UInt32									var73C;						// 73C
		UInt32									var740;						// 740
		UInt32									var744;						// 744
		UInt32									var748;						// 748
		UInt32									var74C;						// 74C
		UInt32									var750;						// 750
		UInt32									var754;						// 754
		UInt32									var758;						// 758
		UInt32									var75C;						// 75C
		UInt32									var760;						// 760
		UInt32									var764;						// 764
		UInt32									var768;						// 768
		UInt32									var76C;						// 76C
		UInt32									var770;						// 770
		UInt32									var774;						// 774
		UInt32									var778;						// 778
		UInt32									var77C;						// 77C
		UInt32									var780;						// 780
		UInt32									var784;						// 784
		UInt32									var788;						// 788
		UInt32									var78C;						// 78C
		UInt32									var790;						// 790
		UInt32									var794;						// 794
		UInt32									var798;						// 798
		UInt32									var79C;						// 79C
		UInt32									var7A0;						// 7A0
		UInt32									var7A4;						// 7A4
		UInt32									var7A8;						// 7A8
		UInt32									var7AC;						// 7AC
		UInt32									var7B0;						// 7B0
		UInt32									var7B4;						// 7B4
		UInt32									var7B8;						// 7B8
		UInt32									var7BC;						// 7BC
		UInt32									var7C0;						// 7C0
		UInt32									var7C4;						// 7C4
		UInt32									var7C8;						// 7C8
		UInt32									var7CC;						// 7CC
		UInt32									var7D0;						// 7D0
		UInt32									var7D4;						// 7D4
		UInt32									var7D8;						// 7D8
		UInt32									var7DC;						// 7DC
		UInt32									var7E0;						// 7E0
		UInt32									var7E4;						// 7E4
		UInt32									var7E8;						// 7E8
		UInt32									var7EC;						// 7EC
		UInt32									var7F0;						// 7F0
		UInt32									var7F4;						// 7F4
		UInt32									var7F8;						// 7F8
		UInt32									var7FC;						// 7FC
		UInt32									var800;						// 800
		UInt32									var804;						// 804
		UInt32									var808;						// 808
		UInt32									var80C;						// 80C
		UInt32									var810;						// 810
		UInt32									var814;						// 814
		UInt32									var818;						// 818
		UInt32									var81C;						// 81C
		UInt32									var820;						// 820
		UInt32									var824;						// 824
		UInt32									var828;						// 828
		UInt32									var82C;						// 82C
		UInt32									var830;						// 830
		UInt32									var834;						// 834
		UInt32									var838;						// 838
		UInt32									var83C;						// 83C
		UInt32									var840;						// 840
		UInt32									var844;						// 844
		UInt32									var848;						// 848
		UInt32									var84C;						// 84C
		UInt32									var850;						// 850
		UInt32									var854;						// 854
		UInt32									var858;						// 858
		UInt32									var85C;						// 85C
		UInt32									var860;						// 860
		NiPixelData								*PixelData1;				// 864
		NiPixelData								*PixelData2;				// 868
		NiPixelData								*PixelData3;				// 86C
		NiPixelData								*PixelData4;				// 870
		UInt32									var874;						// 874
		NiRenderTargetGroup						*RenderTargetGroup1;		// 878
		NiRenderTargetGroup						*RenderTargetGroup2;		// 87C
		NiRenderTargetGroup						*RenderTargetGroup3;		// 880
		NiTPointerMap<NiRenderTargetGroup>		RenderTargetList;			// 884
		UInt32									var894;						// 894
		UInt8									var898;						// 898
		UInt8									var899;						// 899
		UInt16									pad89A;						// 89A
		UInt32									var89C;						// 89C
		NiD3DGeometryGroupManager				*GeometryGroupManager;		// 8A0
		NiUnsharedGeometryGroup					*UnsharedGeometryGroup;		// 8A4
		NiDynamicGeometryGroup					*DynamicGeometryGroup;		// 8A8
		NiDX9RenderState						*RenderStateManager;		// 8AC
		NiDX9VertexBufferManager				*VertexBufferManager;		// 8B0
		NiDX9IndexBufferManager					*IndexBufferManager;		// 8B4
		NiDX9TextureManager						*TextureManager;			// 8B8
		NiDX9LightManager						*LightManager;				// 8BC
		NiTPointerMap<NiDX9RenderedTextureData>	RenderedTextureDataMap;		// 8C0 - hash NiRenderedTexture*
		NiTPointerMap<NiDX9RenderedCubeMapData>	RenderedCubMapDataMap;		// 8D0 - hash NiRenderedCubeMap*
		NiTPointerMap<NiDX9DynamicTextureData>	DynamicTextureDataMap;		// 8E0 - hash NiDynamicTexture*
		NiSourceTexture							*SourceTexture;				// 8F0
		NiTPointerList<NiDX92DBufferData>		BufferDataList;				// 8F4
		NiTPointerList<NiD3DShaderInterface>	ShaderInterfaceList;		// 904
		UInt32									var914;						// 914
		UInt32									var918;						// 918
		UInt32									var91C;						// 91C
		UInt32									var920;						// 920
		UInt32									var924;						// 924
		UInt32									var928;						// 928
		UInt32									var92C;						// 92C
		UInt32									var930;						// 930
		UInt32									var934;						// 934
		UInt32									var938;						// 938
		UInt32									var93C;						// 93C
		D3DMATRIX								m44World;					// 940
		D3DMATRIX								m44View;					// 980
		D3DMATRIX								m44Projection;				// 9C0
		D3DMATRIX								varA00;						// A00
		UInt32									varA40;						// A40
		UInt32									varA44;						// A44
		UInt32									varA48;						// A48
		UInt16									varA4C;						// A4C
		UInt16									padA4E;						// A4E
		UInt32									varA50;						// A50
		UInt32									varA54;						// A54
		UInt32									SizeWidth;					// A58
		UInt32									SizeHeight;					// A5C
		UInt32									varA60;						// A60
		HANDLE									hWnd1;						// A64
		HANDLE									hWnd2;						// A68
		UInt32									Adapter;					// A6C
		UInt32									varA70;						// A70
		D3DFORMAT								SurfaceFormat;				// A74
		UInt32									varA78;						// A78
		UINT									PresentInterval;			// A7C
		UInt32									varA80;						// A80
		UInt32									varA84;						// A84
		UInt32									varA88;						// A88
		UInt32									varA8C;						// A8C
		UInt32									varA90;						// A90
		NiD3DDefaultShader						*D3DDefaultShader;			// A94
		NiTArray<bool(*)(bool, void*)>			DeviceResetFunctionList;	// A98
		NiTArray<void *>						DeviceResetFuctionDataList;	// AA8
		NiTArray<bool(*)(void *)>				UnkCallbackList;			// AB8
		NiTArray<void *>						UnkCallbackDataList;		// AC8
		UInt32									varAD8;						// AD8
		UInt32									varADC;						// ADC
		UInt32									varAE0;						// AE0
		UInt32									varAE4;						// AE4
		UInt32									varAE8;						// AE8
		NiTransformInterpolator					*TransformInterpolator;		// AEC
		NiRect<float>							varAD0;						// AF0
		
	};

	NiDX9Renderer *GetRenderer(void);							// Crashes if I declare as a static memeber function?

}
		
		