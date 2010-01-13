/*	Name:			NiAVObject
**	Description:	Contains properties of an object.
**	Inheritance:	NiRefObject::NiObject::NiObjectNET::
**	Size:			AC
**	vTable:			00A7DF24
**	vTable size:	21
**	Constructor:	00708450
**	Includes:		NiNode, NiSphere, NiMatrix33, NiVector3, NiProperty, bhkCollisionObject, NiPointer
*/	

#pragma once

#include "NiObjectNET.h"
//#include "NiNode.h"			// Can't include this as namespaces get messed up?
#include "NiPointer.h"
#include "NiVector3.h"
#include "NiMatrix33.h"
#include "GameTypes.h"

namespace v1_2_416
{

	class NiProperty;
	class bhkCollisionObject;
	class NiNode;

	class NiAVObject : public NiObjectNET
	{
	public:
		NiAVObject();
		virtual ~NiAVObject();
		
		virtual void		func_12(UInt32 u1);							// 12
		virtual void		func_13(float u1);							// 13
		virtual void		func_14(void);								// 14
		virtual void		func_15(UInt32 u1, UInt32 u2, UInt32 u3);	// 15
		virtual void		*func_16(void *u1);							// 16
		virtual void		func_17(UInt32 u1, UInt32 u2, UInt32 u3);	// 17
		virtual void		func_18(float u1, bool u2);					// 18
		virtual void		func_19(float u1);							// 19
		virtual void		func_1A(float u1);							// 1A
		virtual void		func_1B(UInt32 u1);							// 1B
		virtual void		func_1C(UInt32 u1);							// 1C
		virtual void		func_1D(void);								// 1D
		virtual void		func_1E(void);								// 1E
		virtual void		CalcCulling(void *CullingInfo);				// 1F
		virtual void		func_20(void *u1);							// 20

		NiNode *FindProperty(char *PropertyName);

		enum
		{
			kFlag_AppCulled =					1 << 0,	// originally named m_bAppCulled but they appear to have used bitfields
			kFlag_SelUpdate =					1 << 1,
			kFlag_SelUpdateTransforms =			1 << 2,
			kFlag_SelUpdatePropControllers =	1 << 3,
			kFlag_SelUpdateRigid =				1 << 4
		};

		struct M_FLAGS_B {
			unsigned AppCulled:1;
			unsigned SelUpdate:1;
			unsigned SelUpdateTransforms:1;
			unsigned SelUpdatePropControllers:1;
			unsigned SelUpdateRigid:1;
		};

		struct M_FLAGS_UI8 {
			UInt8	flags;
			UInt8	pad[3];
		};

		union u_m_flags {					// Do fancy set-up. Can access individual bitfields or the whole record for bitwise operations.
			M_FLAGS_B	individual;
			M_FLAGS_UI8 whole;
		};

		u_m_flags						m_flags;				// 018

		NiNode							*ParentNode;			// 01C - inherits from NiNode
		NiSphere						m_kWorldBound;			// 020
		v1_2_416::NiMatrix33			m_localRotate;			// 030
		v1_2_416::NiVector3				m_localTranslate;		// 054
		float							m_fLocalScale;			// 060
		v1_2_416::NiMatrix33			m_worldRotate;			// 064
		v1_2_416::NiVector3				m_worldTranslate;		// 088
		float							m_worldScale;			// 094
		NiTPointerList<NiProperty>		PropertyList;			// 098 - inherits from NiProperty
		NiPointer<bhkCollisionObject>	m_spCollisionObject;	// 0A8 - bhkCollisionObject
	};
}
		
		