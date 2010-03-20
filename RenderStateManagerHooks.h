#pragma once

#include "nodes\NiDX9RenderState.h"
#include "nodes\NiFogProperty.h"
#include "D3D9.h"

namespace v1_2_416
{
	class NiDX9RenderStateEx: public NiDX9RenderState
	{
	public:
		static bool DisableFogOverride;

		void SetRenderStateNew(D3DRENDERSTATETYPE state, UInt32 value, BOOL BackUp);
		void SetRenderStateOld(D3DRENDERSTATETYPE state, UInt32 value, BOOL BackUp);

		static void HookRenderStateManager(void);
	};
}