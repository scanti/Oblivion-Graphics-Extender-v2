/*	Name:			Sun
**	Description:	Sun sky object.
**	Inheritance:	SkyObject::
**	Size:			28
**	vTable:			00A571DC
**	vTable size:	4
**	Constructor:	00544B50
**	Includes:		NiPointer, NiBillboardNode, NiTriShape, NiPick, NiLight, NiTArray
*/	

#pragma once

#include "SkyObject.h"
#include "nodes\NiPointer.h"
#include "nodes\MiscNiDataTypes.h"
#include "nodes\NiBillboardNode.h"
//#include "NiTriShape.h"
//#include "NiPick.h"
//#include "NiLight.h"

namespace OBGEfork
{
	class NiLight;
	class NiTriShape;
	class NiPick;

	class Sun: public SkyObject
	{
	public:
		Sun();
		virtual ~Sun();		// 00
	
		v1_2_416::NiPointer<v1_2_416::NiBillboardNode>	SunBillboard;			// 08
		v1_2_416::NiPointer<v1_2_416::NiBillboardNode>	SunGlareBillboard;		// 0C
		v1_2_416::NiPointer<NiTriShape>			SunGeometry;			// 10
		v1_2_416::NiPointer<NiTriShape>			SunGlareGeometry;		// 14
		v1_2_416::NiTArray<NiPick*>*			SunPickList;			// 18 NiPick::Record
		v1_2_416::NiPointer<NiLight>			SunDirLight;			// 1C
		float									var20;					// 20
		UInt8									var24;					// 24
		UInt8									var25;					// 25
		UInt16									var26;					// 26
	};
}
		
		