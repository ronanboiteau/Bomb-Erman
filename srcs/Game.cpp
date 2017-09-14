#include <regex>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <irrlicht.h>
#include <iomanip>
#include "ILikeToMoveIt.hpp"
#include "Game.hh"
#include "AI.hh"
#include "Player.hh"
#include "SizeTConverter.hh"

using namespace std::chrono;

Game::Game(const GameParameters &game_param, const OptionsManager &settings,
	   irr::IrrlichtDevice *device, RessourcesLoader *ressources,
	   SoundManager *sound_manager, HighScores *high_scores) :
  _settings(settings),
  _map(game_param.Get_map_info()._size,
       game_param.Get_map_info()._density,
       device, ressources->Get_meshes_loader(), ressources->Get_images_loader()),
  _sound_manager(sound_manager),
  _high_scores(high_scores),
  _game_over(false),
  _font(ressources->Get_ressources_menu()->Get_font("indie_ressources/fonts/bigfont.png"))
{
  _ressources_loader = ressources;
  size_t	id_player = 0;
  Position	pos_player;
  eHeading	heading;
  size_t	map_size = _map.Get_size();

  _sound_manager->Play_music_game();
  for (auto &it : game_param.Get_characters_info())
    {
      if (it._is_present)
	{
	  switch (id_player)
	    {
	    case (0) :
	      pos_player._x = 1;
	      pos_player._y = 1;
	      heading = eHeading::DOWN;
	      break ;
	    case (1) :
	      pos_player._x = map_size - 2;
	      pos_player._y = map_size - 2;
	      heading = eHeading::DOWN;
	      break ;
	    case (2) :
	      pos_player._x = map_size - 2;
	      pos_player._y = 1;
	      heading = eHeading::DOWN;
	      break ;
	    default :
	      pos_player._x = 1;
	      pos_player._y = map_size - 2;
	      break ;
	    }
	  if (it._is_ai)
	    _characters.push_back(new AI(it._name, it._color, pos_player, _map, heading, id_player, it._level, _sound_manager, _ressources_loader->Get_meshes_loader(), _ressources_loader->Get_images_loader()));
	  else
	    _characters.push_back(new Player(it._name, it._color, pos_player, _map, heading, id_player, _sound_manager, _ressources_loader->Get_meshes_loader(), _ressources_loader->Get_images_loader()));
	  id_player += 1;
	}
    }
  for (auto &it2 : _characters)
    it2->Set_characters(_characters);
  _map.Get_device().getGUIEnvironment()->addImage(_ressources_loader->Get_images_loader()->Get_image("indie_ressources/images/white.png"),
						  irr::core::position2d<irr::s32>(0,0));
}

void			Game::skip_map(std::ifstream &file)
{
  size_t		size;
  size_t		trash;
  size_t		idx = 0;
  size_t		idx_line;

  file >> size;
  while (idx < size)
    {
      idx_line = 0;
      while (idx_line < size)
	{
	  file >> trash;
	  ++idx_line;
	}
      ++idx;
    }
}

void		Game::Load_save(const std::string &file_path)
{
  std::ifstream		file(file_path);
  std::string		line;
  size_t		nb_players;
  size_t		idx = 0;

  if (!file.is_open() || check_file(file_path) == false)
    return ;
  skip_map(file);
  file >> nb_players;
  idx = 0;
  while (idx < nb_players)
    {
      ACharacter	*character;
      size_t		len;
      size_t		color;
      Position		pos_player;
      size_t		heading;
      size_t		id_player;
      bool		is_an_ai;
      bool		extra_life;
      size_t		range_bomb;
      size_t		sim_bomb;
      bool		has_master_bomb;
      size_t		score;
      bool		am_i_dead;
      size_t		level;
      file >> len;
      ++len;
      char		*raw = new char[len];
      file.get();
      file.get(raw, len);
      std::string	name(raw);
      delete[] raw;
      ++idx;
      file >> color;
      file >> pos_player._x;
      file >> pos_player._y;
      file >> heading;
      file >> id_player;
      file >> is_an_ai;
      if (is_an_ai)
	file >> level;
      file >> extra_life;
      file >> range_bomb;
      file >> sim_bomb;
      file >> has_master_bomb;
      file >> score;
      file >> am_i_dead;
      if (is_an_ai)
	character = new AI(std::wstring(name.begin(), name.end()),static_cast<eColor>(color),
			   pos_player, _map, static_cast<eHeading>(heading), id_player,
			   static_cast<eAILevel>(level), _sound_manager, _ressources_loader->Get_meshes_loader(), _ressources_loader->Get_images_loader());
      else
	character = new Player(std::wstring(name.begin(), name.end()), static_cast<eColor>(color),
			       pos_player, _map, static_cast<eHeading>(heading), id_player, _sound_manager, _ressources_loader->Get_meshes_loader(), _ressources_loader->Get_images_loader());
      character->Set_extra_life(extra_life);
      while (range_bomb > 3)
	{
	  character->Inc_range_bomb();
	  --range_bomb;
	}
      while (sim_bomb > 1)
	{
	  character->Inc_sim_bomb();
	  --sim_bomb;
	}
      character->Set_master_bomb(has_master_bomb);
      character->Add_score(score);
      character->Set_am_i_dead(am_i_dead);
      _characters.push_back(character);
    }
  for (auto &it2 : _characters)
    it2->Set_characters(_characters);
  _map.Get_device().getGUIEnvironment()->addImage(_map.Get_driver().getTexture("indie_ressources/assets/white.png"), irr::core::position2d<irr::s32>(0,0));
}

Game::Game(const std::string &file_path, const OptionsManager &settings,
	   irr::IrrlichtDevice *device, RessourcesLoader *ressources,
	   SoundManager *sound_manager, HighScores *high_scores) :
  _settings(settings),
  _map(file_path, device, ressources->Get_meshes_loader(), ressources->Get_images_loader()),
  _sound_manager(sound_manager),
  _high_scores(high_scores),
  _game_over(false),
  _font(ressources->Get_ressources_menu()->Get_font("indie_ressources/fonts/bigfont.png"))
{
  _ressources_loader = ressources;
  _sound_manager->Play_music_game();
  Load_save(file_path);
}

const Map	&Game::Get_map() const
{
  return (_map);
}

const std::vector<ACharacter *>	&Game::Get_characters() const
{
  return (_characters);
}

void			Game::end_game_win()
{
  for (auto &it : _characters)
    {
      if (it->Am_i_dead() == false)
	{
	  int	idx = 0;

	  for (auto &it2 : _map.Get_map())
	    {
	      (void)it2;
	      for (auto &it3 : _map.Get_map()[idx])
		{
		  if (it3->Is_a_bonus())
		    it->Take_bonus(it3->Get_pos());
		}
	      idx += 1;
	    }
	}
    }
  for (auto &it : _characters)
    _high_scores->Add_highscore(std::string(it->Get_name().begin(), it->Get_name().end()), it->Get_score());
  _game_over = true;
}

void			Game::end_game_draw()
{
  for (auto &it : _characters)
    _high_scores->Add_highscore(std::string(it->Get_name().begin(), it->Get_name().end()), it->Get_score());
  _game_over = true;
}

bool			Game::is_end_of_game()
{
  if (_game_over)
    return (true);

  size_t		alive_players = 0;

  for (auto &it : _characters)
    {
      if (it->Am_i_dead() == false)
	++alive_players;
    }
  if (alive_players == 1)
    {
      end_game_win();
      return (true);
    }
  else if (alive_players == 0)
    {
      end_game_draw();
      return (true);
    }
  return (false);
}

void				Game::Event_loop()
{
  wchar_t			titre[100];
  irr::core::vector3df		posCam;
  ILikeToMoveIt			receiver;
  time_point<system_clock>      t = system_clock::now();
  time_point<system_clock>	*end = NULL;

  _map.Get_device().setEventReceiver(&receiver);
  for (auto &it : _characters)
    it->Spawn();
  _map.Get_device().getCursorControl()->setVisible(false);
  while (_map.Get_device().run())
    {
      t += milliseconds(25);
      std::this_thread::sleep_until(t);
      for (auto &it : _characters)
	{
	  if (it->Am_i_dead() == false)
	    it->Set_heading(receiver);
	  if (it->Get_is_moving() == 42 && end == NULL)
	    {
	      end = new time_point<system_clock>;
	      *end = system_clock::now();
	    }
	}
      posCam = _map.Get_camera().getPosition();
      _map.Get_driver().beginScene(true, true, irr::video::SColor(250, 250, 250, 250));
      _map.Get_scene_manager().drawAll();
      if (receiver.IsKeyDown(irr::KEY_SPACE))
	{
	  if (end != NULL || pause(receiver) == false)
	    break ;
	  receiver.Reset_key();
	}
      draw_scores();
      if (end != NULL)
	{
	  _font->draw("Somebody won ('ce told me...)", irr::core::rect<irr::s32>(100, 375, 800, 475), irr::video::SColor(255,255,0,0));
	    _font->draw("PRESS SPACE TO QUIT", irr::core::rect<irr::s32>(200, 475, 450, 575), irr::video::SColor(255,255,0,0));
	  _map.Get_driver().draw2DRectangle(irr::video::SColor(100,255,255,255),
					    irr::core::rect<irr::s32>(0, 0, 800, 800), 0);
	  _map.Get_camera().setPosition({posCam.X, posCam.Y, posCam.Z});
	}
      _map.Get_driver().endScene();
      _map.Try_explode_bombs();
      if (is_end_of_game() && end != NULL && *end + milliseconds(7000) <= system_clock::now())
	break ;
    }
  if (!_game_over)
    {
      Save_game();
      exit(0);
    }
  _map.Get_device().getCursorControl()->setVisible(true);
  for (auto &it : _characters)
    {
      if (it->Am_i_dead() == false)
	it->Get_node()->remove();
    }
}

void				Game::draw_scores()
{
  wchar_t			score[100];
  size_t			id_player = 0;
  irr::core::rect<irr::s32>	pos;

  for (auto &it : _characters)
    {
      swprintf(score, 100, L"%d", it->Get_score());
      switch (id_player)
	{
	case (0) :
	  pos = irr::core::rect<irr::s32>(0,0,100,50);
	  break ;
	case (1) :
	  pos = irr::core::rect<irr::s32>(700,750,800,800);
	  break ;
	case (2) :
	  pos = irr::core::rect<irr::s32>(0,750,100,800);
	  break ;
	default :
	  pos = irr::core::rect<irr::s32>(700,0,800,50);
	  break ;
	}
      _map.Get_driver().draw2DRectangle(irr::video::SColor(255,255,255,255), pos, 0);
      _font->draw(score, pos, irr::video::SColor(255,255,0,0));
      id_player += 1;
    }
}

void			Game::Save_game() const
{
  std::string		file_name("indie_persistent_data/saves/Erman_");
  auto			now = std::chrono::system_clock::now();
  auto			in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream	time;

  time << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%X");
  file_name += time.str();
  file_name += ".sqg";
  std::ofstream		file(file_name);

  if (!file.is_open())
    return ;
  file << _map.Get_size();
  file << std::endl;
  for (auto &it : _map.Get_map())
    {
      size_t	i = 0;
      for (auto &it2 : it)
  	{
	  file << static_cast<size_t>(it2->Get_type());
	  if (i != it.size() - 1)
	    file << " ";
	  i += 1;
  	}
      file << std::endl;
    }
  file << _characters.size() << std::endl;
  for (auto &it : _characters)
    {
      std::string	name(it->Get_name().begin(), it->Get_name().end());
      file << name.size() << std::endl;
      file << name << std::endl;
      file << static_cast<size_t>(it->Get_color()) << std::endl;
      file << it->Get_pos()._x << std::endl;
      file << it->Get_pos()._y << std::endl;
      file << static_cast<size_t>(it->Get_heading()) << std::endl;
      file << it->Get_id() << std::endl;
      file << it->Is_AI() << std::endl;
      if (it->Is_AI())
	file << static_cast<size_t>(static_cast<AI*>(it)->Get_level()) << std::endl;
      file << it->Has_extra_life() << std::endl;
      file << it->Get_range_bomb() << std::endl;
      file << it->Get_sim_bomb() << std::endl;
      file << it->Has_master_bomb() << std::endl;
      file << it->Get_score() << std::endl;
      file << it->Am_i_dead() << std::endl;
    }
}

bool				Game::pause(ILikeToMoveIt &receiver)
{
  time_point<system_clock>      t = system_clock::now();

  receiver.Reset_key();
  _font->draw("PAUSE", irr::core::rect<irr::s32>(350, 275, 450, 375), irr::video::SColor(255,255,0,0));
  _font->draw("PRESS SPACE TO RESUME", irr::core::rect<irr::s32>(200, 375, 450, 475), irr::video::SColor(255,255,0,0));
  _font->draw("PRESS X TO SAVE AND QUIT", irr::core::rect<irr::s32>(170, 475, 450, 575), irr::video::SColor(255,255,0,0));
  _map.Get_driver().draw2DRectangle(irr::video::SColor(100,255,255,255),
				    irr::core::rect<irr::s32>(0, 0, 800, 800), 0);
  _map.Get_driver().endScene();
  while (_map.Get_device().run())
    {
      if (receiver.IsKeyDown(irr::KEY_SPACE))
	break ;
      if (receiver.IsKeyDown(irr::KEY_KEY_X))
	{
	  _map.Add_to_timer(std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now() - t));
	  return (false);
	}
    }
  _map.Add_to_timer(std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now() - t));
  return (true);
}

int			Game::get_line(std::ifstream &file) const
{
  std::string		line;
  SizeTConverter	truc;

  std::getline(file, line);
  return (truc.atoi(line));
}

bool		Game::check_file(std::string const &file_name) const
{
  std::ifstream file(file_name, std::ios::in);
  if (!file)
    return (false);
  std::string	line;
  int		map_size = get_line(file);
  int		nb_characters;
  std::string	character;
  int		i = 0;

  if (map_size < 7 && map_size > 25)
    return (false);
  while (std::getline(file, line) && i != map_size - 1)
    {
      if (regex_match(line, std::regex("((10|[0-9]) ){10}(10|[0-9])")) == false)
	return (false);
      i += 1;
    }
  std::getline(file, line);
  if (i != map_size - 1 || regex_match(line, std::regex("((10|[0-9]) ){10}(10|[0-9])")) == true)
    return (false);
  nb_characters = std::stoi(line);
  if (nb_characters < 2 || nb_characters > 4)
    return (false);
  i = 0;
  while (i != nb_characters)
    {
      if (check_characters(file, map_size) == false)
	return (false);
      i += 1;
    }
  return (true);
}

bool		Game::check_characters(std::ifstream &file, int size_map) const
{
  std::string	line;
  int		temp = 0;

  temp = get_line(file);
  if (std::getline(file, line) && static_cast<int>(line.size()) != temp)
    return (false);
  temp = get_line(file);
  if (temp < 0 || temp > 3)
    return (false);
  temp = get_line(file);
  if (temp < 0 || temp > size_map)
    return (false);
  temp = get_line(file);
  if (temp < 0 || temp > size_map)
    return (false);
  temp = get_line(file);
  if (temp < 0 || temp > 3)
    return (false);
  temp = get_line(file);
  if (temp < 0 || temp > 3)
    return (false);
  temp = get_line(file);
  if (temp != 1 && temp != 0)
    return (false);
  else if (temp == 1)
    {
      temp = get_line(file);
      if (temp < 0 || temp > 3)
	return (false);
    }
  temp = get_line(file);
  if (temp != 1 && temp != 0)
    return (false);
  temp = get_line(file);
  if (temp <= 0)
    return (false);
  temp = get_line(file);
  if (temp <= 0)
    return (false);
  temp = get_line(file);
  if (temp != 1 && temp != 0)
    return (false);
  temp = get_line(file);
  if (temp < 0)
    return (false);
  temp = get_line(file);
  if (temp != 1 && temp != 0)
    return (false);
  return (true);
}

Game::~Game()
{
  _sound_manager->Play_music_menu();
}
