#include "nodes\NiVector4.h"

namespace v1_2_416
{
	NiVector4::NiVector4()
	{
		this->Zero();
	}

	NiVector4::NiVector4(float _x, float _y, float _z, float _w)
	{
		x=_x;
		y=_y;
		z=_z;
		w=_w;
	}

	NiVector4::~NiVector4()
	{
	};

	void NiVector4::Zero()
	{
		x=0;
		y=0;
		z=0;
		w=0;
		return;
	}
	
	float NiVector4::GetLength()
	{
		return(sqrt((x*x)+(y*y)+(z*z)+(w*w)));
	}

	void NiVector4::Normalize()
	{
		float len=this->GetLength();
		x=x/len;
		y=y/len;
		z=z/len;
		w=w/len;
		return;
	}
	
	void NiVector4::Normalize3()
	{
		float len=sqrt((x*x)+(y*y)+(z*z));

		x=x/len;
		y=y/len;
		z=z/len;
		w=0;
		return;
	}
}