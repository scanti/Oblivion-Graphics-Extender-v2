/*	Name:			NiRefObject
**	Description:	Keeps track of the reference counting for each class. Like IUnknown.
**	Inheritance:	Base Class
**	Size:			08
**	vTable:			00A3FCF8
**	vTable size:	01
**	Constructor:	inline?
**	Includes:		Windows.h
*/	

#pragma once

#include "Windows.h"
#include "MiscNiDataTypes.h"
#include "NiRefObject.h"

/* Base class. Keeps track of the reference count of a class.
*/

namespace v1_2_416
{
	void NiRefObject::AddRef()
	{
		InterlockedIncrement((LONG *)&m_uiRefCount);
		return;
	}

	UInt32 NiRefObject::Release()
	{
		if (!InterlockedDecrement((LONG *)&m_uiRefCount))
			delete(this);
		return(m_uiRefCount);
	}

	UInt32 NiRefObject::GetRefCount()
	{
		return(m_uiRefCount);
	}
		
	// static UInt32	m_uiGlobalObjectCount				// loc: 00B3FD64
}
		
		