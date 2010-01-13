/*	Name:			NiRect
**	Description:	Creates a quad of a data type;
**	Inheritance:	none
**	Size:			4 * size of data type
**	vTable:			none
**	vTable size:	
**	Constructor:	
**	Includes:		
*/	

#pragma once


namespace v1_2_416
{
	template<typename T>
	class NiRect
	{
	public:
		T		a;
		T		b;
		T		c;
		T		d;		
	};
}
		
		