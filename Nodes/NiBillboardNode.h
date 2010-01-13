/*	Name:			NiBillboardNode
**	Description:	Geometry that always faces the front of the screen.
**	Inheritance:	NiRefObject::NiObject::NiObjectNET::NiAVObject::NiNode::
**	Size:			E4
**	vTable:			00A45134
**	vTable size:	27
**	Constructor:	004BA360, inline a few times
**	Includes:		
*/	

#pragma once

#include "NiNode.h"

namespace v1_2_416
{
	class NiBillboardNode: public NiNode
	{
	public:
		NiBillboardNode();
		virtual ~NiBillboardNode();

		enum {
			ALWAYS_FACECAMERA,
			ROTATE_ABOUTUP,
			RIGID_FACECAMERA,
			ALWAYS_FACECENTER,
			RIGID_FACECENTER,
			BSROTATE_ABOUTUP
		};

		UInt16		m_eMode;				// DC init = 9
		UInt16		pad_DE;					// DE
		float		var_E0;					// E0 init = 0.0
	};
}
		
		