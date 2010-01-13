/*	Name:			NiCamera
**	Description:	Camera node.
**	Inheritance:	NiRefObject::NiObject::NiObjectNET::NiAVObject::
**	Size:			124
**	vTable:			00A7E4C4
**	vTable size:	21
**	Constructor:	0070D59
**	Includes:		NiViewPort
*/	

#pragma once

#include "NiAVObject.h"
#include "NiNodes.h"
#include "NiViewPort.h"

namespace v1_2_416
{
	class NiCamera:public NiAVObject
	{
	public:
		NiCamera();
		virtual ~NiCamera();
		
		UInt32		var_0AC;				// 0AC
		UInt32		var_0B0;				// 0B0
		UInt32		var_0B4;				// 0B4
		UInt32		var_0B8;				// 0B8
		UInt32		var_0BC;				// 0BC
		UInt32		var_0C0;				// 0C0
		UInt32		var_0C4;				// 0C4
		UInt32		var_0C8;				// 0C8
		UInt32		var_0CC;				// 0CC
		UInt32		var_0D0;				// 0D0
		UInt32		var_0D4;				// 0D4
		UInt32		var_0D8;				// 0D8
		UInt32		var_0DC;				// 0DC
		UInt32		var_0E0;				// 0E0
		UInt32		var_0E4;				// 0E4
		UInt32		var_0E8;				// 0E8
		NiFrustum	m_kViewFrustum;			// 0EC
		float		m_fMinNearPlaneDist;	// 108
		float		m_fMaxFarNearRatio;		// 10C
		NiViewPort	m_kPort;				// 110
		float		var_120;				// 120
	};
}
		
		