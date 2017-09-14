#include <locale>
#include <codecvt>
#include <algorithm>
#include "Configuration.hh"
#include "SizeTConverter.hh"
#include "GameParameters.hh"

GameParameters::GameParameters(const std::string &filename) :
  _characters{
  SCharacter_info{true, true, L"Player 1", eColor::BLUE, eAILevel::EASY},
    SCharacter_info{true, true, L"Player 2", eColor::RED, eAILevel::EASY},
      SCharacter_info{true, true, L"Player 3", eColor::GREEN, eAILevel::EASY},
	SCharacter_info{true, false, L"Player 4", eColor::ORANGE, eAILevel::NONE}
},
  _map{11, 50}
{
  try
    {
      Configuration	game_parameters_file{filename, std::vector<std::string>{
	  {"map_size:"},
	    {"map_density:"},
	      {"player_one_existence:"},
		{"player_one_ai:"},
		  {"player_one_color:"},
		    {"player_one_script:"},
		      {"player_one_name:"},
			{"player_two_existence:"},
			  {"player_two_ai:"},
			    {"player_two_color:"},
			      {"player_two_script:"},
				{"player_two_name:"},
				  {"player_three_existence:"},
				    {"player_three_ai:"},
				      {"player_three_color:"},
					{"player_three_script:"},
					  {"player_three_name:"},
					    {"player_four_existence:"},
					      {"player_four_ai:"},
						{"player_four_color:"},
						  {"player_four_script:"},
						    {"player_four_name:"}
	}};
      SizeTConverter	converter;
      std::string	tmp;
      _map._size = converter.atoi_ranged(game_parameters_file.Get_var_value("map_size:"), 10, 100);
      _map._density = converter.atoi_ranged(game_parameters_file.Get_var_value("map_density:"), 0, 100);
      _characters[0]._is_present = converter.atoi_ranged(game_parameters_file.Get_var_value("player_one_existence:"), 0, 1);
      _characters[0]._is_ai = converter.atoi_ranged(game_parameters_file.Get_var_value("player_one_ai:"), 0, 1);
      tmp = game_parameters_file.Get_var_value("player_one_name:");
      _characters[0]._name = std::wstring(tmp.begin(), tmp.end());
      _characters[0]._color = static_cast<eColor>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_one_color:"), static_cast<size_t>(eColor::BLUE), static_cast<size_t>(eColor::ORANGE)));
      _characters[0]._level = static_cast<eAILevel>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_one_script:"), static_cast<size_t>(eAILevel::EASY), static_cast<size_t>(eAILevel::NONE)));
      _characters[1]._is_present = converter.atoi_ranged(game_parameters_file.Get_var_value("player_two_existence:"), 0, 1);
      _characters[1]._is_ai = converter.atoi_ranged(game_parameters_file.Get_var_value("player_two_ai:"), 0, 1);
      tmp = game_parameters_file.Get_var_value("player_two_name:");
      _characters[1]._name = std::wstring(tmp.begin(), tmp.end());
      _characters[1]._color = static_cast<eColor>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_two_color:"), static_cast<size_t>(eColor::BLUE), static_cast<size_t>(eColor::ORANGE)));
      _characters[1]._level = static_cast<eAILevel>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_two_script:"), static_cast<size_t>(eAILevel::EASY), static_cast<size_t>(eAILevel::NONE)));
      _characters[2]._is_present = converter.atoi_ranged(game_parameters_file.Get_var_value("player_three_existence:"), 0, 1);
      _characters[2]._is_ai = converter.atoi_ranged(game_parameters_file.Get_var_value("player_three_ai:"), 0, 1);
      tmp = game_parameters_file.Get_var_value("player_three_name:");
      _characters[2]._name = std::wstring(tmp.begin(), tmp.end());
      _characters[2]._color = static_cast<eColor>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_three_color:"), static_cast<size_t>(eColor::BLUE), static_cast<size_t>(eColor::ORANGE)));
      _characters[2]._level = static_cast<eAILevel>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_three_script:"), static_cast<size_t>(eAILevel::EASY), static_cast<size_t>(eAILevel::NONE)));
      _characters[3]._is_present = converter.atoi_ranged(game_parameters_file.Get_var_value("player_four_existence:"), 0, 1);
      _characters[3]._is_ai = converter.atoi_ranged(game_parameters_file.Get_var_value("player_four_ai:"), 0, 1);
      tmp = game_parameters_file.Get_var_value("player_four_name:");
      _characters[3]._name = std::wstring(tmp.begin(), tmp.end());
      _characters[3]._color = static_cast<eColor>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_four_color:"), static_cast<size_t>(eColor::BLUE), static_cast<size_t>(eColor::ORANGE)));
      _characters[3]._level = static_cast<eAILevel>(converter.atoi_ranged(game_parameters_file.Get_var_value("player_four_script:"), static_cast<size_t>(eAILevel::EASY), static_cast<size_t>(eAILevel::NONE)));
    }
  catch (std::exception &e)
    {
      std::cerr << "Invalid game parameters, using default values" << std::endl;
      _characters[0] = SCharacter_info{true, false, L"Player 1", eColor::BLUE, eAILevel::NONE};
      _characters[1] = SCharacter_info{true, true, L"Player 2", eColor::RED, eAILevel::EASY};
      _characters[2] = SCharacter_info{true, true, L"Player 3", eColor::GREEN, eAILevel::EASY};
      _characters[3] = SCharacter_info{true, true, L"Player 4", eColor::ORANGE, eAILevel::EASY};
      _map = SMap_info{11, 50};
    }
}

bool			GameParameters::invalid_parameters(const wchar_t *error_str)
{
  _last_error = error_str;
  return (false);
}

bool			GameParameters::Parameters_are_valids()
{
  size_t		nb_present{0};
  std::vector<eColor>	color_sets;
  std::vector<std::wstring>	player_names;

  size_t	idx{0};
  for (auto & it : _characters)
    {
      if (it._is_present)
	++nb_present;
      if (std::find(player_names.begin(), player_names.end(), it._name) != player_names.end())
	return (invalid_parameters(L"Multiple players have the same name!"));
      else if (std::find(color_sets.begin(), color_sets.end(), it._color) != color_sets.end())
	return (invalid_parameters(L"Multiple players have the same color!"));
      else if ((it._is_ai
		&& it._level == eAILevel::NONE)
	       || (!it._is_ai
		   && it._level != eAILevel::NONE))
	return (invalid_parameters(L"All human players must have none difficulty and AI players can't have anyhting else"));
      player_names.push_back(it._name);
      color_sets.push_back(it._color);
    }
  if (nb_present < 2)
    return (invalid_parameters(L"Need at least two players to play!"));
  return (true);
}

const std::wstring	&GameParameters::Get_last_error() const
{
  return (_last_error);
}

void	GameParameters::Set_a_character_status(size_t character_idx, bool status_idx, bool value)
{
  if (status_idx == 0)
    _characters.at(character_idx)._is_present = value;
  else
    _characters.at(character_idx)._is_ai = value;
}

void	GameParameters::Set_a_character_name(size_t character_idx, const std::wstring &new_character_name)
{
  _characters.at(character_idx)._name = new_character_name;
}

void	GameParameters::Set_a_character_color(size_t character_idx, eColor color)
{
  _characters.at(character_idx)._color = color;
}

void	GameParameters::Set_a_character_level(size_t character_idx, eAILevel level)
{
  _characters.at(character_idx)._level = level;
}

std::vector<SCharacter_info> const	&GameParameters::Get_characters_info() const
{
  return (_characters);
}

void	GameParameters::Set_map_density(size_t density)
{
  _map._density = density;
}

void	GameParameters::Set_map_size(size_t size)
{
  _map._size = size;
}

SMap_info const			&GameParameters::Get_map_info() const
{
  return (_map);
}
