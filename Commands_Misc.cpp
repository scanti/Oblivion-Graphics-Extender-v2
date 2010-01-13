#include "Commands_Misc.h"
#include "Commands_Params.h"
#include "nodes\NiDX9Renderer.h"
#include "Rendering.h"

void NotImplemented(void)
{
	_MESSAGE("This command is not yet implemented.");
	return;
}

static bool GetAvailableGraphicsMemory_Execute(COMMAND_ARGS)
{
	*result = GetD3DDevice()->GetAvailableTextureMem();
	return true;
}
static bool GetScreenWidth_Execute(COMMAND_ARGS)
{
	v1_2_416::NiDX9Renderer *renderer=v1_2_416::GetRenderer();
	if(renderer)
	{
		*result = renderer->SizeWidth;
	}
	else
	{
		_MESSAGE("Can't locate renderer data.");
		*result=-1;
	}
	return true;
}
static bool GetScreenHeight_Execute(COMMAND_ARGS)
{
	v1_2_416::NiDX9Renderer *renderer=v1_2_416::GetRenderer();
	if(renderer)
	{
		*result = renderer->SizeHeight;
	}
	else
	{
		_MESSAGE("Can't locate renderer data.");
		*result=-1;
	}
	return true;
}
static bool ForceGraphicsReset_Execute(COMMAND_ARGS)
{
	NotImplemented();
	*result=0;
	return true;
}
static bool PurgeManagedTextures_Execute(COMMAND_ARGS)
{
	GetD3DDevice()->EvictManagedResources();
	*result=0;
	return true;
}

CommandInfo kCommandInfo_GetAvailableGraphicsMemory =
{
	"GetAvailableGraphicsMemory",
	"",
	0,
	"Returns an approximate amount of remaining graphics memory",
	0,
	0,
	0,
	GetAvailableGraphicsMemory_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_GetScreenWidth =
{
	"GetScreenWidth",
	"",
	0,
	"Returns the x resolution of the backbuffer",
	0,
	0,
	0,
	GetScreenWidth_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_GetScreenHeight =
{
	"GetScreenHeight",
	"",
	0,
	"Returns the y resolution of the backbuffer",
	0,
	0,
	0,
	GetScreenHeight_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_ForceGraphicsReset =
{
	"ForceGraphicsReset",
	"",
	0,
	"Resets the graphics device in the same way as alt-tabbing",
	0,
	0,
	0,
	ForceGraphicsReset_Execute,
	0,
	0,
	0
};
CommandInfo kCommandInfo_PurgeManagedTextures =
{
	"PurgeManagedTextures",
	"",
	0,
	"Evicts managed resources from vram",
	0,
	0,
	0,
	PurgeManagedTextures_Execute,
	0,
	0,
	0
};