/*	Name:			NiRefObject
**	Description:	Keeps track of the reference counting for each class. Like IUnknown.
**	Inheritance:	Base Class
**	Size:			08
**	vTable:			00A3FCF8
**	vTable size:	01
**	Constructor:	inline?
**	Includes:		
*/	

#pragma once

#include "MiscNiDataTypes.h"

/* Base class. Keeps track of the reference count of a class.
*/

namespace v1_2_416
{
	class NiRefObject
	{
	public:
		NiRefObject();
		virtual ~NiRefObject();	

		// Helper functions

		void 	AddRef();										// Adds to the reference count of an object.
		UInt32 	Release();										// Releases an object. Deletes object if there
																// are no more instances of the object.
																// Otherwise returns the new ref count.
		UInt32 	GetRefCount();									// Gets the object count of an object.
		
	protected:
		UInt32			m_uiRefCount;							// 04
		// static UInt32	m_uiGlobalObjectCount				// loc: 00B3FD64
	};
}
		
		