#pragma once

#include "obse/NiNodes.h"
#include "nodes/BSRenderedTexture.h"
#include "nodes/NiRefObject.h"
#include "D3D9.h"

class TextureLink
{
public:
	v1_2_416::BSRenderedTexture *RenderedTexture;
};

static NiRTTI		SpoofShaderRTTI = {"SpoofShader",(NiRTTI *)0xB4257C};
static UInt32		SpoofShaderSerializationCounter = 0;


class SpoofShader
{
public:
	SpoofShader();
	//~SpoofShader();

	virtual void			Deconstructor(UInt32 u1);
	virtual NiRTTI			*GetType(void);
	virtual UInt32			Unk_02(void);
	virtual UInt32			Unk_03(void);		
	virtual UInt32			Unk_04(void);			
	virtual UInt32			Unk_05(void);	
	// This is one of three functions that gets called by the ImageSpaceShader routines. It's purpose is to update any
	// internal variables.
	virtual UInt32			UpdateInternalVars(UInt32 Unk01);	
	virtual UInt32			Unk_07(void);

	virtual UInt8			Unk_08(void);																						// Returns Unk_01C
	virtual void			Unk_09(UInt32 Unk01);
	virtual UInt32			Unk_0A(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7);				// Returns false
	virtual UInt32			Unk_0B(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7);				// Returns false
	virtual UInt32			Unk_0C(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7);				// Returns false
	virtual UInt32			Unk_0D(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7, UInt32 u8);		// Returns false
	virtual UInt32			Unk_0E(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7, UInt32 u8);		// Returns false
	virtual UInt32			Unk_0F(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4);													// Returns false
	virtual UInt32			Unk_10(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7, UInt32 u8);		// Returns false
	virtual UInt32			Unk_11(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 u5, UInt32 u6, UInt32 u7);				// Returns false
	virtual void			Unk_12(void);																						// Returns false
	virtual void			Unk_13(void);																						// Returns false
	virtual void			Unk_14(void);																						// Returns false
	virtual void			Unk_15(UInt32 u1);																					// Doesn't do anything or return a value.
	virtual void			Unk_16(void);
	virtual void			Unk_17(void);
	virtual void			Unk_18(void);
	virtual void			Unk_19(void);
	virtual void			Unk_1A(void);																						// Returns false
	virtual void			Unk_1B(void);																						// Returns false
	virtual void			Unk_1C(void);																						// Returns false
	virtual void			Unk_1D(void);																						// Returns false
	virtual UInt8			Unk_1E(void);																						// Returns Unk_01D
	virtual void			Unk_1F(UInt8 value);

	virtual void			Unk_20(void);

	virtual bool			Unk_21(void);
	virtual void			Unk_22(void);					// Doesn't do or return anything
	virtual void			Unk_23(void);					// Doesn't do or return anything
	virtual void			Unk_24(void);
	virtual void			Unk_25(UInt32 u1);
	virtual bool			Unk_26(void);					// Returns true
	virtual void			Unk_27(void);
	virtual bool			Unk_28(void);					// Returns true
	virtual void			Unk_29(UInt32 u1, UInt8 u2);	// Sets Unk_074 to u1, Unk_078 to u2.

	// This function is called when the engine wants to render an imagespace shader.
	virtual void			RenderShader(void *ScreenElements, TextureLink *RenderedTexture, TextureLink *AltRenderTarget, UInt8 u4);
	
	// This tells the engine if an imagespace shader is active or not. I've changed it so it returns the boolean variable
	// ActivateShader. Although you could overload it with your own test.
	virtual bool			IsShaderActive(void);

/**************************************************************************************************************************
**           END OF IMAGE SPACE SHADER VIRTUAL FUNCTIONS. ANY FUNCTIONS AFTER THIS ARE MY OWN IMPLEMENTATIONS.           **
**************************************************************************************************************************/

	struct DeviceInfo {
		UInt32			Width;
		UInt32			Height;
		bool			AltRenderTarget;
		D3DCAPS9		*Caps;
	};

	// This function is overloaded with your own shader code. At the moment it just StretchRects to the render target.
	// It will automatically Begin and End the scene as is needed. I need to think about what to do when the 3D device is
	// lost. At the moment I don't need to do anything but if the overloaded shader code function creates any resources they
	// will need to be destroyed and recreated when the device is lost.


	virtual void			ShaderCode(IDirect3DDevice9	*D3DDevice,IDirect3DSurface9 *RenderTo,IDirect3DSurface9 *RenderFrom, DeviceInfo *Info);

	// Call this function to initialise any internal vars.

	virtual void			InitialiseShader(void);

	// Allows you to assign a name to your shader code. TO DO: Add code to make use of this.

	virtual void			SetName(char *name);

	// Gets the name of the shader assigned by SetName.

	virtual char			*GetName(void);

	// This function is called whenever the graphics card device is lost. You must overload this function with your
	// code to release any resources that your object uses, otherwise Oblivion will freeze up in a release/recreate
	// resources loop.

	virtual void			DeviceLost(void);

	// This function is called whenever Oblivion is recreating the graphics card device. You can use this function to
	// recreate any previously released resources.

	virtual void			DeviceReset(void);

	// This function returns true if the shader object is a SpoofShader created in the current plug-in. This is to allow
	// several plug-ins to use the image space shader list and not conflict with each other.

	bool					IsSpoofShader(void);

	UInt32					RefCount;
	// As far as I'm aware the only variable is this class that's accessed outside the class i.e. public is RefCount.
	// However I can't be 100% sure so I've padded out the class so the Oblivion code doesn't accidentally trample all
	// over the heap. (A very bad thing and difficult to trace).
	UInt8					Padding[0x8c];
	bool					ActivateShader;

	// This contain a unique UInt32 for each shader object that's created.

	UInt32					Serialization;
	char					Name[100];

};

class NiScreenElements;

class SpoofShaderList
{
public:

	NiTPointerList<SpoofShader>		ShaderList;				// 00
	NiScreenElements				*ScreenElements;		// 10
	v1_2_416::BSRenderedTexture		*RenderedTexture;		// 14
	SpoofShader						*CopyShader;			// 18


	void AddShader(SpoofShader *shader);
};

class pSpoofShaderList
{
public:
	SpoofShaderList	*p;
};