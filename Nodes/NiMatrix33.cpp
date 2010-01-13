#include "NiMatrix33.h"

namespace v1_2_416
{
	NiMatrix33::NiMatrix33()
	{
		data[0][0]=0;
		data[0][1]=0;
		data[0][2]=0;
		data[1][0]=0;
		data[1][1]=0;
		data[1][2]=0;
		data[2][0]=0;
		data[2][1]=0;
		data[3][2]=0;
	}

	void NiMatrix33::GetUpVector(v1_2_416::NiVector3 *up)
	{
		up->Set(this->data[0][1],this->data[1][1],this->data[2][1]);
		return;
	}

	void NiMatrix33::GetRightVector(v1_2_416::NiVector3 *right)
	{
		right->Set(this->data[0][2],this->data[1][2],this->data[2][2]);
		return;
	}

	void NiMatrix33::GetForwardVector(v1_2_416::NiVector3 *forward)
	{
		forward->Set(this->data[0][0],this->data[1][0],this->data[2][0]);
		return;
	}
}