/*	Name:			
**	Description:	
**	Inheritance:	
**	Size:			
**	vTable:			
**	vTable size:	
**	Constructor:	
**	Includes:		
*/	

#pragma once

#include "NiVector3.h"

namespace v1_2_416
{
	
	void NiVector3::Set(float x, float y, float z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
		return;
	}

	void NiVector3::Zero()
	{
		x=0.0;
		y=0.0;
		z=0.0;
		return;
	}

	void NiVector3::Normalize()
	{
		float len=sqrt((x*x)+(y*y)+(z*z));

		if(len>0.0000001)
		{
			x=x/len;
			y=y/len;
			z=z/len;
		}
		else
		{
			x=0;
			y=0;
			z=0;
		}
		return;
	}



}
		
		