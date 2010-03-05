/*	Name:			BSRenderedTexture	
**	Description:	Container for the render surfaces
**	Inheritance:	NiRefObject
**	Size:			0x24
**	vTable:			0x00A91370
**	vTable size:	1
**	Constructor:	0x007D6BD0
**	Includes:		NiRenderTargetGroup, NiRenderedTexture
*/	

#pragma once
#include "NiRefObject.h"
#include "NiRenderTargetGroup.h"
//#include "NiRenderedTexture.h"


namespace v1_2_416
{
	class NiRenderedTexture;

	class BSRenderedTexture: public NiRefObject
	{
	public:
		BSRenderedTexture();
		virtual ~BSRenderedTexture();
		
		static BSRenderedTexture *Create(UInt32 Width, UInt32 Height, UInt32 u3, UInt32 u4, void *DepthStecilBuffer)
		{
			_asm
			{
				mov eax,0x007D6F40
				jmp eax
			}
		}
		
		NiRenderTargetGroup		*RenderTargets;		// 08
		UInt32					var_0C;				// 0C
		UInt32					var_10;				// 10
		UInt32					var_14;				// 14
		UInt32					var_18;				// 18
		UInt32					var_1C;				// 1C
		NiRenderedTexture		*RenderedTexture;	// 20
		
	};
}
		
		