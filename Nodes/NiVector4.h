/*	Name:			NiVector4
**	Description:	A vector or point in 4D space.
**	Inheritance:	none
**	Size:			
**	vTable:			none
**	vTable size:	none
**	Constructor:	
**	Includes:		
*/	

#pragma once

#include "d3dx9.h"

namespace v1_2_416
{
	class NiVector4: public D3DXVECTOR4
	{
	public:
		NiVector4();
		NiVector4(float _x, float _y, float _z, float _w);
		~NiVector4();

		void	Zero();
		float	GetLength();
		void	Normalize();
		void	Normalize3();
	};		
}