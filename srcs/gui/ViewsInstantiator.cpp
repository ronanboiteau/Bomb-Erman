#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "ViewsInstantiator.hh"
#include "HighScores.hh"

ViewsInstantiator::ViewsInstantiator(RessourcesMenuLoader *ressources_menu_loader,
				     ImagesLoader *images_loader,
				     const GameParameters &game_parameters,
				     const OptionsManager &settings,
				     const HighScores &high_scores)
{
  const std::vector<std::string>	&files{ressources_menu_loader->Get_saves()};
  irr::core::array<std::wstring>	*tmp_saves = new irr::core::array<std::wstring>;
  for (auto &it: files)
    tmp_saves->push_back(std::wstring{it.begin(), it.end()});
  static SGuiElem	button_default{GuiType::BUTTON, 0, 0, 0, SGuiButtonParams{
      irr::core::dimension2d<irr::s32>{0,0}, L""
					       }
  };
  static SGuiElem	scrollbar_default{GuiType::SCROLL_BAR, 0, 0, 0, SGuiScrollBarParams{
      irr::core::dimension2d<irr::s32>{0,0}, false, 0, 0, 0, 0, 0
					       }
  };
  static SGuiElem	check_box_default{GuiType::CHECK_BOX, 0, 0, 0, SGuiCheckBoxParams{
      irr::core::dimension2d<irr::s32>{0, 0}, false, L""
						}
  };
  static SGuiElem	static_text_default{GuiType::STATIC_TEXT, 0, 0, 0, SGuiStaticTextParams{
      new std::wstring, false, false, false
	}
  };
  static SGuiElem	edit_box_default{GuiType::EDIT_BOX, 0, 0, 0, SGuiEditBoxParams{
      new std::wstring, irr::core::dimension2d<irr::s32>{0,0}, false
								 }
  };

  static SGuiElem	list_box_default{GuiType::LIST_BOX, 0, 0, 0, SGuiListBoxParams{
      irr::core::dimension2d<irr::s32>{0, 0}
    }
  };

  std::vector<SCharacter_info>	_chars{game_parameters.Get_characters_info()};

  static SGuiElem	static_combo_box_default{GuiType::COMBO_BOX, 0, 0, 0, SGuiComboBoxParams{
      irr::core::dimension2d<irr::s32>{0,0}, false, 0, new irr::core::array<std::wstring>()}
  };

  std::vector<SGuiElem>	help_menu_view{button_default};
  help_menu_view[0]._id = static_cast<irr::s32>(ButtonsID::Help::RETURN);
  help_menu_view[0]._distance_from_top_border = 0;
  help_menu_view[0]._distance_from_left_border = 0;
  help_menu_view[0]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{16,8};
  help_menu_view[0]._BtnParams._text = L"Return";
  GuiView		help_menu{std::move(help_menu_view), images_loader->Get_image("indie_ressources/images/help.png")};
  _views[ViewID::HELP] = std::move(help_menu);

  std::vector<SGuiElem>	saves_menu_view{button_default, button_default, static_combo_box_default, button_default, list_box_default};
  saves_menu_view[0]._id = static_cast<irr::s32>(ButtonsID::Saves::RETURN);
  saves_menu_view[0]._distance_from_top_border = 0;
  saves_menu_view[0]._distance_from_left_border = 0;
  saves_menu_view[0]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{33,8};
  saves_menu_view[0]._BtnParams._text = L"Return";
  saves_menu_view[1]._id = static_cast<irr::s32>(ButtonsID::Saves::REMOVE);
  saves_menu_view[1]._distance_from_top_border = 45;
  saves_menu_view[1]._distance_from_left_border = 20;
  saves_menu_view[1]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{10,8};
  saves_menu_view[1]._BtnParams._text = L"Delete";
  saves_menu_view[2]._id = static_cast<irr::s32>(ButtonsID::Saves::SAVES);
  saves_menu_view[2]._distance_from_top_border = 45;
  saves_menu_view[2]._distance_from_left_border = 30;
  saves_menu_view[2]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{40, 8};
  saves_menu_view[2]._CmboBxParams._options = tmp_saves;
  saves_menu_view[2]._CmboBxParams._option_idx = 0;
  saves_menu_view[3]._id = static_cast<irr::s32>(ButtonsID::Saves::CONTINUE);
  saves_menu_view[3]._distance_from_top_border = 45;
  saves_menu_view[3]._distance_from_left_border = 70;
  saves_menu_view[3]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{10,8};
  saves_menu_view[3]._BtnParams._text = L"Load";
  saves_menu_view[4]._id = static_cast<irr::s32>(ButtonsID::Saves::ERRORS_MESSAGE_BOX);
  saves_menu_view[4]._distance_from_top_border = 80;
  saves_menu_view[4]._distance_from_left_border = 5;
  saves_menu_view[4]._LstBxParams._dimensions = irr::core::dimension2d<irr::s32>{90, 10};

  GuiView		save_menu{std::move(saves_menu_view), NULL};// images_loader->Get_image("indie_ressources/images/help.png")};
  _views[ViewID::SAVES] = std::move(save_menu);

  std::vector<SGuiElem>	main_menu_view{button_default, button_default, button_default, button_default, button_default, button_default, button_default};
  main_menu_view[0]._id = static_cast<irr::s32>(ButtonsID::Main::GAME);
  main_menu_view[0]._distance_from_top_border = 50;
  main_menu_view[0]._distance_from_left_border = 10;
  main_menu_view[0]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[0]._BtnParams._text = L"Play!";
  main_menu_view[1]._id = static_cast<irr::s32>(ButtonsID::Main::OPTIONS);
  main_menu_view[1]._distance_from_top_border = 60;
  main_menu_view[1]._distance_from_left_border = 10;
  main_menu_view[1]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[1]._BtnParams._text = L"Sound";
  main_menu_view[2]._id = static_cast<irr::s32>(ButtonsID::Main::HIGHSCORES);
  main_menu_view[2]._distance_from_top_border = 70;
  main_menu_view[2]._distance_from_left_border = 10;
  main_menu_view[2]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[2]._BtnParams._text = L"Highscores";
  main_menu_view[3]._id = static_cast<irr::s32>(ButtonsID::Main::SAVES);
  main_menu_view[3]._distance_from_top_border = 80;
  main_menu_view[3]._distance_from_left_border = 10;
  main_menu_view[3]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[3]._BtnParams._text = L"Saves";
  main_menu_view[4]._id = static_cast<irr::s32>(ButtonsID::Main::GAME_PARAMETERS);
  main_menu_view[4]._distance_from_top_border = 50;
  main_menu_view[4]._distance_from_left_border = 60;
  main_menu_view[4]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[4]._BtnParams._text = L"Settings";
  main_menu_view[5]._id = static_cast<irr::s32>(ButtonsID::Main::HELP);
  main_menu_view[5]._distance_from_top_border = 60;
  main_menu_view[5]._distance_from_left_border = 60;
  main_menu_view[5]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[5]._BtnParams._text = L"Help";
  main_menu_view[6]._id = static_cast<irr::s32>(ButtonsID::Main::EXIT);
  main_menu_view[6]._distance_from_top_border = 70;
  main_menu_view[6]._distance_from_left_border = 60;
  main_menu_view[6]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  main_menu_view[6]._BtnParams._text = L"Exit";
  GuiView		main_menu{std::move(main_menu_view), images_loader->Get_image("indie_ressources/images/main_menu_background.png")};
  _views[ViewID::MAIN_MENU] = std::move(main_menu);

  std::vector<SGuiElem>		game_parameters_view{button_default, check_box_default, check_box_default, edit_box_default, static_combo_box_default, static_combo_box_default,
      check_box_default, check_box_default, edit_box_default, static_combo_box_default, static_combo_box_default,
      check_box_default, check_box_default, edit_box_default, static_combo_box_default, static_combo_box_default,
      check_box_default, check_box_default, edit_box_default, static_combo_box_default, static_combo_box_default,
      list_box_default, static_text_default,
      scrollbar_default, static_text_default, scrollbar_default};
  game_parameters_view[0]._id = static_cast<irr::s32>(ButtonsID::GameParameters::RETURN);
  game_parameters_view[0]._distance_from_top_border = 0;
  game_parameters_view[0]._distance_from_left_border = 0;
  game_parameters_view[0]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{33,8};
  game_parameters_view[0]._BtnParams._text = L"Return";
  game_parameters_view[1]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE);
  game_parameters_view[1]._distance_from_top_border = 5;
  game_parameters_view[1]._distance_from_left_border = 35;
  game_parameters_view[1]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[1]._ChkBxParams._checked =_chars[0]._is_present;
  game_parameters_view[1]._ChkBxParams._text = L"Enable P1";
  game_parameters_view[2]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FIRST_PLAYER_IS_IA);
  game_parameters_view[2]._distance_from_top_border = 10;
  game_parameters_view[2]._distance_from_left_border = 35;
  game_parameters_view[2]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[2]._ChkBxParams._checked = _chars[0]._is_ai;;
  game_parameters_view[2]._ChkBxParams._text = L"CPU";
  game_parameters_view[3]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FIRST_PLAYER_NAME);
  game_parameters_view[3]._distance_from_top_border = 15;
  game_parameters_view[3]._distance_from_left_border = 41;
  game_parameters_view[3]._EdtBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[3]._EdtBxParams._text = new std::wstring(_chars[0]._name);
  game_parameters_view[3]._EdtBxParams._border = false;
  game_parameters_view[4]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FIRST_PLAYER_COLOR);
  game_parameters_view[4]._distance_from_top_border = 28;
  game_parameters_view[4]._distance_from_left_border = 41;
  game_parameters_view[4]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[4]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[4]._CmboBxParams._options->push_back(L"Blue");
  game_parameters_view[4]._CmboBxParams._options->push_back(L"Red");
  game_parameters_view[4]._CmboBxParams._options->push_back(L"Green");
  game_parameters_view[4]._CmboBxParams._options->push_back(L"Orange");
  game_parameters_view[4]._CmboBxParams._option_idx = static_cast<size_t>(_chars[0]._color);
  game_parameters_view[5]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FIRST_PLAYER_SCRIPT_NAME);
  game_parameters_view[5]._distance_from_top_border = 41;
  game_parameters_view[5]._distance_from_left_border = 41;
  game_parameters_view[5]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[5]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[5]._CmboBxParams._options->push_back(L"Easy");
  game_parameters_view[5]._CmboBxParams._options->push_back(L"Medium");
  game_parameters_view[5]._CmboBxParams._options->push_back(L"Hard");
  game_parameters_view[5]._CmboBxParams._options->push_back(L"None");
  game_parameters_view[5]._CmboBxParams._option_idx = static_cast<size_t>(_chars[0]._level);
  game_parameters_view[6]._id = static_cast<irr::s32>(ButtonsID::GameParameters::SECOND_PLAYER_EXISTENCE);
  game_parameters_view[6]._distance_from_top_border = 51;
  game_parameters_view[6]._distance_from_left_border = 35;
  game_parameters_view[6]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[6]._ChkBxParams._checked = _chars[1]._is_present;
  game_parameters_view[6]._ChkBxParams._text = L"Enable P2";
  game_parameters_view[7]._id = static_cast<irr::s32>(ButtonsID::GameParameters::SECOND_PLAYER_IS_IA);
  game_parameters_view[7]._distance_from_top_border = 56;
  game_parameters_view[7]._distance_from_left_border = 35;
  game_parameters_view[7]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[7]._ChkBxParams._checked = _chars[1]._is_ai;;
  game_parameters_view[7]._ChkBxParams._text = L"CPU";
  game_parameters_view[8]._id = static_cast<irr::s32>(ButtonsID::GameParameters::SECOND_PLAYER_NAME);
  game_parameters_view[8]._distance_from_top_border = 61;
  game_parameters_view[8]._distance_from_left_border = 41;
  game_parameters_view[8]._EdtBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[8]._EdtBxParams._text = new std::wstring(_chars[1]._name);
  game_parameters_view[8]._EdtBxParams._border = false;
  game_parameters_view[9]._id = static_cast<irr::s32>(ButtonsID::GameParameters::SECOND_PLAYER_COLOR);
  game_parameters_view[9]._distance_from_top_border = 74;
  game_parameters_view[9]._distance_from_left_border = 41;
  game_parameters_view[9]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[9]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[9]._CmboBxParams._options->push_back(L"Blue");
  game_parameters_view[9]._CmboBxParams._options->push_back(L"Red");
  game_parameters_view[9]._CmboBxParams._options->push_back(L"Green");
  game_parameters_view[9]._CmboBxParams._options->push_back(L"Orange");
  game_parameters_view[9]._CmboBxParams._option_idx = static_cast<size_t>(_chars[1]._color);
  game_parameters_view[10]._id = static_cast<irr::s32>(ButtonsID::GameParameters::SECOND_PLAYER_SCRIPT_NAME);
  game_parameters_view[10]._distance_from_top_border = 87;
  game_parameters_view[10]._distance_from_left_border = 41;
  game_parameters_view[10]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[10]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[10]._CmboBxParams._options->push_back(L"Easy");
  game_parameters_view[10]._CmboBxParams._options->push_back(L"Medium");
  game_parameters_view[10]._CmboBxParams._options->push_back(L"Hard");
  game_parameters_view[10]._CmboBxParams._options->push_back(L"None");
  game_parameters_view[10]._CmboBxParams._option_idx = static_cast<size_t>(_chars[1]._level);
  game_parameters_view[11]._id = static_cast<irr::s32>(ButtonsID::GameParameters::THIRD_PLAYER_EXISTENCE);
  game_parameters_view[11]._distance_from_top_border = 5;
  game_parameters_view[11]._distance_from_left_border = 70;
  game_parameters_view[11]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[11]._ChkBxParams._checked = _chars[2]._is_present;
  game_parameters_view[11]._ChkBxParams._text = L"Enable P3";
  game_parameters_view[12]._id = static_cast<irr::s32>(ButtonsID::GameParameters::THIRD_PLAYER_IS_IA);
  game_parameters_view[12]._distance_from_top_border = 10;
  game_parameters_view[12]._distance_from_left_border = 70;
  game_parameters_view[12]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[12]._ChkBxParams._checked = _chars[2]._is_ai;
  game_parameters_view[12]._ChkBxParams._text = L"CPU";
  game_parameters_view[13]._id = static_cast<irr::s32>(ButtonsID::GameParameters::THIRD_PLAYER_NAME);
  game_parameters_view[13]._distance_from_top_border = 15;
  game_parameters_view[13]._distance_from_left_border = 76;
  game_parameters_view[13]._EdtBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[13]._EdtBxParams._text = new std::wstring(_chars[2]._name);
  game_parameters_view[13]._EdtBxParams._border = false;
  game_parameters_view[14]._id = static_cast<irr::s32>(ButtonsID::GameParameters::THIRD_PLAYER_COLOR);
  game_parameters_view[14]._distance_from_top_border = 28;
  game_parameters_view[14]._distance_from_left_border = 76;
  game_parameters_view[14]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[14]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[14]._CmboBxParams._options->push_back(L"Blue");
  game_parameters_view[14]._CmboBxParams._options->push_back(L"Red");
  game_parameters_view[14]._CmboBxParams._options->push_back(L"Green");
  game_parameters_view[14]._CmboBxParams._options->push_back(L"Orange");
  game_parameters_view[14]._CmboBxParams._option_idx = static_cast<size_t>(_chars[2]._color);
  game_parameters_view[15]._id = static_cast<irr::s32>(ButtonsID::GameParameters::THIRD_PLAYER_SCRIPT_NAME);
  game_parameters_view[15]._distance_from_top_border = 41;
  game_parameters_view[15]._distance_from_left_border = 76;
  game_parameters_view[15]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[15]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[15]._CmboBxParams._options->push_back(L"Easy");
  game_parameters_view[15]._CmboBxParams._options->push_back(L"Medium");
  game_parameters_view[15]._CmboBxParams._options->push_back(L"Hard");
  game_parameters_view[15]._CmboBxParams._options->push_back(L"None");
  game_parameters_view[15]._CmboBxParams._option_idx = static_cast<size_t>(_chars[2]._level);
  game_parameters_view[16]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FOURTH_PLAYER_EXISTENCE);
  game_parameters_view[16]._distance_from_top_border = 51;
  game_parameters_view[16]._distance_from_left_border = 70;
  game_parameters_view[16]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[16]._ChkBxParams._checked = _chars[3]._is_present;
  game_parameters_view[16]._ChkBxParams._text = L"Enable P4";
  game_parameters_view[17]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FOURTH_PLAYER_IS_IA);
  game_parameters_view[17]._distance_from_top_border = 56;
  game_parameters_view[17]._distance_from_left_border = 70;
  game_parameters_view[17]._ChkBxParams._dimensions = irr::core::dimension2d<irr::s32>{50,4};
  game_parameters_view[17]._ChkBxParams._checked = _chars[3]._is_ai;
  game_parameters_view[17]._ChkBxParams._text = L"CPU";
  game_parameters_view[18]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FOURTH_PLAYER_NAME);
  game_parameters_view[18]._distance_from_top_border = 61;
  game_parameters_view[18]._distance_from_left_border = 76;
  game_parameters_view[18]._EdtBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[18]._EdtBxParams._text = new std::wstring(_chars[3]._name);
  game_parameters_view[18]._EdtBxParams._border = false;
  game_parameters_view[19]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FOURTH_PLAYER_COLOR);
  game_parameters_view[19]._distance_from_top_border = 74;
  game_parameters_view[19]._distance_from_left_border = 76;
  game_parameters_view[19]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[19]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[19]._CmboBxParams._options->push_back(L"Blue");
  game_parameters_view[19]._CmboBxParams._options->push_back(L"Red");
  game_parameters_view[19]._CmboBxParams._options->push_back(L"Green");
  game_parameters_view[19]._CmboBxParams._options->push_back(L"Orange");
  game_parameters_view[19]._CmboBxParams._option_idx = static_cast<size_t>(_chars[3]._color);
  game_parameters_view[20]._id = static_cast<irr::s32>(ButtonsID::GameParameters::FOURTH_PLAYER_SCRIPT_NAME);
  game_parameters_view[20]._distance_from_top_border = 87;
  game_parameters_view[20]._distance_from_left_border = 76;
  game_parameters_view[20]._CmboBxParams._dimensions = irr::core::dimension2d<irr::s32>{16, 8};
  game_parameters_view[20]._CmboBxParams._options = new irr::core::array<std::wstring>;
  game_parameters_view[20]._CmboBxParams._options->push_back(L"Easy");
  game_parameters_view[20]._CmboBxParams._options->push_back(L"Medium");
  game_parameters_view[20]._CmboBxParams._options->push_back(L"Hard");
  game_parameters_view[20]._CmboBxParams._options->push_back(L"None");
  game_parameters_view[20]._CmboBxParams._option_idx = static_cast<size_t>(_chars[3]._level);
  game_parameters_view[21]._id = static_cast<irr::s32>(ButtonsID::GameParameters::ERRORS_MESSAGE_BOX);
  game_parameters_view[21]._distance_from_top_border = 70;
  game_parameters_view[21]._distance_from_left_border = 5;
  game_parameters_view[21]._LstBxParams._dimensions = irr::core::dimension2d<irr::s32>{25, 10};
  game_parameters_view[22]._id = static_cast<irr::s32>(ButtonsID::GameParameters::MAP_DENSITY_TEXT);
  game_parameters_view[22]._distance_from_top_border = 38;
  game_parameters_view[22]._distance_from_left_border = 2;
  game_parameters_view[22]._StaticTextParams._text = new std::wstring(L"Density");
  game_parameters_view[22]._StaticTextParams._border = false;
  game_parameters_view[22]._StaticTextParams._wordwrap = true;
  game_parameters_view[22]._StaticTextParams._fill_background = false;
  game_parameters_view[23]._id = static_cast<irr::s32>(ButtonsID::GameParameters::MAP_DENSITY);
  game_parameters_view[23]._distance_from_top_border = 43;
  game_parameters_view[23]._distance_from_left_border = 2;
  game_parameters_view[23]._SBarParams._dimensions = irr::core::dimension2d<irr::s32>{29, 4};
  game_parameters_view[23]._SBarParams._horizontal = true;
  game_parameters_view[23]._SBarParams._pos = game_parameters.Get_map_info()._density;
  game_parameters_view[23]._SBarParams._min = 0;
  game_parameters_view[23]._SBarParams._max = 100;
  game_parameters_view[23]._SBarParams._small_step = 1;
  game_parameters_view[23]._SBarParams._large_step = 1;
  game_parameters_view[24]._id = static_cast<irr::s32>(ButtonsID::GameParameters::MAP_SIZE_TEXT);
  game_parameters_view[24]._distance_from_top_border = 50;
  game_parameters_view[24]._distance_from_left_border = 2;
  game_parameters_view[24]._StaticTextParams._text = new std::wstring(L"Map Size");
  game_parameters_view[24]._StaticTextParams._border = false;
  game_parameters_view[24]._StaticTextParams._wordwrap = true;
  game_parameters_view[24]._StaticTextParams._fill_background = false;
  game_parameters_view[25]._id = static_cast<irr::s32>(ButtonsID::GameParameters::MAP_SIZE);
  game_parameters_view[25]._distance_from_top_border = 55;
  game_parameters_view[25]._distance_from_left_border = 2;
  game_parameters_view[25]._SBarParams._dimensions = irr::core::dimension2d<irr::s32>{29, 4};
  game_parameters_view[25]._SBarParams._horizontal = true;
  game_parameters_view[25]._SBarParams._pos = game_parameters.Get_map_info()._size;
  game_parameters_view[25]._SBarParams._min = 7;
  game_parameters_view[25]._SBarParams._max = 25;
  game_parameters_view[25]._SBarParams._small_step = 1;
  game_parameters_view[25]._SBarParams._large_step = 1;
  GuiView		game_parameter{std::move(game_parameters_view), images_loader->Get_image("indie_ressources/images/settings_background.png")};
  _views[ViewID::GAME_PARAMETERS] = std::move(game_parameter);

  std::vector<SGuiElem>	game_menu_view{button_default};

  game_menu_view[0]._id = static_cast<irr::s32>(ButtonsID::Game::PAUSE);
  game_menu_view[0]._distance_from_top_border = 0;
  game_menu_view[0]._distance_from_left_border = 0;
  game_menu_view[0]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  game_menu_view[0]._BtnParams._text = L"Pause";
  GuiView		game_view{std::move(game_menu_view), NULL};
  _views[ViewID::GAME] = std::move(game_view);

  std::vector<SGuiElem>	options_menu_view{static_text_default, scrollbar_default, static_text_default, scrollbar_default, button_default};
  options_menu_view[0]._id = static_cast<irr::s32>(ButtonsID::Options::SOUNDS_TEXT);
  options_menu_view[0]._distance_from_top_border = 37;
  options_menu_view[0]._distance_from_left_border = 32;
  options_menu_view[0]._StaticTextParams._text = new std::wstring(L"Sound FX Volume [0 - 100]");
  options_menu_view[0]._StaticTextParams._border = false;
  options_menu_view[0]._StaticTextParams._wordwrap = true;
  options_menu_view[0]._StaticTextParams._fill_background = false;

  options_menu_view[1]._id = static_cast<irr::s32>(ButtonsID::Options::SOUNDS_VOLUME);
  options_menu_view[1]._distance_from_top_border = 42;
  options_menu_view[1]._distance_from_left_border = 30;
  options_menu_view[1]._SBarParams._dimensions = irr::core::dimension2d<irr::s32>{40, 4};
  options_menu_view[1]._SBarParams._horizontal = true;
  options_menu_view[1]._SBarParams._pos = settings.Get_sounds_volume();
  options_menu_view[1]._SBarParams._min = 0;
  options_menu_view[1]._SBarParams._max = 100;
  options_menu_view[1]._SBarParams._small_step = 1;
  options_menu_view[1]._SBarParams._large_step = 1;

  options_menu_view[2]._id = static_cast<irr::s32>(ButtonsID::Options::MUSICS_TEXT);
  options_menu_view[2]._distance_from_top_border = 48;
  options_menu_view[2]._distance_from_left_border = 32;
  options_menu_view[2]._StaticTextParams._text = new std::wstring(L"Music Volume [0 - 100]");
  options_menu_view[2]._StaticTextParams._border = false;
  options_menu_view[2]._StaticTextParams._wordwrap = true;
  options_menu_view[2]._StaticTextParams._fill_background = false;

  options_menu_view[3]._id = static_cast<irr::s32>(ButtonsID::Options::MUSICS_VOLUME);
  options_menu_view[3]._distance_from_top_border = 53;
  options_menu_view[3]._distance_from_left_border = 30;
  options_menu_view[3]._SBarParams._dimensions = irr::core::dimension2d<irr::s32>{40, 4};
  options_menu_view[3]._SBarParams._horizontal = true;
  options_menu_view[3]._SBarParams._pos = settings.Get_musics_volume();
  options_menu_view[3]._SBarParams._min = 0;
  options_menu_view[3]._SBarParams._max = 100;
  options_menu_view[3]._SBarParams._small_step = 1;
  options_menu_view[3]._SBarParams._large_step = 1;

  options_menu_view[4]._id = static_cast<irr::s32>(ButtonsID::Options::RETURN);
  options_menu_view[4]._distance_from_top_border = 0;
  options_menu_view[4]._distance_from_left_border = 0;
  options_menu_view[4]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  options_menu_view[4]._BtnParams._text = L"Return";

  GuiView		options_menu{std::move(options_menu_view), images_loader->Get_image("indie_ressources/images/sound_background.png")};
  _views[ViewID::OPTIONS] = std::move(options_menu);

  std::vector<SGuiElem>	highscores_view{button_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default, static_text_default};

  std::vector<Score>	_hs = high_scores.Get_highscores();

  highscores_view[0]._id = static_cast<irr::s32>(ButtonsID::Scores::RETURN);
  highscores_view[0]._distance_from_top_border = 0;
  highscores_view[0]._distance_from_left_border = 0;
  highscores_view[0]._BtnParams._dimensions = irr::core::dimension2d<irr::s32>{30,8};
  highscores_view[0]._BtnParams._text = L"Return";

  size_t	y_pos = 28;
  size_t	user_idx = 0;
  for (size_t idx = 0 ; idx < (_hs.size() * 2); idx += 2)
    {
      std::string		username(_hs[user_idx]._username);
      std::ostringstream	score;
      score << _hs[user_idx]._score;
      user_idx += 1;
      highscores_view[idx + 1]._id = static_cast<irr::s32>(ButtonsID::Scores::SCORE_TEXT);
      highscores_view[idx + 1]._distance_from_top_border = y_pos;
      highscores_view[idx + 1]._distance_from_left_border = 30;
      highscores_view[idx + 1]._StaticTextParams._text = new std::wstring(username.begin(), username.end());
      highscores_view[idx + 1]._StaticTextParams._border = false;
      highscores_view[idx + 1]._StaticTextParams._wordwrap = true;
      highscores_view[idx + 1]._StaticTextParams._fill_background = false;

      highscores_view[idx + 2]._id = static_cast<irr::s32>(ButtonsID::Scores::SCORE_TEXT);
      highscores_view[idx + 2]._distance_from_top_border = y_pos;
      highscores_view[idx + 2]._distance_from_left_border = 60;
      highscores_view[idx + 2]._StaticTextParams._text = new std::wstring(score.str().begin(), score.str().end());
      highscores_view[idx + 2]._StaticTextParams._border = false;
      highscores_view[idx + 2]._StaticTextParams._wordwrap = true;
      highscores_view[idx + 2]._StaticTextParams._fill_background = false;
      y_pos += 10;
    }

  GuiView		highscores{std::move(highscores_view), images_loader->Get_image("indie_ressources/images/highscores_background.png")};
  _views[ViewID::HIGHSCORES] = std::move(highscores);
}

std::unordered_map<ViewID, GuiView>	ViewsInstantiator::Get_views()
{
  return (std::move(_views));
}
