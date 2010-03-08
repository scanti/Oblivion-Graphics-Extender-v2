#pragma once

#include "SpoofShader.h"
#include "TextBuffer.h"
#include "d3dx9.h"
#include "ShaderManager.h"
#include <stdio.h>
#include "obse\PluginAPI.h"

// This class overloads the SpoofShader class and renders the memory dump to the screen.

// TO DO: Tidy up this class. Protect internal vars.

class OBSEShaderInterface:public SpoofShader
{
public:

	static OBSEShaderInterface		*GetSingleton(void);	// Use this to access the OBSEShaderInterface object. If the object doesn't exist
													// then one will be created. DO NOT USE new.
	static OBSEShaderInterface		*Singleton;

	virtual void			ShaderCode(IDirect3DDevice9	*D3DDevice,IDirect3DSurface9 *RenderTo,IDirect3DSurface9 *RenderFrom, DeviceInfo *Info);
	virtual void			InitialiseShader(void);
	virtual void			DeviceLost(void);
	virtual void			DeviceReset(void);
	virtual void			DeviceRelease(void);		// Basically the deconstructor. Kept seperate do I can't confuse with "Oblivion's" deconstructor.
	virtual void			NewGame(void);
	virtual void			LoadGame(OBSESerializationInterface *Interface);
	virtual void			SaveGame(OBSESerializationInterface *Interface);

	TextBuffer 				*MemoryDumpString;

	float rcpres[2];
	
	LPD3DXFONT				pFont;
	LPD3DXFONT				pFont2;
	D3DXFONT_DESC			FontDescription;
	D3DXFONT_DESC			FontDescription2;
	RECT					FontRect;
	D3DCOLOR				FontColor;
	D3DCOLOR				FontColor2;

	bool					DebugOn;
};

static pSpoofShaderList *obImageSpaceShaderList=(pSpoofShaderList *)0x00B42D7C;
static void (*obAddImageSpaceShader)(SpoofShader *)=(void(*)(SpoofShader *))0x00803790;

bool LostDevice(bool stage,void *parameters);

static OBSEMessagingInterface* messanger=NULL;
static PluginHandle handle = kPluginHandle_Invalid;

void SetMessaging(OBSEMessagingInterface *Interface, PluginHandle Handle);
OBSEMessagingInterface	*GetMessaging(void);
PluginHandle			GetHandle(void);
bool IsEnabled();
