#include <algorithm>
#include <iostream>
#include "AI.hh"
#include "Bomb.hh"
#include "ABox.hh"
#include "Empty.hh"
#include "GetRand.hpp"

AI::AI(const std::wstring &name, eColor color, Position pos, Map &map, eHeading heading, size_t id, eAILevel level, SoundManager *sound, MeshesLoader *meshesLoader, ImagesLoader *imagesLoader) :
  ACharacter(name, color, pos, map, heading, id, sound, true, meshesLoader, imagesLoader),
  _level{level}
{
}

AI::AI(const std::wstring &file_to_load) :
  ACharacter(file_to_load)
{
}

void	AI::_print_debug() const
{
  size_t	t_x = 0;
  size_t	t_y = 0;

  std::wcout << Get_name() << std::endl;
  for (auto &y : _way)
    {
      for (auto &x : y)
	{
	  if (_map->Get_element(Position(t_x, t_y))->Get_type() == BoxType::eBoxType::BOMB_REGULAR ||
	      _map->Get_element(Position(t_x, t_y))->Get_type() == BoxType::eBoxType::BOMB_MASTER)
	    std::cout << "#";
	  else if (_map->Get_element(Position(t_x, t_y))->Get_type() == BoxType::eBoxType::EXPLOSION)
	    std::cout << "0";
	  else if (_way[t_y][t_x]._collision != 0)
	    std::cout << "█";
	  else
	    std::cout << _way[t_y][t_x]._danger;
	  t_x += 1;
	}
      std::cout << std::endl;
      t_x = 0;
      t_y += 1;
    }
  std::cout << std::endl;
}

eAILevel	AI::Get_level() const
{
  return (_level);
}

int	AI::_is_danger(Position const &pos) const
{
  return (_way[pos._y][pos._x]._danger);
}

bool	AI::_is_collision(Position const &pos) const
{
  return (_way[pos._y][pos._x]._collision);
}

bool	AI::_is_goal(Position const &pos) const
{
  return (_way[pos._y][pos._x]._goal);
}

void			AI::_easy_script()
{
  GetRand<unsigned int> rand{1, 100, static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count())};
  if (rand() <= 50)
    {
      std::vector<eHeading>	way;

      if (_way[_pos._y][_pos._x - 1]._danger != 1 &&
	  _way[_pos._y][_pos._x - 1]._collision == 0)
	way.push_back(eHeading::UP);
      if (_way[_pos._y][_pos._x + 1]._danger != 1 &&
	  _way[_pos._y][_pos._x + 1]._collision == 0)
 	way.push_back(eHeading::DOWN);
      if (_way[_pos._y + 1][_pos._x]._danger != 1 &&
	  _way[_pos._y + 1][_pos._x]._collision == 0)
	way.push_back(eHeading::RIGHT);
      if (_way[_pos._y - 1][_pos._x]._danger != 1 &&
	  _way[_pos._y - 1][_pos._x]._collision == 0)
	way.push_back(eHeading::LEFT);
      std::random_shuffle(way.begin(), way.end());
      if (way.size() != 0)
	Move(way.at(0));
      else if (_is_moving != 0)
	{
	  _node->setMD2Animation(irr::scene::EMAT_STAND);
	  _is_moving = 0;
	}	
    }
}

void	AI::_medium_script()
{
  if (_way[_pos._y][_pos._x]._danger == 1)
    _find_safe_zone();
  else
    {
      sWay	danger;
      for (auto &y : _way)
	{
	  for (auto &x : y)
	    {
	      if (x._count != -1 && x._danger == 0 && (x._count < danger._count || danger._count == -1))
		danger = x;
	    }
	}
      if (danger._count != -1 && danger._count <= 3)
	Drop_bomb();
      _easy_script();
    }
}

void	AI::_hard_script()
{
  if (_way[_pos._y][_pos._x]._danger == 1)
    _find_safe_zone();
  else if (_find_goal() == false)
    {
      sWay	danger;
      for (auto &y : _way)
	{
	  for (auto &x : y)
	    {
	      if (x._count != -1 && x._danger == 0 &&
		  (x._count < danger._count || danger._count == -1))
		danger = x;
	    }
	}
      if (danger._count != -1 && danger._count <= 3)
	Drop_bomb();
      _easy_script();
    }
}

void	AI::_find_safe_zone()
{
  sWay	danger;

  for (auto &y : _way)
    {
      for (auto &x : y)
	{
	  if (x._count != -1 && x._danger != 1 && (x._count < danger._count || danger._count == -1))
	    danger = x;
	}
    }
  if (danger._count != -1)
    Move(danger._heading);
  else if (_is_moving != 0)
    {
      _node->setMD2Animation(irr::scene::EMAT_STAND);
      _is_moving = 0;
    }
}

bool	AI::_find_goal()
{
  sWay	goal;

  for (auto &y : _way)
    {
      for (auto &x : y)
	{
	  if ((x._count != -1 && x._goal == 2) ||
	      (goal._goal != 2 && x._count != -1 && x._goal == 1 &&
	       (goal._count == -1 || x._count < goal._count)))
	    goal = x;
	}
    }
  if (goal._count != -1 &&
      ((goal._heading == eHeading::UP && _way[_pos._y][_pos._x - 1]._danger != 1) ||
       (goal._heading == eHeading::DOWN && _way[_pos._y][_pos._x + 1]._danger != 1) ||
       (goal._heading == eHeading::LEFT && _way[_pos._y - 1][_pos._x]._danger != 1) ||
       (goal._heading == eHeading::RIGHT && _way[_pos._y + 1][_pos._x]._danger != 1)))
    {
      Move(goal._heading);
      return (true);
    }
  else if (_is_moving != 0)
    {
      _node->setMD2Animation(irr::scene::EMAT_STAND);
      _is_moving = 0;
    }
  return (false);
}

void		AI::_set_goal(size_t x, size_t y)
{
  size_t	i = 0;

  if (_map->Get_element(Position(x, y))->Is_a_bonus())
    _way[y][x]._goal = 2;
  else
    {
      for (auto &it : *_characters)
      	{
      	  if (it != this && it->Am_i_dead() == false
	      && it->Get_pos()._x == x && it->Get_pos()._y == y)
      	    {
      	      _way[y][x]._goal = 1;
      	      break ;
      	    }
      	  i++;
      	}
      if (i == _characters->size())
	_way[y][x]._goal = 0;
    }
}

void	AI::_expand(int x, int y, int range, int hey)
{
  int	t_range = 1;

  _way[y][x]._danger = hey;
  while (range != t_range)
    {
      if (y + t_range < static_cast<int>(_map->Get_size() - 1))
      	_way[y + t_range][x]._danger = hey;
      if (y - t_range >= 0)
	_way[y - t_range][x]._danger = hey;
      if (x + t_range < static_cast<int>(_map->Get_size() - 1))
       	_way[y][x + t_range]._danger = hey;
      if (x - t_range >= 0)
       	_way[y][x - t_range]._danger = hey;
      t_range += 1;
    }
}

void	AI::_set_danger_zone()
{
  size_t	t_x = 0;
  size_t	t_y = 0;
  
  for (auto &y : _map->Get_map())
    {
      for (auto &x : y)
	{
	  if (x->Get_type() == BoxType::eBoxType::BOMB_REGULAR)
	    _expand(t_x, t_y, static_cast<Bomb *>(x)->Get_owner().Get_range_bomb(), 1);
	  else if (x->Get_type() == BoxType::eBoxType::BOMB_MASTER)
	    _expand(t_x, t_y, _map->Get_size(), 1);
	  t_x += 1;
	}
      t_x = 0;
      t_y += 1;
    }
}

void	AI::_set_collision()
{
  for (auto &y : _map->Get_map())
    {
      std::vector<sWay>	line;
      for (auto &x : y)
	{
	  line.push_back(sWay());
	  if (x->Get_type() == BoxType::eBoxType::BLOCK_BREAKABLE)
	    line.back()._collision = 1;
	  else if (x->Get_type() == BoxType::eBoxType::BLOCK_UNBREAKABLE ||
		   (x->Get_type() == BoxType::eBoxType::BOMB_REGULAR
		   && &static_cast<Bomb *>(x)->Get_owner() != this) ||
		   (x->Get_type() == BoxType::eBoxType::BOMB_MASTER
		    && &static_cast<Bomb *>(x)->Get_owner() != this) ||
		   x->Get_type() == BoxType::eBoxType::EXPLOSION)
	    line.back()._collision = 2;
	  else
	    line.back()._collision = 0;
	}
      _way.push_back(std::move(line));
    }
}

void		AI::_recursive_feelings(size_t x, size_t y, int count, eHeading heading)
{
  if (_way[y][x]._count != -1 && _way[y][x]._count <= count)
    return ;
  _set_goal(x, y);
  _way[y][x]._count = count;
  _way[y][x]._heading = heading;
  if (!_is_collision(Position(x + 1, y)))
    _recursive_feelings(x + 1, y, count + 1, heading);
  if (!_is_collision(Position(x, y + 1)))
    _recursive_feelings(x, y + 1, count + 1, heading);
  if (!_is_collision(Position(x - 1, y)))
    _recursive_feelings(x - 1, y, count + 1, heading);
  if (!_is_collision(Position(x, y - 1)))
    _recursive_feelings(x, y - 1, count + 1, heading);
}

void	AI::_set_way()
{
  if (!_is_collision(Position(_pos._x + 1, _pos._y)))
    _recursive_feelings(_pos._x + 1, _pos._y, 1, eHeading::DOWN);
  if (!_is_collision(Position(_pos._x, _pos._y + 1)))
    _recursive_feelings(_pos._x, _pos._y + 1, 1, eHeading::RIGHT);
  if (!_is_collision(Position(_pos._x - 1, _pos._y)))
    _recursive_feelings(_pos._x - 1, _pos._y, 1, eHeading::UP);
  if (!_is_collision(Position(_pos._x, _pos._y - 1)))
    _recursive_feelings(_pos._x, _pos._y - 1, 1, eHeading::LEFT);
}

void	AI::Set_characters(std::vector<ACharacter *> &characters)
{
  _characters = &characters;
}

void	AI::Set_heading(ILikeToMoveIt const &)
{
  int	i = 0;

  for (auto &it: *_characters)
    {
      if (it->Am_i_dead() == false)
	i += 1;
    }
  if (i == 1 && _is_moving != 42)
    {
      _is_moving = 42;
      _node->setMD2Animation(irr::scene::EMAT_WAVE);
    }
  else if (i != 1)
    {
      Take_bonus();
      irr::core::vector3df  pos = _node->getPosition();
      _way.clear();
      _set_collision();
      _set_way();
      _expand(_pos._x, _pos._y, _range_bomb, 2);
      _set_danger_zone();
      sWay	safe;

      for (auto &y : _way)
	{
	  for (auto &x : y)
	    {
	      if (x._count != -1 && x._danger == 0 && (x._count < safe._count || safe._count == -1))
		safe = x;
	    }
	}
      if (safe._count != -1 && safe._count <= 3 && _way[_pos._y][_pos._x]._goal == 1)
	Drop_bomb();
      if (static_cast<int>(pos.X) % 10 == 5 && static_cast<int>(pos.Z) % 10 == 5)
	{
	  if (_script_level.find(_level) != _script_level.end())
	    (this->*_script_level[_level])();
	  else
	    (this->*_script_level[eAILevel::HARD])();
	}
      else if (Move(_heading) == false)
	{
	  switch (_heading)
	    {
	    case eHeading::UP:
	      Move(eHeading::DOWN);
	      break ;
	    case eHeading::DOWN:
	      Move(eHeading::UP);
	      break ;
	    case eHeading::LEFT:
	      Move(eHeading::RIGHT);
	      break ;
	    case eHeading::RIGHT:
	      Move(eHeading::LEFT);
	      break ;
	    }
	}
      if (_map->Get_element(_pos)->Get_type() == BoxType::eBoxType::EXPLOSION)
	{
	  if (_extra_life == false)
	    {
	      Kill_it();
	      return ;
	    }
	  _extra_life = false;
	  _map->Set_element(Get_pos(), new Empty{Get_pos(), *_map, _meshesLoader, _imagesLoader});
	}
      _node->animateJoints();
    }
}
