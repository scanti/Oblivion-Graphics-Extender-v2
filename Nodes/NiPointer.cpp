#include "NiPointer.h"

namespace v1_2_416
{

/*
	template <typename T>
	NiPointer<T>::NiPointer(T *data)
	{
		p=data;
		if (data)
			data->AddRef();
	}
*/ 

	template <typename T>
	NiPointer<T> *NiPointer<T>::Set(T *object)
	{
		if(p)
		{
			p->Release();
			p=NULL;
		}
			
		if(object)
		{
			p=object;
			p->AddRef();
		}
		
		return(this);	
	}

	template <typename T>
	void NiPointer<T>::ToNull(void)
	{
		if(p)
		{
			p->Release();
			p=NULL;
		}
		return;
	}

	template <typename T>
	T *NiPointer<T>::Get(void)
	{
		return(p);	
	}
}