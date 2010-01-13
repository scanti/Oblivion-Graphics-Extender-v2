/*	Name:			NiPointer
**	Description:	A pointer to an object. Keeps track of the objects ref count.
**	Inheritance:	none
**	Size:			4
**	vTable:			none
**	vTable size:	
**	Constructor:	
**	Includes:		
*/	

#pragma once


namespace v1_2_416
{
	template <typename T>
	class NiPointer
	{
	public:
		NiPointer(void)
		{
			p=NULL;
		};

		NiPointer(T *data)
		{
			p=data;
		}
		
		~NiPointer(void)
		{
			ToNull();
		};

		NiPointer<T> *Set(T *object)
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
		};		// MUST INHERIT FROM NiRefObject

		void ToNull(void)
		{
			if(p)
			{
				p->Release();
				p=NULL;
			}
			return;
		};

		T *Get(void)
		{
			return(p);	
		};
		
		T* 		p;				
	};
}
		
		