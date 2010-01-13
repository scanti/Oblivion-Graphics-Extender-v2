/*	Name:			NiDX9TextureBufferData
**	Description:	Contains the D3D surface data for a texture
**	Inheritance:	NiRefObject::NiDX92DBufferData
**	Size:			0x18
**	vTable:			0x00A898E4
**	vTable size:	0x10
**	Constructor:	0x0076D9B0
**	Includes:		none
*/	

#pragma once

#include "NiDX92DBufferData.h"

namespace v1_2_416
{
	class NiDX9TextureBufferData:public NiDX92DBufferData
	{
	public:

		NiDX9TextureBufferData();
		virtual ~NiDX9TextureBufferData();
		
		void	*UnkD3DData;			// 14
	};
}
		
		