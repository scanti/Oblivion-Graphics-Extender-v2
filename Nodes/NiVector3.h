/*	Name:			NiVector3
**	Description:	A vector or point in 3D space.
**	Inheritance:	none
**	Size:			16
**	vTable:			none
**	vTable size:	none
**	Constructor:	
**	Includes:		
*/	

#pragma once

#include "NiPoint3.h"

namespace v1_2_416
{
	class NiVector3: public NiPoint3
	{
	public:

		void	Set(float x, float y, float z);
		void	Zero();
		void	Normalize();
		float	GetLength();
		void	DotProduct(NiVector3 v1, NiVector3 v2);
		void	CrossProduct(NiVector3 v1, NiVector3 v2);
		
	};
}
		
		