/*	Name:			NiDX9ImplicitDepthStencilBufferData	
**	Description:	
**	Inheritance:	NiRefObject::NiDX92DBufferData::
**	Size:			14
**	vTable:			00A899F4
**	vTable size:	10
**	Constructor:	0076E0B0 - Creates singleton
**	Includes:	
** 	Notes:			Also inherits from NiDX9DepthStencilBufferData. I think class defined only for RTTI info.	
*/	

#pragma once

#include "NiDX92DBufferData.h"

namespace v1_2_416
{
	class NiDX9ImplicitDepthStencilBufferData: public NiDX92DBufferData
	{
	public:
		NiDX9ImplicitDepthStencilBufferData();
		virtual ~NiDX9ImplicitDepthStencilBufferData();
				
	};
}
		
		