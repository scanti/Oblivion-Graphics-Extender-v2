#include "NiAVObject.h"

namespace v1_2_416
{
	#pragma optimize("",off)

	NiNode _declspec(naked) *NiAVObject::FindProperty(char *PropertyName)
	{
		_asm
		{
			mov eax,0x0006FF9C0
			jmp eax
		}
	};
	
	#pragma optimize("",on)
}