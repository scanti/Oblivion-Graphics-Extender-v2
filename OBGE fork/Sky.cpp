#include "OBGE fork\Sky.h"

namespace OBGEfork
{
#pragma optimize("",off)
	_declspec(naked) Sky*  Sky::GetSingleton(void)
	{
		_asm
		{
			mov eax,0x00542EA0
			jmp eax
		}
	}
#pragma optimize("",on)
}