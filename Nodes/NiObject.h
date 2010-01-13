/*	Name:			NiObject
**	Description:	Base for all scenegraph node objects.
**	Inheritance:	NiRefObject::
**	Size:			08
**	vTable:			00A7D61C
**	vTable size:	13
**	Constructor:	007005D0
**	Includes:		NiRTTI
*/	

#pragma once

#include "MiscNiDataTypes.h"
#include "NiRefObject.h"

namespace v1_2_416
{
	class NiObject: public NiRefObject
	{
	public:
		NiObject();
		virtual ~NiObject();

		virtual NiRTTI		*GetType(void);
		virtual void		Unk_02(void);
		virtual void		Unk_03(void);
		virtual void		Unk_04(void);
		virtual void		Unk_05(void);
		virtual void		Unk_06(void);
		virtual void		Unk_07(void);
		virtual void		Unk_08(void);
		virtual void		Unk_09(void);
		virtual void		Unk_0A(void);
		virtual void		Unk_0B(void);
		virtual void		DumpAttributes(NiTArray <char *> * dst);
		virtual void		Unk_0D(void);
		virtual void		Unk_0E(void);
		virtual void		Unk_0F(void);
		virtual void		Unk_10(void);
		virtual void		Unk_11(void);
		virtual void		Unk_12(void);
	};
}