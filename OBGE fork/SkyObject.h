/*	Name:			SkyObject
**	Description:	Base class for sky objects.
**	Inheritance:	None
**	Size:			8
**	vTable:			00A570C8
**	vTable size:	4
**	Constructor:	00543C10
**	Includes:		NiPointer, NiNode
*/	

#pragma once

#include "nodes\NiPointer.h"
#include "nodes\NiNode.h"

namespace OBGEfork
{
	class SkyObject
	{
	public:
		SkyObject();
		virtual ~SkyObject();					// 00
		
		virtual v1_2_416::NiNode*	GetObjectNode(void);			// 01
		virtual void				Initialize(UInt32 u1);			// 02
		virtual void				func_03(UInt32 u1, UInt32 u2);	// 03
		
		v1_2_416::NiPointer<v1_2_416::NiNode>	ObjectNode;			// 04	
	};
}
		
		