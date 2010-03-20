/*	Name:			NiFogProperty
**	Description:	Holds settings for fog.
**	Inheritance:	NiRefObject::NiObject::NiObjectNET::NiProperty::
**	Size:			2C
**	vTable:			0x00A81984
**	vTable size:	15
**	Constructor:	007C82A0
**	Includes:		NiColorRGB
*/	

#pragma once

#include "NiProperty.h"
#include "MiscNiDataTypes.h"


namespace v1_2_416
{
	class NiFogProperty: public NiProperty
	{
	public:
		enum {
			Enabled = 1,
			FogFunctionMask = 2+4,
			FOG_Z_LINEAR = 2,
			FOG_RANGE_SQ = 3,
			FOG_VERTEX_ALPHA = 4
		};
		
		virtual UInt32		func_013(void);			// returns 1
		virtual void		func_014(float u1);
		
		UInt8				Flags;					// 018
		UInt8				pad19;					// 019
		UInt16				pad1A;					// 01A
		float				Depth;					// 01C
		NiColorRGB			Color;					// 020
		UInt8				pad23;					// 023
		float				var24;					// 024
		float				var28;					// 028
	};
}
		
		