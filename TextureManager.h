#pragma once

#include "obse\PluginAPI.h"
#include "d3dx9.h"
#include <vector>
#include "DepthBufferHook.h"
#include "Rendering.h"
#include "nodes\NiDX9Renderer.h"

#define TEXTUREVERSION 1

class TextureRecord
{
public:
	TextureRecord();
	~TextureRecord();

	IDirect3DTexture9*		texture;
	char					Filepath[260];
	bool					FromFile;
};

class StaticTextureRecord: public TextureRecord
{
public:
	StaticTextureRecord();
	~StaticTextureRecord();

	int AddRef();
	int Release();

	int						RefCount;
};

typedef std::vector<TextureRecord*> TextureList;
typedef std::vector<StaticTextureRecord*> StaticTextureList;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	static TextureManager*	GetSingleton();
	static TextureManager*	Singleton;

	void					InitialiseFrameTextures(void);
	void					DeviceRelease(void);
	int						LoadTexture(char *Filename,DWORD FromFile);
	StaticTextureRecord*	LoadStaticTexture(char *Filename);
	void					NewGame(void);
	void					LoadGame(OBSESerializationInterface *Interface);
	void					SaveGame(OBSESerializationInterface *Interface);
	bool					IsValidTexture(int TextureNum);
	IDirect3DTexture9*		GetTexture(int TextureNum);
	void					ReleaseTexture(IDirect3DTexture9* texture);
	void					FreeTexture(int index);
	int						FindTexture(IDirect3DTexture9* texture);

	TextureList				Textures;
	StaticTextureList		StaticTextures;

	IDirect3DTexture9*		thisframeTex;						
	IDirect3DSurface9*		thisframeSurf;

	IDirect3DTexture9*		lastpassTex;						
	IDirect3DSurface9*		lastpassSurf;					
	
	IDirect3DTexture9*		lastframeTex;
	IDirect3DSurface9*		lastframeSurf;
	
	bool					HasDepth;
	
	IDirect3DTexture9*		depth;
	IDirect3DSurface9*		depthSurface;
	IDirect3DTexture9*		depthRAWZ;
	
	bool					RAWZflag;
};

