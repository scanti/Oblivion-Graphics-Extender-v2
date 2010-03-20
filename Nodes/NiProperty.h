/*	Name:			NiProperty
**	Description:	Parent node for property classes. Abstract class.
**	Inheritance:	NiRefObject::NiObject::NiObjectNET::
**	Size:			18
**	vTable:			None
**	vTable size:	None
**	Constructor:	None
**	Includes:		
*/	

#pragma once

#include "NiObjectNet.h"

namespace v1_2_416
{
	class NiProperty: public NiObjectNET
	{
	public:
		NiProperty();
		~NiProperty();
	};
}
		
		