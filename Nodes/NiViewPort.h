/*	Name:			NiViewPort
**	Description:	View port
**	Inheritance:	none
**	Size:			10
**	vTable:			none
**	vTable size:	
**	Constructor:	inline
**	Includes:		NiRect
*/	

#pragma once

#include "NiRect.h"

namespace v1_2_416
{
	class NiViewPort
	{
	public:
		NiViewPort();
		~NiViewPort();
		
		NiRect<float>	port;
		
	};
}
		
		