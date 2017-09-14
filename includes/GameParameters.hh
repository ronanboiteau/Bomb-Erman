#ifndef GAME_PARAMETERS_HH_
# define GAME_PARAMETERS_HH_

# include <vector>
# include "AI.hh"
struct	SCharacter_info
{
  bool		_is_present;
  bool		_is_ai;
  std::wstring	_name;
  eColor	_color;
  eAILevel	_level;
};

struct	SMap_info
{
  size_t	_size;
  size_t	_density;
};

class	GameParameters final
{
private:
  std::vector<SCharacter_info>		_characters;
  SMap_info				_map;
  std::wstring				_last_error;
  bool					invalid_parameters(const wchar_t *error_str);
public:
  GameParameters(const std::string &filename);
  const std::wstring			&Get_last_error() const;
  void					Set_a_character_status(size_t character_idx, bool status_idx, bool value);
  void					Set_a_character_name(size_t character_idx,
							     const std::wstring &new_character_name);
  void					Set_a_character_color(size_t character_idx,
							      eColor color);
  void					Set_a_character_level(size_t character_idx,
							     eAILevel level);
  std::vector<SCharacter_info> const	&Get_characters_info() const;
  bool					Parameters_are_valids();
  void					Set_map_density(size_t density);
  void					Set_map_size(size_t size);
  SMap_info const			&Get_map_info() const;
  ~GameParameters() = default;
};

#endif /* !GAME_PARAMETERS_HH_ */
