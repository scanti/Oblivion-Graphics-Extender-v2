/*	Name:			NiBackToFrontAccumulator
**	Description:	To do with sorting?
**	Inheritance:	NiRefObject::NiObject::NiAccumulator::
**	Size:			34
**	vTable:			00A80BCC
**	vTable size:	18
**	Constructor:	00733710
**	Includes:		NiTPointerList, NiGeometry
*/	

#pragma once

#include "NiAccumulator.h"
#include "../obse/GameTypes.h"

class		NiGeometry;

namespace v1_2_416
{
	class NiBackToFrontAccumulator: public NiAccumulator
	{
	public:
		NiBackToFrontAccumulator();
		virtual ~NiBackToFrontAccumulator();

		NiTPointerList<NiGeometry>		Unk_00C;				// 00C
		UInt32							Unk_01C;				// 01C
		UInt32							Unk_020;				// 020
		UInt32							Unk_024;				// 024
		UInt32							Unk_028;				// 028
		UInt32							Unk_02C;				// 02C
		UInt32							Unk_030;				// 030
	};
}
		
		