#include "Commands_Textures.h"
#include "Commands_Misc.h"
#include "TextureManager.h"
#include "Commands_Params.h"
#include "OBSEShaderInterface.h"

static bool LoadTexture_Execute(COMMAND_ARGS)
{
	*result=0;
	
	char path[256];
	DWORD fromFile;
	if(!ExtractArgs(EXTRACTARGS, &path, &fromFile)) return true;

	if(IsEnabled())
		*result = TextureManager::GetSingleton()->LoadTexture(path, fromFile);
	else
		*result=-1;

	return true;
}

static bool FreeTexture_Execute(COMMAND_ARGS)
{
	*result=0;
	
	DWORD id;
	if(!ExtractArgs(EXTRACTARGS, &id)) return true;

	if(IsEnabled())
		TextureManager::GetSingleton()->FreeTexture(id);
	
	return true;
}

CommandInfo kCommandInfo_LoadTexture =
{
	"LoadTexture",
	"",
	0,
	"Loads a texture for use in shaders or HUD elements",
	0,
	2,
	kParams_StringInt,
	LoadTexture_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_FreeTexture =
{
	"FreeTexture",
	"",
	0,
	"Frees up the memory used by an obge texture",
	0,
	1,
	kParams_OneInt,
	FreeTexture_Execute,
	0,
	0,
	0
};