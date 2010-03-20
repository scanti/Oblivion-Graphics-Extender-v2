#pragma once

namespace v1_2_416
{

	struct NiRTTI
	{
		const char	* name;
		NiRTTI		* parent;
	};
	
	struct NiColorRGB
	{
		UInt8	r,g,b;
	};
	
	struct NiColorRGBA
	{
		UInt8	r,g,b,a;
	};
	
	struct NiMaterial
	{
		float r,g,b;
	};
	
	struct NiMatrix44
	{
		float	data[4][4];
	};

	struct NiSphere
	{
		float	x, y, z, radius;
	};

	struct NiFrustum
	{
		float	l;			// 00
		float	r;			// 04
		float	t;			// 08
		float	b;			// 0C
		float	n;			// 10
		float	f;			// 14
		UInt8	o;			// 18
	};

	template <typename T>
	struct NiTArray
	{
		void	* _vtbl;	// 00
		T		* data;		// 04
		UInt16	unk08;		// 08 - init'd to size of preallocation
		UInt16	length;		// 0A - init'd to 0
		UInt16	unk0C;		// 0C - init'd to 0
		UInt16	unk0E;		// 0E - init'd to size of preallocation
	};
}