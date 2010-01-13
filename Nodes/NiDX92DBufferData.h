/*	Name:			NiDX92DBufferData
**	Description:	Container for a D3D surface.
**	Inheritance:	NiRefObject
**	Size:			14?
**	vTable:			00A8981C
**	vTable size:	10
**	Constructor:	not found
**	Includes:		NiRTTI, Ni2DBufferData
*/	

#pragma once

#include "NiRefObject.h"
#include "MiscNiDataTypes.h"
#include "Ni2DBuffer.h"
#include "D3D9.h"


namespace v1_2_416
{
	class NiDX92DBufferData: public NiRefObject
	{
	public:
		NiDX92DBufferData();
		virtual ~NiDX92DBufferData();
		
		virtual UInt32		GetWidth(void);												// 01
		virtual UInt32		GetHeight(void);											// 02
		virtual void		*GetVar10(void);											// 03
		virtual NiRTTI		*GetRTTI(void);												// 04
		virtual	UInt32		func05(void);												// 05
		virtual	UInt32		func06(void);												// 06
		virtual UInt32		func07(void);												// 07
		virtual UInt32		func08(void);												// 08
		virtual UInt32		func09(void);												// 09
		virtual UInt32		func0A(void);												// 0A
		virtual bool		ReleaseSurface1(void);										// 0B
		virtual bool		GetBufferData(IDirect3DDevice9 *D3DDevice);					// 0C
		virtual bool		SetRenderTarget(IDirect3DDevice9 *D3DDevice, UInt32 index);	// 0D
		virtual bool		SetSurface(IDirect3DDevice9 *D3DDevice);					// 0E
		virtual void		ReleaseSurface2(void);										// 0F

		Ni2DBuffer			*ParentData;												// 08
		IDirect3DSurface9	*surface;													// 0C
		void				*SurfaceData;												// 10	- 0x44 bytes long.
	};
}
		
		