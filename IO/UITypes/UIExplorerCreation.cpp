//////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015-2016 Daniel Allendorf                                   //
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
#include "UIExplorerCreation.h"
#include "UIRaceSelect.h"
#include "UILoginNotice.h"
#include "UICharSelect.h"

#include "../UI.h"
#include "../Configuration.h"

#include "../Components/MapleButton.h"
#include "../Data/ItemData.h"
#include "../Audio/Audio.h"

#include "../Net/Packets/CharCreationPackets.h"

#include "nlnx/nx.hpp"

namespace jrc
{
	UIExplorerCreation::UIExplorerCreation(uint8_t selected) : UIElement(Point<int16_t>(0, 0), Point<int16_t>(800, 600)), selected_class(selected)
	{
		gender = false;
		charSet = false;
		named = false;

		std::string version_text = Configuration::get().get_version();
		version = Text(Text::Font::A11M, Text::Alignment::LEFT, Text::Color::LEMONGRASS, "Ver. " + version_text);

		nl::node Login = nl::nx::ui["Login.img"];
		nl::node Common = Login["Common"];
		nl::node CustomizeChar = Login["CustomizeChar"];
		nl::node back = nl::nx::map["Back"]["login.img"]["back"];

		sky = back["2"];
		cloud = back["27"];

		if (selected_class == Classes::ARAN)
		{
			nl::node customizeCharAran = CustomizeChar["2000"];
			nl::node board = customizeCharAran["board"];
			nl::node genderSelect = customizeCharAran["genderSelect"];

			sprites.emplace_back(back["33"], Point<int16_t>(256, 289)); // From v203.3
			sprites.emplace_back(back["34"], Point<int16_t>(587, 147)); // From v203.3
			sprites_gender_select.emplace_back(board["genderTop"], Point<int16_t>(491, 158));
			sprites_gender_select.emplace_back(board["boardMid"], Point<int16_t>(491, 210));
			sprites_gender_select.emplace_back(board["boardBottom"], Point<int16_t>(491, 303));

			sprites_lookboard.emplace_back(customizeCharAran["charSet"], Point<int16_t>(473, 93));

			for (size_t i = 0; i <= 6; i++)
				sprites_lookboard.emplace_back(customizeCharAran["avatarSel"][i]["normal"], Point<int16_t>(504, 177 + (i * 18)));

			buttons[Buttons::BT_CHARC_GENDER_M] = std::make_unique<MapleButton>(genderSelect["male"], Point<int16_t>(439, 96));
			buttons[Buttons::BT_CHARC_GEMDER_F] = std::make_unique<MapleButton>(genderSelect["female"], Point<int16_t>(437, 96));

			buttons[Buttons::BT_CHARC_SKINL] = std::make_unique<MapleButton>(customizeCharAran["BtLeft"], Point<int16_t>(562, 177 + (2 * 18)));
			buttons[Buttons::BT_CHARC_SKINR] = std::make_unique<MapleButton>(customizeCharAran["BtRight"], Point<int16_t>(699, 177 + (2 * 18)));
			buttons[Buttons::BT_CHARC_SKINL]->set_active(false);
			buttons[Buttons::BT_CHARC_SKINR]->set_active(false);

			buttons[Buttons::BT_CHARC_OK] = std::make_unique<MapleButton>(customizeCharAran["BtYes"], Point<int16_t>(520, 387));
			buttons[Buttons::BT_CHARC_CANCEL] = std::make_unique<MapleButton>(customizeCharAran["BtNo"], Point<int16_t>(594, 387));

			nameboard = customizeCharAran["charName"];
			namechar = Textfield(Text::Font::A13M, Text::Alignment::LEFT, Text::Color::WHITE, Rectangle<int16_t>(Point<int16_t>(524, 186), Point<int16_t>(630, 243)), 12);
		}
		else if (selected_class == Classes::EXPLORER)
		{
			nl::node customizeCharExplorers = CustomizeChar["000"];
			nl::node board = customizeCharExplorers["board"];
			nl::node genderSelect = customizeCharExplorers["genderSelect"];

			sprites.emplace_back(back["14"], Point<int16_t>(250, 292)); // From v203.3
			sprites_gender_select.emplace_back(board["genderTop"], Point<int16_t>(486, 85));
			sprites_gender_select.emplace_back(board["boardMid"], Point<int16_t>(486, 199));
			sprites_gender_select.emplace_back(board["boardBottom"], Point<int16_t>(486, 319));

			sprites_lookboard.emplace_back(customizeCharExplorers["charSet"], Point<int16_t>(486, 85));

			for (size_t i = 0; i <= 5; i++)
			{
				size_t f = i;

				if (i >= 2)
					f++;

				sprites_lookboard.emplace_back(customizeCharExplorers["avatarSel"][i]["normal"], Point<int16_t>(497, 187 + (f * 18)));
			}

			buttons[Buttons::BT_CHARC_GENDER_M] = std::make_unique<MapleButton>(genderSelect["male"], Point<int16_t>(487, 99));
			buttons[Buttons::BT_CHARC_GEMDER_F] = std::make_unique<MapleButton>(genderSelect["female"], Point<int16_t>(485, 99));

			buttons[Buttons::BT_CHARC_FACEL] = std::make_unique<MapleButton>(customizeCharExplorers["BtLeft"], Point<int16_t>(552, 188 + (0 * 18)));
			buttons[Buttons::BT_CHARC_FACER] = std::make_unique<MapleButton>(customizeCharExplorers["BtRight"], Point<int16_t>(684, 188 + (0 * 18)));
			buttons[Buttons::BT_CHARC_HAIRL] = std::make_unique<MapleButton>(customizeCharExplorers["BtLeft"], Point<int16_t>(552, 188 + (1 * 18)));
			buttons[Buttons::BT_CHARC_HAIRR] = std::make_unique<MapleButton>(customizeCharExplorers["BtRight"], Point<int16_t>(684, 188 + (1 * 18)));
			buttons[Buttons::BT_CHARC_SKINL] = std::make_unique<MapleButton>(customizeCharExplorers["BtLeft"], Point<int16_t>(552, 188 + (3 * 18)));
			buttons[Buttons::BT_CHARC_SKINR] = std::make_unique<MapleButton>(customizeCharExplorers["BtRight"], Point<int16_t>(684, 188 + (3 * 18)));
			buttons[Buttons::BT_CHARC_TOPL] = std::make_unique<MapleButton>(customizeCharExplorers["BtLeft"], Point<int16_t>(552, 188 + (4 * 18)));
			buttons[Buttons::BT_CHARC_TOPR] = std::make_unique<MapleButton>(customizeCharExplorers["BtRight"], Point<int16_t>(684, 188 + (4 * 18)));
			buttons[Buttons::BT_CHARC_SHOESL] = std::make_unique<MapleButton>(customizeCharExplorers["BtLeft"], Point<int16_t>(552, 188 + (5 * 18)));
			buttons[Buttons::BT_CHARC_SHOESR] = std::make_unique<MapleButton>(customizeCharExplorers["BtRight"], Point<int16_t>(684, 188 + (5 * 18)));
			buttons[Buttons::BT_CHARC_WEPL] = std::make_unique<MapleButton>(customizeCharExplorers["BtLeft"], Point<int16_t>(552, 188 + (6 * 18)));
			buttons[Buttons::BT_CHARC_WEPR] = std::make_unique<MapleButton>(customizeCharExplorers["BtRight"], Point<int16_t>(684, 188 + (6 * 18)));

			for (size_t i = 0; i <= 7; i++)
			{
				buttons[Buttons::BT_CHARC_HAIRC0 + i] = std::make_unique<MapleButton>(customizeCharExplorers["hairSelect"][i], Point<int16_t>(549 + (i * 15), 224));
				buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(false);
			}

			buttons[Buttons::BT_CHARC_FACEL]->set_active(false);
			buttons[Buttons::BT_CHARC_FACER]->set_active(false);
			buttons[Buttons::BT_CHARC_HAIRL]->set_active(false);
			buttons[Buttons::BT_CHARC_HAIRR]->set_active(false);
			buttons[Buttons::BT_CHARC_SKINL]->set_active(false);
			buttons[Buttons::BT_CHARC_SKINR]->set_active(false);
			buttons[Buttons::BT_CHARC_TOPL]->set_active(false);
			buttons[Buttons::BT_CHARC_TOPR]->set_active(false);
			buttons[Buttons::BT_CHARC_SHOESL]->set_active(false);
			buttons[Buttons::BT_CHARC_SHOESR]->set_active(false);
			buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
			buttons[Buttons::BT_CHARC_WEPR]->set_active(false);

			buttons[Buttons::BT_CHARC_OK] = std::make_unique<MapleButton>(customizeCharExplorers["BtYes"], Point<int16_t>(514, 384));
			buttons[Buttons::BT_CHARC_CANCEL] = std::make_unique<MapleButton>(customizeCharExplorers["BtNo"], Point<int16_t>(590, 384));

			nameboard = customizeCharExplorers["charName"];
			namechar = Textfield(Text::Font::A13M, Text::Alignment::LEFT, Text::Color::WHITE, Rectangle<int16_t>(Point<int16_t>(522, 185), Point<int16_t>(630, 243)), 12);
		}
		else if (selected_class == Classes::CYGNUSKNIGHTS)
		{
			nl::node customizeCharCygnus = CustomizeChar["1000"];
			nl::node board = customizeCharCygnus["board"];
			nl::node genderSelect = customizeCharCygnus["genderSelect"];

			sprites.emplace_back(back["46"], Point<int16_t>(400, 290)); // From v203.3
			sprites_gender_select.emplace_back(board["genderTop"], Point<int16_t>(423, 94));
			sprites_gender_select.emplace_back(board["boardMid"], Point<int16_t>(423, 212));
			sprites_gender_select.emplace_back(board["boardBottom"], Point<int16_t>(423, 338));

			sprites_lookboard.emplace_back(board["avatarTop"], Point<int16_t>(415, 79));
			sprites_lookboard.emplace_back(board["boardMid"], Point<int16_t>(415, 197));
			sprites_lookboard.emplace_back(board["boardBottom"], Point<int16_t>(415, 341));

			for (size_t i = 0; i <= 6; i++)
			{
				int16_t y = 0;

				if (i == 3)
					y = 2;
				else if (i == 4)
					y = 20;

				sprites_lookboard.emplace_back(customizeCharCygnus["avatarSel"][i]["normal"], Point<int16_t>(416, 88 + y));
			}

			buttons[Buttons::BT_CHARC_GENDER_M] = std::make_unique<MapleButton>(genderSelect["male"], Point<int16_t>(425, 97));
			buttons[Buttons::BT_CHARC_GEMDER_F] = std::make_unique<MapleButton>(genderSelect["female"], Point<int16_t>(423, 97));

			buttons[Buttons::BT_CHARC_SKINL] = std::make_unique<MapleButton>(customizeCharCygnus["BtLeft"], Point<int16_t>(551, 177 + (4 * 18)));
			buttons[Buttons::BT_CHARC_SKINR] = std::make_unique<MapleButton>(customizeCharCygnus["BtRight"], Point<int16_t>(664, 177 + (4 * 18)));
			buttons[Buttons::BT_CHARC_WEPL] = std::make_unique<MapleButton>(customizeCharCygnus["BtLeft"], Point<int16_t>(551, 177 + (8 * 18)));
			buttons[Buttons::BT_CHARC_WEPR] = std::make_unique<MapleButton>(customizeCharCygnus["BtRight"], Point<int16_t>(664, 177 + (8 * 18)));

			for (size_t i = 0; i <= 7; i++)
			{
				buttons[Buttons::BT_CHARC_HAIRC0 + i] = std::make_unique<MapleButton>(customizeCharCygnus["hairSelect"][i], Point<int16_t>(553 + (i * 15), 228));
				buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(false);
			}

			buttons[Buttons::BT_CHARC_SKINL]->set_active(false);
			buttons[Buttons::BT_CHARC_SKINR]->set_active(false);
			buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
			buttons[Buttons::BT_CHARC_WEPR]->set_active(false);

			buttons[Buttons::BT_CHARC_OK] = std::make_unique<MapleButton>(customizeCharCygnus["BtYes"], Point<int16_t>(510, 386));
			buttons[Buttons::BT_CHARC_CANCEL] = std::make_unique<MapleButton>(customizeCharCygnus["BtNo"], Point<int16_t>(615, 386));

			nameboard = customizeCharCygnus["charName"];
			namechar = Textfield(Text::Font::A13M, Text::Alignment::LEFT, Text::Color::BLACK, Rectangle<int16_t>(Point<int16_t>(538, 200), Point<int16_t>(630, 243)), 12);
		}
		else
		{
			button_pressed(Buttons::BT_BACK);

			return;
		}

		sprites.emplace_back(Common["frame"], Point<int16_t>(399, 289));
		sprites.emplace_back(Common["step"]["3"], Point<int16_t>(40, -10));

		buttons[Buttons::BT_BACK] = std::make_unique<MapleButton>(Login["Common"]["BtStart"], Point<int16_t>(0, 505));

		namechar.set_state(Textfield::DISABLED);

		namechar.set_enter_callback(
			[&](std::string)
			{
				button_pressed(Buttons::BT_CHARC_OK);
			}
		);

		namechar.set_key_callback(
			KeyAction::Id::ESCAPE,
			[&]()
			{
				button_pressed(Buttons::BT_CHARC_CANCEL);
			}
		);

		facename = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		hairname = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		haircname = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		bodyname = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		topname = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		botname = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		shoename = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		wepname = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);
		gendername = Text(Text::Font::A11M, Text::Alignment::CENTER, Text::Color::BLACK);

		nl::node mkinfo = nl::nx::etc["MakeCharInfo.img"]["Info"];

		for (size_t i = 0; i < 2; i++)
		{
			bool f;
			nl::node CharGender;

			if (i == 0)
			{
				f = true;
				CharGender = mkinfo["CharFemale"];
			}
			else
			{
				f = false;
				CharGender = mkinfo["CharMale"];
			}

			for (auto node : CharGender)
			{
				int num = stoi(node.name());

				for (auto idnode : node)
				{
					int32_t value = idnode;

					switch (num)
					{
					case 0:
						faces[f].push_back(value);
						break;
					case 1:
						hairs[f].push_back(value);
						break;
					case 2:
						haircolors[f].push_back(static_cast<uint8_t>(value));
						break;
					case 3:
						skins[f].push_back(static_cast<uint8_t>(value));
						break;
					case 4:
						tops[f].push_back(value);
						break;
					case 5:
						bots[f].push_back(value);
						break;
					case 6:
						shoes[f].push_back(value);
						break;
					case 7:
						weapons[f].push_back(value);
						break;
					}
				}
			}
		}

		female = false;
		randomize_look();

		newchar.set_direction(true);

		cloudfx = 200.0f;
	}

	void UIExplorerCreation::draw(float inter) const
	{
		for (size_t i = 0; i < 2; i++)
			for (size_t k = 0; k < 800; k += sky.width())
				sky.draw(Point<int16_t>(k, (400 * i) - 100));

		int16_t cloudx = static_cast<int16_t>(cloudfx) % 800;
		cloud.draw(Point<int16_t>(cloudx - cloud.width(), 300));
		cloud.draw(Point<int16_t>(cloudx, 300));
		cloud.draw(Point<int16_t>(cloudx + cloud.width(), 300));

		if (!gender)
		{
			if (selected_class == Classes::ARAN || selected_class == Classes::EXPLORER)
			{
				for (size_t i = 0; i < sprites_gender_select.size(); i++)
				{
					if (i == 1)
					{
						for (size_t f = 0; f <= 4; f++)
							sprites_gender_select[i].draw(position + Point<int16_t>(0, 24 * f), inter);
					}
					else
					{
						sprites_gender_select[i].draw(position, inter);
					}
				}

				UIElement::draw(inter);

				newchar.draw(Point<int16_t>(394, 329), inter);
			}
			else if (selected_class == Classes::CYGNUSKNIGHTS)
			{
				UIElement::draw_sprites(inter);

				for (size_t i = 0; i < sprites_gender_select.size(); i++)
				{
					if (i == 1)
					{
						for (size_t f = 0; f <= 6; f++)
							sprites_gender_select[i].draw(position + Point<int16_t>(0, 18 * f), inter);
					}
					else
					{
						sprites_gender_select[i].draw(position, inter);
					}
				}

				UIElement::draw_buttons(inter);

				newchar.draw(Point<int16_t>(394, 329), inter);
			}
		}
		else
		{
			if (!charSet)
			{
				UIElement::draw_sprites(inter);

				if (selected_class == Classes::ARAN)
				{
					for (auto& sprite : sprites_lookboard)
						sprite.draw(position, inter);

					facename.draw(Point<int16_t>(643, 173 + (0 * 18)));
					hairname.draw(Point<int16_t>(643, 173 + (1 * 18)));
					bodyname.draw(Point<int16_t>(643, 173 + (2 * 18)));
					topname.draw(Point<int16_t>(643, 173 + (3 * 18)));
					botname.draw(Point<int16_t>(643, 173 + (4 * 18)));
					shoename.draw(Point<int16_t>(643, 173 + (5 * 18)));
					wepname.draw(Point<int16_t>(643, 173 + (6 * 18)));
				}
				else if (selected_class == Classes::EXPLORER)
				{
					for (auto& sprite : sprites_lookboard)
						sprite.draw(position, inter);

					facename.draw(Point<int16_t>(623, 183 + (0 * 18)));
					hairname.draw(Point<int16_t>(623, 183 + (1 * 18)));
					bodyname.draw(Point<int16_t>(623, 183 + (3 * 18)));
					topname.draw(Point<int16_t>(623, 183 + (4 * 18)));
					shoename.draw(Point<int16_t>(623, 183 + (5 * 18)));
					wepname.draw(Point<int16_t>(623, 183 + (6 * 18)));
				}
				else if (selected_class == Classes::CYGNUSKNIGHTS)
				{
					for (size_t i = 0; i < sprites_lookboard.size(); i++)
					{
						if (i == 1)
						{
							for (size_t f = 0; f <= 7; f++)
								sprites_lookboard[i].draw(position + Point<int16_t>(0, 18 * f), inter);
						}
						else
						{
							sprites_lookboard[i].draw(position, inter);
						}
					}

					facename.draw(Point<int16_t>(620, 208 + (-1 * 18)));
					hairname.draw(Point<int16_t>(620, 208 + (0 * 18)));
					bodyname.draw(Point<int16_t>(620, 208 + (2 * 18)));
					topname.draw(Point<int16_t>(620, 208 + (3 * 18)));
					botname.draw(Point<int16_t>(620, 208 + (4 * 18)));
					shoename.draw(Point<int16_t>(620, 208 + (5 * 18)));
					wepname.draw(Point<int16_t>(620, 208 + (6 * 18)));
				}

				newchar.draw(Point<int16_t>(394, 329), inter);

				UIElement::draw_buttons(inter);
			}
			else
			{
				if (!named)
				{
					UIElement::draw_sprites(inter);

					if (selected_class == Classes::ARAN)
						nameboard.draw(Point<int16_t>(489, 96));
					else if (selected_class == Classes::EXPLORER)
						nameboard.draw(Point<int16_t>(486, 85));
					else if (selected_class == Classes::CYGNUSKNIGHTS)
						nameboard.draw(Point<int16_t>(423, 94));

					namechar.draw(position);
					newchar.draw(Point<int16_t>(394, 329), inter);

					UIElement::draw_buttons(inter);
				}
				else
				{
					UIElement::draw_sprites(inter);

					if (selected_class == Classes::ARAN)
						nameboard.draw(Point<int16_t>(489, 96));
					else if (selected_class == Classes::EXPLORER)
						nameboard.draw(Point<int16_t>(486, 85));
					else if (selected_class == Classes::CYGNUSKNIGHTS)
						nameboard.draw(Point<int16_t>(423, 94));

					UIElement::draw_buttons(inter);

					for (auto& sprite : sprites_keytype)
						sprite.draw(position, inter);
				}
			}
		}

		version.draw(position + Point<int16_t>(707, -9));
	}

	void UIExplorerCreation::update()
	{
		if (!gender)
		{
			for (auto& sprite : sprites_gender_select)
				sprite.update();

			newchar.update(Constants::TIMESTEP);
		}
		else
		{
			if (!charSet)
			{
				for (auto& sprite : sprites_lookboard)
					sprite.update();

				newchar.update(Constants::TIMESTEP);
			}
			else
			{
				if (!named)
				{
					namechar.update(position);
					newchar.update(Constants::TIMESTEP);
				}
				else
				{
					for (auto& sprite : sprites_keytype)
						sprite.update();

					namechar.set_state(Textfield::State::DISABLED);
				}
			}
		}

		UIElement::update();

		cloudfx += 0.25f;
	}

	Cursor::State UIExplorerCreation::send_cursor(bool clicked, Point<int16_t> cursorpos)
	{
		if (namechar.get_bounds().contains(cursorpos))
		{
			if (clicked)
			{
				if (namechar.get_state() == Textfield::State::NORMAL)
					namechar.set_state(Textfield::State::FOCUSED);

				return Cursor::State::CLICKING;
			}
			else
			{
				return Cursor::State::IDLE;
			}
		}

		return UIElement::send_cursor(clicked, cursorpos);
	}

	void UIExplorerCreation::send_key(int32_t keycode, bool pressed)
	{
		if (pressed)
		{
			if (keycode == KeyAction::Id::ESCAPE)
				button_pressed(Buttons::BT_CHARC_CANCEL);
			else if (keycode == KeyAction::Id::RETURN)
				button_pressed(Buttons::BT_CHARC_OK);
		}
	}

	void UIExplorerCreation::send_naming_result(bool nameused)
	{
		if (!named)
		{
			if (!nameused)
			{
				named = true;

				std::string cname = namechar.get_text();
				int32_t cface = faces[female][face];
				int32_t chair = hairs[female][hair];
				uint8_t chairc = haircolors[female][haircolor];
				uint8_t cskin = skins[female][skin];
				int32_t ctop = tops[female][top];
				int32_t cbot = bots[female][bot];
				int32_t cshoe = shoes[female][shoe];
				int32_t cwep = weapons[female][weapon];

				int16_t cjob = -1;

				if (selected_class == Classes::CYGNUSKNIGHTS)
					cjob = 0;
				else if (selected_class == Classes::EXPLORER)
					cjob = 1;
				else if (selected_class == Classes::ARAN)
					cjob = 2;

				if (cjob != -1)
				{
					CreateCharPacket(cname, cjob, cface, chair, chairc, cskin, ctop, cbot, cshoe, cwep, female).dispatch();

					auto onok = [&](bool alternate)
					{
						Sound(Sound::Name::SCROLLUP).play();

						UI::get().remove(UIElement::Type::LOGINNOTICE_CONFIRM);
						UI::get().remove(UIElement::Type::LOGINNOTICE);
						UI::get().remove(UIElement::Type::CLASSCREATION);
						UI::get().remove(UIElement::Type::CHARCREATION);

						if (auto charselect = UI::get().get_element<UICharSelect>())
							charselect->post_add_character();
					};

					UI::get().emplace<UIKeySelect>(onok, true);
				}
			}
			else
			{
				auto onok = [&]()
				{
					namechar.set_state(Textfield::State::FOCUSED);

					buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::NORMAL);
					buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::NORMAL);
				};

				UI::get().emplace<UILoginNotice>(UILoginNotice::Message::NAME_IN_USE, onok);
			}
		}
	}

	Button::State UIExplorerCreation::button_pressed(uint16_t buttonid)
	{
		switch (buttonid)
		{
		case Buttons::BT_CHARC_OK:
			if (!gender)
			{
				gender = true;

				buttons[Buttons::BT_CHARC_GENDER_M]->set_active(false);
				buttons[Buttons::BT_CHARC_GEMDER_F]->set_active(false);

				buttons[Buttons::BT_CHARC_SKINL]->set_active(true);
				buttons[Buttons::BT_CHARC_SKINR]->set_active(true);

				if (selected_class == Classes::ARAN)
				{
					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(533, 358));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(607, 358));
				}
				else if (selected_class == Classes::EXPLORER)
				{
					buttons[Buttons::BT_CHARC_FACEL]->set_active(true);
					buttons[Buttons::BT_CHARC_FACER]->set_active(true);
					buttons[Buttons::BT_CHARC_HAIRL]->set_active(true);
					buttons[Buttons::BT_CHARC_HAIRR]->set_active(true);
					buttons[Buttons::BT_CHARC_TOPL]->set_active(true);
					buttons[Buttons::BT_CHARC_TOPR]->set_active(true);
					buttons[Buttons::BT_CHARC_SHOESL]->set_active(true);
					buttons[Buttons::BT_CHARC_SHOESR]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPL]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPR]->set_active(true);

					for (size_t i = 0; i <= 7; i++)
						buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(true);

					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(523, 415));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(597, 415));
				}
				else if (selected_class == Classes::CYGNUSKNIGHTS)
				{
					buttons[Buttons::BT_CHARC_WEPL]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPR]->set_active(true);

					for (size_t i = 0; i <= 7; i++)
						buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(true);

					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(502, 371));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(607, 371));
				}

				return Button::State::NORMAL;
			}
			else
			{
				if (!charSet)
				{
					charSet = true;

					buttons[Buttons::BT_CHARC_SKINL]->set_active(false);
					buttons[Buttons::BT_CHARC_SKINR]->set_active(false);

					if (selected_class == Classes::ARAN)
					{
						buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(523, 233));
						buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(597, 233));
					}
					else if (selected_class == Classes::EXPLORER)
					{
						buttons[Buttons::BT_CHARC_FACEL]->set_active(false);
						buttons[Buttons::BT_CHARC_FACER]->set_active(false);
						buttons[Buttons::BT_CHARC_HAIRL]->set_active(false);
						buttons[Buttons::BT_CHARC_HAIRR]->set_active(false);
						buttons[Buttons::BT_CHARC_TOPL]->set_active(false);
						buttons[Buttons::BT_CHARC_TOPR]->set_active(false);
						buttons[Buttons::BT_CHARC_SHOESL]->set_active(false);
						buttons[Buttons::BT_CHARC_SHOESR]->set_active(false);
						buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
						buttons[Buttons::BT_CHARC_WEPR]->set_active(false);

						for (size_t i = 0; i <= 7; i++)
							buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(false);

						buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(513, 263));
						buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(587, 263));
					}
					else if (selected_class == Classes::CYGNUSKNIGHTS)
					{
						buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
						buttons[Buttons::BT_CHARC_WEPR]->set_active(false);

						for (size_t i = 0; i <= 7; i++)
							buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(false);

						buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(510, 279));
						buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(615, 279));
					}

					namechar.set_state(Textfield::State::FOCUSED);

					return Button::State::NORMAL;
				}
				else
				{
					if (!named)
					{
						std::string name = namechar.get_text();

						if (name.size() <= 0)
						{
							return Button::State::NORMAL;
						}
						else if (name.size() >= 4)
						{
							namechar.set_state(Textfield::State::DISABLED);

							buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::DISABLED);
							buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::DISABLED);

							NameCharPacket(name).dispatch();

							return Button::State::IDENTITY;
						}
						else
						{
							namechar.set_state(Textfield::State::DISABLED);

							buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::DISABLED);
							buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::DISABLED);

							std::function<void()> okhandler = [&]()
							{
								namechar.set_state(Textfield::State::FOCUSED);

								buttons[Buttons::BT_CHARC_OK]->set_state(Button::State::NORMAL);
								buttons[Buttons::BT_CHARC_CANCEL]->set_state(Button::State::NORMAL);
							};

							UI::get().emplace<UILoginNotice>(UILoginNotice::Message::ILLEGAL_NAME, okhandler);

							return Button::State::IDENTITY;
						}
					}
					else
					{
						return Button::State::NORMAL;
					}
				}
			}
		case BT_BACK:
			Sound(Sound::Name::SCROLLUP).play();

			UI::get().remove(UIElement::Type::CLASSCREATION);
			UI::get().emplace<UIRaceSelect>();

			return Button::State::NORMAL;
		case Buttons::BT_CHARC_CANCEL:
			if (charSet)
			{
				charSet = false;

				buttons[Buttons::BT_CHARC_SKINL]->set_active(true);
				buttons[Buttons::BT_CHARC_SKINR]->set_active(true);

				if (selected_class == Classes::ARAN)
				{
					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(533, 358));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(607, 358));
				}
				else if (selected_class == Classes::EXPLORER)
				{
					buttons[Buttons::BT_CHARC_FACEL]->set_active(true);
					buttons[Buttons::BT_CHARC_FACER]->set_active(true);
					buttons[Buttons::BT_CHARC_HAIRL]->set_active(true);
					buttons[Buttons::BT_CHARC_HAIRR]->set_active(true);
					buttons[Buttons::BT_CHARC_TOPL]->set_active(true);
					buttons[Buttons::BT_CHARC_TOPR]->set_active(true);
					buttons[Buttons::BT_CHARC_SHOESL]->set_active(true);
					buttons[Buttons::BT_CHARC_SHOESR]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPL]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPR]->set_active(true);

					for (size_t i = 0; i <= 7; i++)
						buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(true);

					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(523, 415));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(597, 415));
				}
				else if (selected_class == Classes::CYGNUSKNIGHTS)
				{
					buttons[Buttons::BT_CHARC_WEPL]->set_active(true);
					buttons[Buttons::BT_CHARC_WEPR]->set_active(true);

					for (size_t i = 0; i <= 7; i++)
						buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(true);

					buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(502, 371));
					buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(607, 371));
				}

				namechar.set_state(Textfield::State::DISABLED);

				return Button::State::NORMAL;
			}
			else
			{
				if (gender)
				{
					gender = false;

					buttons[Buttons::BT_CHARC_GENDER_M]->set_active(true);
					buttons[Buttons::BT_CHARC_GEMDER_F]->set_active(true);

					buttons[Buttons::BT_CHARC_SKINL]->set_active(false);
					buttons[Buttons::BT_CHARC_SKINR]->set_active(false);

					if (selected_class == Classes::ARAN)
					{
						buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(520, 387));
						buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(594, 387));
					}
					else if (selected_class == Classes::EXPLORER)
					{
						buttons[Buttons::BT_CHARC_FACEL]->set_active(false);
						buttons[Buttons::BT_CHARC_FACER]->set_active(false);
						buttons[Buttons::BT_CHARC_HAIRL]->set_active(false);
						buttons[Buttons::BT_CHARC_HAIRR]->set_active(false);
						buttons[Buttons::BT_CHARC_TOPL]->set_active(false);
						buttons[Buttons::BT_CHARC_TOPR]->set_active(false);
						buttons[Buttons::BT_CHARC_SHOESL]->set_active(false);
						buttons[Buttons::BT_CHARC_SHOESR]->set_active(false);
						buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
						buttons[Buttons::BT_CHARC_WEPR]->set_active(false);

						for (size_t i = 0; i <= 7; i++)
							buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(false);

						buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(514, 384));
						buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(590, 384));
					}
					else if (selected_class == Classes::CYGNUSKNIGHTS)
					{
						buttons[Buttons::BT_CHARC_WEPL]->set_active(false);
						buttons[Buttons::BT_CHARC_WEPR]->set_active(false);

						for (size_t i = 0; i <= 7; i++)
							buttons[Buttons::BT_CHARC_HAIRC0 + i]->set_active(false);

						buttons[Buttons::BT_CHARC_OK]->set_position(Point<int16_t>(510, 386));
						buttons[Buttons::BT_CHARC_CANCEL]->set_position(Point<int16_t>(615, 386));
					}

					return Button::State::NORMAL;
				}
				else
				{
					button_pressed(Buttons::BT_BACK);

					return Button::State::NORMAL;
				}
			}
		}

		if (buttonid >= Buttons::BT_CHARC_FACEL && buttonid <= Buttons::BT_CHARC_HAIRC7)
		{
			switch (buttonid)
			{
			case Buttons::BT_CHARC_FACEL:
				face = (face > 0) ? face - 1 : faces[female].size() - 1;
				newchar.set_face(faces[female][face]);
				facename.change_text(newchar.get_face()->get_name());
				break;
			case Buttons::BT_CHARC_FACER:
				face = (face < faces[female].size() - 1) ? face + 1 : 0;
				newchar.set_face(faces[female][face]);
				facename.change_text(newchar.get_face()->get_name());
				break;
			case Buttons::BT_CHARC_HAIRL:
				hair = (hair > 0) ? hair - 1 : hairs[female].size() - 1;
				newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
				hairname.change_text(newchar.get_hair()->get_name());
				break;
			case Buttons::BT_CHARC_HAIRR:
				hair = (hair < hairs[female].size() - 1) ? hair + 1 : 0;
				newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
				hairname.change_text(newchar.get_hair()->get_name());
				break;
			case Buttons::BT_CHARC_HAIRC0:
			case Buttons::BT_CHARC_HAIRC1:
			case Buttons::BT_CHARC_HAIRC2:
			case Buttons::BT_CHARC_HAIRC3:
			case Buttons::BT_CHARC_HAIRC4:
			case Buttons::BT_CHARC_HAIRC5:
			case Buttons::BT_CHARC_HAIRC6:
			case Buttons::BT_CHARC_HAIRC7:
				// TODO: These need to be changed so when you click the color it only assigns the color, not the next in the series
				haircolor = (haircolor > 0) ? haircolor - 1 : haircolors[female].size() - 1;
				newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
				haircname.change_text(newchar.get_hair()->getcolor());
				break;
			case Buttons::BT_CHARC_SKINL:
				skin = (skin > 0) ? skin - 1 : skins[female].size() - 1;
				newchar.set_body(skins[female][skin]);
				bodyname.change_text(newchar.get_body()->get_name());
				break;
			case Buttons::BT_CHARC_SKINR:
				skin = (skin < skins[female].size() - 1) ? skin + 1 : 0;
				newchar.set_body(skins[female][skin]);
				bodyname.change_text(newchar.get_body()->get_name());
				break;
			case Buttons::BT_CHARC_TOPL:
				top = (top > 0) ? top - 1 : tops[female].size() - 1;
				newchar.add_equip(tops[female][top]);
				topname.change_text(get_equipname(Equipslot::Id::TOP));
				break;
			case Buttons::BT_CHARC_TOPR:
				top = (top < tops[female].size() - 1) ? top + 1 : 0;
				newchar.add_equip(tops[female][top]);
				topname.change_text(get_equipname(Equipslot::Id::TOP));
				break;
			case Buttons::BT_CHARC_BOTL:
				bot = (bot > 0) ? bot - 1 : bots[female].size() - 1;
				newchar.add_equip(bots[female][bot]);
				botname.change_text(get_equipname(Equipslot::Id::PANTS));
				break;
			case Buttons::BT_CHARC_BOTR:
				bot = (bot < bots[female].size() - 1) ? bot + 1 : 0;
				newchar.add_equip(bots[female][bot]);
				botname.change_text(get_equipname(Equipslot::Id::PANTS));
				break;
			case Buttons::BT_CHARC_SHOESL:
				shoe = (shoe > 0) ? shoe - 1 : shoes[female].size() - 1;
				newchar.add_equip(shoes[female][shoe]);
				shoename.change_text(get_equipname(Equipslot::Id::SHOES));
				break;
			case Buttons::BT_CHARC_SHOESR:
				shoe = (shoe < shoes[female].size() - 1) ? shoe + 1 : 0;
				newchar.add_equip(shoes[female][shoe]);
				shoename.change_text(get_equipname(Equipslot::Id::SHOES));
				break;
			case Buttons::BT_CHARC_WEPL:
				weapon = (weapon > 0) ? weapon - 1 : weapons[female].size() - 1;
				newchar.add_equip(weapons[female][weapon]);
				wepname.change_text(get_equipname(Equipslot::Id::WEAPON));
				break;
			case Buttons::BT_CHARC_WEPR:
				weapon = (weapon < weapons[female].size() - 1) ? weapon + 1 : 0;
				newchar.add_equip(weapons[female][weapon]);
				wepname.change_text(get_equipname(Equipslot::Id::WEAPON));
				break;
			case Buttons::BT_CHARC_GENDER_M:
				if (female)
				{
					female = false;
					randomize_look();
				}

				break;
			case Buttons::BT_CHARC_GEMDER_F:
				if (!female)
				{
					female = true;
					randomize_look();
				}

				break;
			}

			return Button::State::MOUSEOVER;
		}

		return Button::State::PRESSED;
	}

	void UIExplorerCreation::randomize_look()
	{
		hair = randomizer.next_int(hairs[female].size());
		face = randomizer.next_int(faces[female].size());
		skin = randomizer.next_int(skins[female].size());
		haircolor = randomizer.next_int(haircolors[female].size());
		top = randomizer.next_int(tops[female].size());
		bot = randomizer.next_int(bots[female].size());
		shoe = randomizer.next_int(shoes[female].size());
		weapon = randomizer.next_int(weapons[female].size());

		newchar.set_body(skins[female][skin]);
		newchar.set_face(faces[female][face]);
		newchar.set_hair(hairs[female][hair] + haircolors[female][haircolor]);
		newchar.add_equip(tops[female][top]);
		newchar.add_equip(bots[female][bot]);
		newchar.add_equip(shoes[female][shoe]);
		newchar.add_equip(weapons[female][weapon]);

		bodyname.change_text(newchar.get_body()->get_name());
		facename.change_text(newchar.get_face()->get_name());
		hairname.change_text(newchar.get_hair()->get_name());
		haircname.change_text(newchar.get_hair()->getcolor());

		topname.change_text(get_equipname(Equipslot::Id::TOP));
		botname.change_text(get_equipname(Equipslot::Id::PANTS));
		shoename.change_text(get_equipname(Equipslot::Id::SHOES));
		wepname.change_text(get_equipname(Equipslot::Id::WEAPON));
		gendername.change_text(female ? "Female" : "Male");
	}

	const std::string& UIExplorerCreation::get_equipname(Equipslot::Id slot) const
	{
		if (int32_t item_id = newchar.get_equips().get_equip(slot))
		{
			return ItemData::get(item_id).get_name();
		}
		else
		{
			static const std::string& nullstr = "Missing name.";

			return nullstr;
		}
	}
}