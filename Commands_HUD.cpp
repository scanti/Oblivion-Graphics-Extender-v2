#include "Commands_HUD.h"
#include "Commands_Misc.h"
#include "Commands_Params.h"
#include "ScreenElements.h"
#include "OBSEShaderInterface.h"

static bool CreateHUDElement_Execute(COMMAND_ARGS)
{
	if(IsEnabled())
	{
		Sprite	*TempSprite=new(Sprite);
		*result = HUDManager::GetSingleton()->AddScreenElement(TempSprite);
	}
	return true;
}

static bool SetHUDElementTexture_Execute(COMMAND_ARGS)
{
	
	*result=0;
	DWORD id;
	int tex;
	if(!ExtractArgs(EXTRACTARGS, &id, &tex)) return true;

	if(IsEnabled())
		HUDManager::GetSingleton()->index(id)->SetTexture(tex);

	return true;
}
static bool SetHUDElementColour_Execute(COMMAND_ARGS)
{
	*result=0;
	
	DWORD id;
	float r, g, b;
	if(!ExtractArgs(EXTRACTARGS, &id, &r, &g, &b)) return true;

	if(IsEnabled())
		HUDManager::GetSingleton()->index(id)->SetColor(r,g,b);
	
	return true;
}
static bool SetHUDElementPosition_Execute(COMMAND_ARGS)
{
	*result=0;

	DWORD id;
	float x, y;
	if(!ExtractArgs(EXTRACTARGS, &id, &x, &y)) return true;

	if(IsEnabled())
		HUDManager::GetSingleton()->index(id)->SetPosition(x,y,0);
	
	return true;
}
static bool SetHUDElementScale_Execute(COMMAND_ARGS)
{
	*result=0;
	
	DWORD id;
	float x, y;
	if(!ExtractArgs(EXTRACTARGS, &id, &x, &y)) return true;

	if(IsEnabled())
		HUDManager::GetSingleton()->index(id)->SetScale(x,y);
	
	return true;
}
static bool SetHUDElementRotation_Execute(COMMAND_ARGS)
{
	*result=0;
	
	DWORD id;
	float rot;
	if(!ExtractArgs(EXTRACTARGS, &id, &rot)) return true;

	if(IsEnabled())
		HUDManager::GetSingleton()->index(id)->SetRotation(rot);
	
	return true;
}

CommandInfo kCommandInfo_CreateHUDElement =
{
	"CreateHUDElement",
	"",
	0,
	"Creates a new HUD element",
	0,
	0,
	0,
	CreateHUDElement_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_SetHUDElementTexture =
{
	"SetHUDElementTexture",
	"",
	0,
	"Sets the texture of a HUD element",
	0,
	2,
	kParams_TwoInt,
	SetHUDElementTexture_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_SetHUDElementColour =
{
	"SetHUDElementColour",
	"",
	0,
	"Sets the colour of a HUD element",
	0,
	4,
	kParams_Int3Floats,
	SetHUDElementColour_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_SetHUDElementPosition =
{
	"SetHUDElementPosition",
	"",
	0,
	"Sets the position of a HUD element",
	0,
	3,
	kParams_Int2Floats,
	SetHUDElementPosition_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_SetHUDElementScale =
{
	"SetHUDElementScale",
	"",
	0,
	"Sets the scale of a HUD element",
	0,
	3,
	kParams_Int2Floats,
	SetHUDElementScale_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_SetHUDElementRotation =
{
	"SetHUDElementRotation",
	"",
	0,
	"Sets the rotation of a HUD element",
	0,
	2,
	kParams_IntFloat,
	SetHUDElementRotation_Execute,
	0,
	0,
	0
};