/*	Name:			Sky
**	Description:	This is a container for all the sky objects.
**	Inheritance:	None
**	Size:			104
**	vTable:			00A56E14
**	vTable size:	1
**	Constructor:	00540FD0
**	Includes:		NiNode, TESClimate, TESWeather, Atmosphere, Stars, Sun, Clouds, Moon, Precipitation
*/	

#pragma once

#include "Sun.h"
#include "GameForms.h"
#include "nodes\NiNode.h"

namespace OBGEfork
{
	class NiNode;
	class Atmosphere;
	class Stars;
	class Clouds;
	class Moon;
	class Precipitation;

	class Sky
	{
	public:
		Sky();
		virtual ~Sky();

		static Sky *	GetSingleton(void);
		static Sky *	Singleton;

		void	RefreshClimate(TESClimate * climate, UInt32 unk1);	// pass 1 for unk1 to pick new random weather etc

		v1_2_416::NiNode*		niNode004;						// 004
		v1_2_416::NiNode*		niNode008;						// 008
		TESClimate	* firstClimate;					// 00C
		TESWeather	* firstWeather;					// 010
		UInt32		unk014;							// 014
		TESWeather*	weather018;						// 018
		UInt32		unk01C;							// 01C
		Atmosphere* atmosphere;						// 020
		Stars*		stars;							// 024
		Sun*		sun;							// 028
		Clouds*		clouds;							// 02C
		Moon*		masserMoon;						// 030
		Moon*		secundaMoon;					// 034
		Precipitation* precipitation;				// 038
		UInt32		unk03C[(0x104 - 0x03C) >> 2];	// 03C
	};
}
		
		