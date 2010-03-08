#pragma once

#include "d3dx9.h"
#include "nodes\NiVector4.h"
#include "nodes\NiDX9Renderer.h"
#include "nodes/NiCamera.h"
#include "OBGE fork/Sky.h"
#include "nodes/NiBillboardNode.h"
#include <vector>
#include <map>
#include <utility>
#include "Rendering.h"
#include "obse/PluginAPI.h"

//#define MYVERTEXFORMAT D3DFVF_XYZRHW|D3DFVF_TEX1
#define MYVERTEXFORMAT D3DFVF_XYZ|D3DFVF_TEX1

#define SHADERVERSION 1

//struct D3D_sShaderVertex { float x,y,z,w,u,v; };
struct D3D_sShaderVertex { float x,y,z,u,v; };

struct TextureType
{
	int tex;
	char Name[100];
};

struct IntType
{
	char Name[100];
	int size;
	int	data[16];
};

struct FloatType
{
	char Name[100];
	int size;
	float data[16];
};

struct Constants
{
// ****** Global static shader constants ******

	float					rcpres[2];
	bool					bHasDepth;

// ****** Global shader constants (Updated each frame) ******

	D3DXMATRIX				world;
	D3DXMATRIX				view;
	D3DXMATRIX				proj;
	v1_2_416::NiVector4		time;
	v1_2_416::NiVector4		SunDir;
	v1_2_416::NiVector3		EyeForward;
};

class ShaderRecord
{
public:
	ShaderRecord();
	~ShaderRecord();

	void						Render(IDirect3DDevice9* D3DDevice,IDirect3DSurface9 *RenderTo);
	void						OnLostDevice(void);
	void						OnResetDevice(void);
	void						ApplyConstants(Constants *ConstList);
	bool						IsEnabled();
	bool						LoadShader(char *Filename);
	void						ApplyCompileDirectives(void);
	bool						SetShaderInt(char *name, int value);
	bool						SetShaderFloat(char *name, float value);
	bool						SetShaderVector(char *name, v1_2_416::NiVector4 *value);
	bool						SetShaderTexture(char *name, int TextureNum);
	void						SaveVars(OBSESerializationInterface *Interface);

	char						Name[100];
	char						Filepath[MAX_PATH];
	ID3DXEffect*				Effect;
	bool						Enabled;
	UINT32						ParentRefID; // Associates a shader with the esp/esm file the script the shader was created in.
};

typedef std::vector<ShaderRecord*> StaticShaderList;
typedef std::map<int, ShaderRecord*> ShaderList;

class ShaderManager
{
private:
	ShaderManager();
public:
	~ShaderManager();

	static ShaderManager*		GetSingleton(void);
	void						UpdateStaticConstants(void);
	void						UpdateFrameConstants(void);
	void						Render(IDirect3DDevice9 *D3DDevice,IDirect3DSurface9 *RenderTo, IDirect3DSurface9 *RenderFrom);
	void						RenderRAWZfix(IDirect3DDevice9*	D3DDevice,IDirect3DSurface9 *RenderTo);
	void						OnLostDevice(void);
	void						OnResetDevice(void);
	void						InitialiseBuffers(void);
	void						DeviceRelease(void);
	void						LoadShaderList(void);
	void						NewGame(void);
	void						LoadGame(OBSESerializationInterface *Interface);
	void						SaveGame(OBSESerializationInterface *Interface);

	int							AddShader(char *Filename, bool AllowDuplicates, UINT32 refID);
	bool						AddStaticShader(char *Filename);
	bool						RemoveShader(int ShaderNum);
	bool						IsShaderValid(int ShaderNum);
	bool						EnableShader(int ShaderNum, bool State);
	bool						SetShaderInt(int ShaderNum,char *name, int value);
	bool						SetShaderFloat(int ShaderNum, char *name, float value);
	bool						SetShaderVector(int ShaderNum, char *name, v1_2_416::NiVector4 *value);
	bool						SetShaderTexture(int ShaderNum, char *name, int TextureNum);
	void						PurgeTexture(IDirect3DTexture9 *texture);
	bool						GetShaderState(int ShaderNum);

	static ShaderManager*		Singleton;

	IDirect3DVertexBuffer9*		D3D_ShaderBuffer;

	int							ShaderIndex;
	int							MaxShaderIndex;
	StaticShaderList			StaticShaders;
	ShaderList					Shaders;
	ShaderRecord*				DepthShader;
	
	Constants					ShaderConst;
};