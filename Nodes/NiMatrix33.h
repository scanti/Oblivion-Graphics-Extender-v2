/*	Name:			NiMatrix3
**	Description:	A 3x3 matrix. Usually contains rotation data.
**	Inheritance:	
**	Includes:		NiVector3
*/	

#pragma once

#include "NiVector3.h"

namespace v1_2_416
{
	class NiMatrix33
	{
	public:
		NiMatrix33();
		
		void		GetUpVector(NiVector3 *up);
		void		GetRightVector(NiVector3 *right);
		void		GetForwardVector(NiVector3 *forward);
		
		float		data[3][3];
	};
}
		
		