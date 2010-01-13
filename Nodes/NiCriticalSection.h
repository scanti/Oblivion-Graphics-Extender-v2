/*	Name:			NiCriticalSection
**	Description:	Contains the critical section stucture/s for multi threading. This is just a fake structure to ensure that any objects
**					that use the NiCriticalSection object are correctly aligned.
**	Inheritance:	None?
**	Size:			0x80
**	vTable:			None
**	vTable size:
**	Constructor:	Unknown
**	Includes:		
*/	

#pragma once


namespace v1_2_416
{
	class NiCriticalSection
	{
	public:
	
		UInt8		padding[0x80];
		
	};
}
		
		