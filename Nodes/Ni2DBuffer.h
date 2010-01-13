/*	Name:			Ni2DBuffer
**	Description:	
**	Inheritance:	NiRefObject::NiObject::
**	Size:			14
**	vTable:			00A8098C
**	vTable size:	15
**	Constructor:	00732050
**	Includes:		
*/	

#pragma once

#include "NiObject.h"

namespace v1_2_416
{
	class NiDX9TextureBufferData;

	class Ni2DBuffer: public NiObject
	{
	public:
		Ni2DBuffer();
		virtual ~Ni2DBuffer();
		
		virtual UInt32	Unk_13(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4);
		virtual UInt32	Unk_14(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4);
		virtual bool	Unk_15(UInt32 u1);
		
		UInt32						width;			// 08
		UInt32						height;			// 0C
		NiDX9TextureBufferData		*BufferData;	// 10
		
	};
}
		
		