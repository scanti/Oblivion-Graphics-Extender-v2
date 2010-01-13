/*	Name:			NiDX9RenderState
**	Description:	DX9 specific render state manager.
**	Inheritance:	NiRefObject::NiD3DRenderState::
**	Size:			1148
**	vTable:			00A8A9F4
**	vTable size:	43
**	Constructor:	0077BB00
**	Includes:		
*/	

#pragma once

#include "NiD3DRenderState.h"

namespace v1_2_416
{
	class NiDX9RenderState: public NiD3DRenderState
	{
	public:
		NiDX9RenderState();
		virtual ~NiDX9RenderState();
	
		UInt8							VertexInfoType;					// 1000
		UInt8							pad_1001;						// 1001
		UInt16							pad_1002;						// 1002
		DWORD							FVF;							// 1004
		DWORD							FVFBackUp;						// 1008
		IDirect3DVertexDeclaration9*	VertexDecl;						// 100C
		IDirect3DVertexDeclaration9*	VertexDeclBackUp;				// 1010
		UInt8							SoftwareVertexProcessing;		// 1014
		UInt8		var_1015;		// 1015
		UInt16		var_1016;		// 1016
		UInt32		var_1018;		// 1018
		UInt32		var_101C;		// 101C
		UInt32		var_1020;		// 1020
		UInt32		var_1024;		// 1024
		UInt32		var_1028;		// 1028
		UInt32		var_102C;		// 102C
		UInt32		var_1030;		// 1030
		UInt32		var_1034;		// 1034
		UInt32		var_1038;		// 1038
		UInt32		var_103C;		// 103C
		UInt32		var_1040;		// 1040
		UInt32		var_1044;		// 1044
		UInt32		var_1048;		// 1048
		UInt32		var_104C;		// 104C
		UInt32		var_1050;		// 1050
		UInt32		var_1054;		// 1054
		UInt32		var_1058;		// 1058
		UInt32		var_105C;		// 105C
		UInt32		var_1060;		// 1060
		UInt32		var_1064;		// 1064
		UInt32		var_1068;		// 1068
		UInt32		var_106C;		// 106C
		UInt32		var_1070;		// 1070
		UInt32		var_1074;		// 1074
		UInt32		var_1078;		// 1078
		UInt32		var_107C;		// 107C
		UInt32		var_1080;		// 1080
		UInt32		var_1084;		// 1084
		UInt32		var_1088;		// 1088
		UInt32		var_108C;		// 108C
		UInt32		var_1090;		// 1090
		UInt32		var_1094;		// 1094
		UInt32		var_1098;		// 1098
		UInt32		var_109C;		// 109C
		UInt32		var_10A0;		// 10A0
		UInt32		var_10A4;		// 10A4
		UInt32		var_10A8;		// 10A8
		UInt32		var_10AC;		// 10AC
		UInt32		var_10B0;		// 10B0
		UInt32		var_10B4;		// 10B4
		UInt32		var_10B8;		// 10B8
		UInt32		var_10BC;		// 10BC
		UInt32		var_10C0;		// 10C0
		UInt32		var_10C4;		// 10C4
		UInt32		var_10C8;		// 10C8
		UInt32		var_10CC;		// 10CC
		UInt32		var_10D0;		// 10D0
		UInt32		var_10D4;		// 10D4
		UInt32		var_10D8;		// 10D8
		UInt32		var_10DC;		// 10DC
		UInt32		var_10E0;		// 10E0
		UInt32		var_10E4;		// 10E4
		UInt32		var_10E8;		// 10E8
		UInt32		var_10EC;		// 10EC
		UInt32		var_10F0;		// 10F0
		UInt32		var_10F4;		// 10F4
		UInt32		var_10F8;		// 10F8
		UInt32		var_10FC;		// 10FC
		UInt32		var_1100;		// 1100
		UInt32		var_1104;		// 1104
		UInt32		var_1108;		// 1108
		UInt32		var_110C;		// 110C
		UInt32		var_1110;		// 1110
		UInt32		var_1114;		// 1114
		UInt32		var_1118;		// 1118
		UInt32		var_111C;		// 111C
		UInt32		var_1120;		// 1120
		UInt32		var_1124;		// 1124
		UInt32		var_1128;		// 1128
		UInt32		var_112C;		// 112C
		UInt32		var_1130;		// 1130
		UInt32		var_1134;		// 1134
		UInt32		var_1138;		// 1138
		UInt32		var_113C;		// 113C
		UInt32		var_1140;		// 1140
		UInt32		var_1144;		// 1144
		
	};
}
		
		