/*	Name:			NiNode
**	Description:	Basic scenegraph branch node.
**	Inheritance:	NiRefObject::NiObject::NiObjectNET::NiAVObject::
**	Size:			DC
**	vTable:			00A7E38C
**	vTable size:	27
**	Constructor:	0070B780
**	Includes:		NiTArray<>, NiTPointerList<>, NiDynamicEffect
*/	

#pragma once

#include "NiAVObject.h"
#include "MiscNiDataTypes.h"
#include "GameTypes.h"

namespace v1_2_416
{
	class NiDynamicEffect;

	class NiNode : public NiAVObject
	{
	public:
		NiNode();
		virtual ~NiNode();

		virtual void		func_21(void *u1, char u2);					// 21
		virtual UInt32		func_22(UInt32 u1, UInt32 u2);				// 22
		virtual UInt32		func_23(UInt32 u1,UInt32 u2);				// 23
		virtual UInt32		func_24(UInt32 u1, UInt32 u2, UInt32 u3);	// 24
		virtual void		func_25(void);								// 25
		virtual UInt32		func_26(void);								// 26 - returns 0

		v1_2_416::NiTArray<NiAVObject *>	ChildList;					// 0AC
		NiTPointerList<NiDynamicEffect>		NiDynamicEffectList;		// 0BC
		float								unkCC;						// 0CC
		float								unkD0;						// 0D0
		float								unkD4;						// 0D4
		float								unkD8;						// 0D8	
	};
}
		
		