/*	Name:			NiAccumulator
**	Description:	Something to do with sorting?
**	Inheritance:	NiRefObject::NiObject::
**	Size:			0C
**	vTable:			00A80B3C
**	vTable size:	18
**	Constructor:	00733810
**	Includes:		
*/	

#pragma once

#include "NiObject.h"

namespace v1_2_416
{
	class NiAccumulator: public NiObject
	{
	public:
		NiAccumulator();
		virtual ~NiAccumulator();

		virtual void			func_13(int i1);				// 013
		virtual void			func_14(int i1);				// 014
		virtual void			func_15(void);					// 015
		virtual UInt32			func_16(int i1);				// 016 = 0
		virtual UInt32			func_17(int i1);				// 017

		UInt32					var_008;						// 008
		
	};
}
		
		