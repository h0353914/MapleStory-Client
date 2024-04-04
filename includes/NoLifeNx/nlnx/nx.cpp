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
#include "nx.hpp"
#include "file.hpp"
#include "node.hpp"

#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>

namespace nl
{
	namespace nx
	{
		std::vector<std::unique_ptr<file>> files;

		bool exists(std::string name)
		{
			return std::ifstream(name).is_open();
		}

		node add_file(std::string name)
		{
			if (!exists(name))
				return {};

			files.emplace_back(new file(name));

			return *files.back();
		}

		node Base, Character, Character_000, Character_Afterimage_000, Character_Face_000, Character_Hair_000, Character_Hair_001, Effect, Effect_001, Effect_020, Etc, Etc_003, Item, Map, Map_Obj_015, Map_Back_014, Map001, Map002, Map2, Mob, Mob001, Mob002, Mob2, Morph, Npc, Quest, Reactor, Skill, Skill001, Skill002, Skill003, Sound, Sound_014, Sound_020, Sound_022, Sound_023, Sound_029, Sound_032, Sound_040, Sound001, Sound002, Sound2, String, TamingMob, UI, UI_000, UI_001, UI_002, UI_003, UI_004, UI_005, UI_006, UI_007, UI_008;

		void load_all()
		{
			if (exists("Base.nx"))
			{
				Base = add_file("Base.nx");
				Character = add_file("Character.nx");
				Character_000 = add_file("WZ/Character/Character_000.nx");
				Character_Afterimage_000 = add_file("WZ/Character/Afterimage/Afterimage_000.nx");
				Character_Face_000 = add_file("WZ/Character/Face/Face_000.nx");
				Character_Hair_000 = add_file("WZ/Character/Hair/Hair_000.nx"); 
				Character_Hair_001 = add_file("WZ/Character/Hair/Hair_001.nx");
				Effect = add_file("Effect.nx");
				Effect_001 = add_file("WZ/Effect/Effect_001.nx");
				Effect_020 = add_file("WZ/Effect/Effect_020.nx");
				Etc = add_file("Etc.nx");
				Etc_003 = add_file("WZ/Etc/Etc_003.nx");
				Item = add_file("Item.nx");
				Map = add_file("Map.nx");
				Map_Back_014 = add_file("WZ/Map/Back/Back_014.nx");
				Map_Obj_015 = add_file("WZ/Map/Obj/Obj_015.nx");
				Map001 = add_file("Map001.nx");
				Map002 = add_file("Map002.nx");
				Map2 = add_file("Map2.nx");
				Mob = add_file("Mob.nx");
				Mob001 = add_file("Mob001.nx");
				Mob002 = add_file("Mob002.nx");
				Mob2 = add_file("Mob2.nx");
				Morph = add_file("Morph.nx");
				Npc = add_file("Npc.nx");
				Quest = add_file("Quest.nx");
				Reactor = add_file("Reactor.nx");
				Skill = add_file("Skill.nx");
				Skill001 = add_file("Skill001.nx");
				Skill002 = add_file("Skill002.nx");
				Skill003 = add_file("Skill003.nx");
				Sound = add_file("Sound.nx");
				Sound_014 = add_file("WZ/Sound/Sound_014.nx");
				Sound_020 = add_file("WZ/Sound/Sound_020.nx");
				Sound_022 = add_file("WZ/Sound/Sound_022.nx"); 
				Sound_023 = add_file("WZ/Sound/Sound_023.nx"); 
				Sound_029 = add_file("WZ/Sound/Sound_029.nx");
				Sound_032 = add_file("WZ/Sound/Sound_032.nx");
				Sound_040 = add_file("WZ/Sound/Sound_040.nx");
				Sound001 = add_file("Sound001.nx");
				Sound002 = add_file("Sound002.nx");
				Sound2 = add_file("Sound2.nx");
				String = add_file("String.nx");
				TamingMob = add_file("TamingMob.nx");
				UI = add_file("UI.nx");
				UI_000 = add_file("WZ/UI/UI_000.nx");
				UI_001 = add_file("WZ/UI/UI_001.nx");
				UI_002 = add_file("WZ/UI/UI_002.nx");
				UI_003 = add_file("WZ/UI/UI_003.nx");
				UI_004 = add_file("WZ/UI/UI_004.nx");
				UI_005 = add_file("WZ/UI/UI_005.nx");
				UI_006 = add_file("WZ/UI/UI_006.nx");
				UI_007 = add_file("WZ/UI/UI_007.nx");
				UI_008 = add_file("WZ/UI/UI_008.nx");

			}
			else if (exists("Data.nx"))
			{
				Base = add_file("Data.nx");
				Character = Base["Character"];
				Character_000 = Base["Character_000"];
				Character_Afterimage_000 = Base["Character_Afterimage_000"];
				Character_Face_000 = Base["Character_Face_000"];
				Character_Hair_000 = Base["Character_Hair_000"];
				Character_Hair_001 = Base["Character_Hair_001"];
				Effect = Base["Effect"];
				Effect_001 = Base["Effect_001"];
				Effect_020 = Base["Effect_020"];
				Etc = Base["Etc"];
				Etc_003 = Base["Etc_003"];
				Item = Base["Item"];
				Map = Base["Map"];
				Map_Back_014 = Base["Back_014"];
				Map_Obj_015 = Base["Map_Obj_015"];
				Map001 = Base["Map001"];
				Map002 = Base["Map002"];
				Map2 = Base["Map2"];
				Mob = Base["Mob"];
				Mob001 = Base["Mob001"];
				Mob002 = Base["Mob002"];
				Mob2 = Base["Mob2"];
				Morph = Base["Morph"];
				Npc = Base["Npc"];
				Quest = Base["Quest"];
				Reactor = Base["Reactor"];
				Skill = Base["Skill"];
				Skill001 = Base["Skill001"];
				Skill002 = Base["Skill002"];
				Skill003 = Base["Skill003"];
				Sound = Base["Sound"];
				Sound_014 = Base["Sound_014"];
				Sound_020 = Base["Sound_020"];
				Sound_022 = Base["Sound_022"];
				Sound_023 = Base["Sound_023"];
				Sound_029 = Base["Sound_029"];
				Sound_032 = Base["Sound_032"];
				Sound_040 = Base["Sound_040"];
				Sound001 = Base["Sound001"];
				Sound002 = Base["Sound002"];
				Sound2 = Base["Sound2"];
				String = Base["String"];
				TamingMob = Base["TamingMob"];
				UI = Base["UI"];
				UI_000 = Base["UI_000"];
				UI_001 = Base["UI_001"];
				UI_001 = Base["UI_002"];
				UI_001 = Base["UI_003"];				
				UI_001 = Base["UI_004"];				
				UI_001 = Base["UI_005"];				
				UI_001 = Base["UI_006"];				
				UI_001 = Base["UI_007"];				
				UI_001 = Base["UI_008"];
			}
			else
			{
				throw std::runtime_error("Failed to locate nx files.");
			}
		}
	}
}