/*	Name:			NiAlphaAccumulator
**	Description:	To do with alpha sorting?
**	Inheritance:	NiRefObject::NiObject::NiAccumulator::NiBackToFrontAccumulator::
**	Size:			0x38
**	vTable:			0x00A7F494
**	vTable size:	0x18
**	Constructor:	0x0071A8E0
**	Includes:		
*/	

#pragma once

#include "nodes\NiBackToFrontAccumulator.h"


namespace v1_2_416
{
	class NiAlphaAccumulator:public NiBackToFrontAccumulator
	{
	public:
	
		UInt8			var34;				// 34 - default 1
		UInt8			var35;				// 35 - default 0
		UInt16			pad36;				// 36
		
	};
}
		
		