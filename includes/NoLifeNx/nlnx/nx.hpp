//////////////////////////////////////////////////////////////////////////////
// NoLifeNx - Part of the NoLifeStory project                               //
// Copyright © 2013 Peter Atashian                                          //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "nxfwd.hpp"

namespace nl
{
	namespace nx
	{
		// Pre-defined nodes to access standard MapleStory style data
		// Make sure you called load_all first
		extern node Base, Character, Character_000, Character_Afterimage_000, Character_Face_000, Character_Hair_000, Character_Hair_001, Effect, Effect_001, Effect_020, Etc, Etc_003, Item, Map, Map_Obj_015, Map_Back_014, Map001, Map002, Map2, Mob, Mob001, Mob002, Mob2, Morph, Npc, Quest, Reactor, Skill, Skill001, Skill002, Skill003, Sound, Sound_014, Sound_020, Sound_022, Sound_023, Sound_029, Sound_032, Sound_040, Sound001, Sound002, Sound2, String, TamingMob, UI, UI_000, UI_001, UI_002, UI_003, UI_004, UI_005, UI_006, UI_007, UI_008;

		// Loads the pre-defined nodes from a standard setup of nx files for MapleStory
		// Only call this function once
		void load_all();
	}
}