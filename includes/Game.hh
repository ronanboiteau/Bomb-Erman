#ifndef GAME_HH_
# define GAME_HH_

# include <vector>
# include <irrKlang.h>
# include "Map.hh"
# include "ACharacter.hh"
# include "RessourcesLoader.hh"
# include "HighScores.hh"
# include "GameParameters.hh"
# include "Settings.hh"
# include "OptionsManager.hh"
# include "SoundManager.hh"
# include "ABox.hh"

// ------ TEST ------

struct		CharactersInfo
{
  bool		_is_present;
  bool		_is_ai;
  std::string	_name;
  eColor	_color;
  CharactersInfo(bool is_present, bool is_ai, std::string name, eColor color) :
    _is_present(is_present),
    _is_ai(is_ai),
    _name(name),
    _color(color)
  {
  };
};

class				Game final
{
  OptionsManager		_settings;
  Map				_map;
  SoundManager			*_sound_manager;
  RessourcesLoader		*_ressources_loader;
  HighScores			*_high_scores;
  std::vector<ACharacter *>	_characters;
  bool				_game_over;
  void				end_game_draw();
  void				end_game_win();
  bool				is_end_of_game();
  void				draw_scores();
  irr::gui::IGUIFont		*_font;
  bool				pause(ILikeToMoveIt &receiver);
  void				skip_map(std::ifstream &file);
  int				get_line(std::ifstream &file) const;
  bool				check_characters(std::ifstream &file, int size_map) const;
  bool				check_file(std::string const &file) const;
public:
  Game(const GameParameters &game_param, const OptionsManager &settings, irr::IrrlichtDevice *device, RessourcesLoader *ressources, SoundManager *sound_manager, HighScores *high_scores);
  Game(const std::string &file_path, const OptionsManager &settings, irr::IrrlichtDevice *device, RessourcesLoader *ressources, SoundManager *sound_manager, HighScores *high_scores);
  Game(const Game &game) = delete;
  Game					&operator=(const Game &game) = delete;
  const Map				&Get_map() const;
  const std::vector<ACharacter *>	&Get_characters() const;
  void					Event_loop();
  void					Load_save(const std::string &file_path);
  void					Save_game() const;
  BoxType::eBoxType			Selected_type(int type);
  ~Game();
};

#endif /* !GAME_HH_ */
