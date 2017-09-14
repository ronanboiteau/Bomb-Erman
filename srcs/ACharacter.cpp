#include <iostream>
#include "ACharacter.hh"
#include "Breakable.hh"
#include "ABox.hh"
#include "Legacy.hh"
#include "ABonus.hh"
#include "Empty.hh"
#include "Bomb.hh"
#include "AI.hh"

ACharacter::ACharacter(const std::wstring &name, eColor color, Position pos, Map &map, eHeading heading, size_t id, SoundManager *sound, bool is_AI, MeshesLoader *meshesLoader, ImagesLoader *imagesLoader) :
  _name(name),
  _color(color),
  _map(&map),
  _heading(heading),
  _id(id),
  _extra_life(false),
  _range_bomb(3),
  _sim_bomb(1),
  _score(0),
  _has_master_bomb(false),
  _pos(pos),
  _is_AI(is_AI),
  _am_i_dead(false),
  _active_bombs(0),
  _sound(sound),
  _meshesLoader(meshesLoader),
  _imagesLoader(imagesLoader)
{
}

size_t	ACharacter::Get_id() const
{
  return (_id);
}

ACharacter::ACharacter(const std::wstring &)
{
}

ACharacter::ACharacter(const ACharacter &character) :
  _name(character._name),
  _color(character._color),
  _map(character._map),
  _heading(character._heading),
  _id(character._id),
  _extra_life(character._extra_life),
  _range_bomb(character._range_bomb),
  _sim_bomb(character._sim_bomb),
  _score(character._score),
  _has_master_bomb(character._has_master_bomb),
  _pos(character._pos),
  _am_i_dead(character._am_i_dead),
  _active_bombs(character._active_bombs),
  _sound(character._sound),
  _meshesLoader(character._meshesLoader),
  _imagesLoader(character._imagesLoader)
{
}

ACharacter	&ACharacter::operator=(const ACharacter &character)
{
  if (this != &character)
    {
      _name = character._name;
      _color = character._color;
      _extra_life = character._extra_life;
      _range_bomb = character._range_bomb;
      _sim_bomb = character._sim_bomb;
      _score = character._score;
      _pos = character._pos;
      _map = character._map;
      _am_i_dead = character._am_i_dead;
      _active_bombs = character._active_bombs;
      _sound = character._sound;
      _meshesLoader = character._meshesLoader;
      _imagesLoader = character._imagesLoader;
    }
  return (*this);
}

std::wstring const	&ACharacter::Get_name() const
{
  return (_name);
}

eColor		ACharacter::Get_color() const
{
  return (_color);
}

eHeading	ACharacter::Get_heading() const
{
  return (_heading);
}

bool		ACharacter::Has_extra_life() const
{
  return (_extra_life);
}

size_t		ACharacter::Get_range_bomb() const
{
  return (_range_bomb);
}

size_t		ACharacter::Get_sim_bomb() const
{
  return (_sim_bomb);
}

size_t		ACharacter::Get_score() const
{
  return (_score);
}

irr::scene::IAnimatedMeshSceneNode	*ACharacter::Get_node()
{
  return (_node);
}

bool		ACharacter::Is_AI() const
{
  return (_is_AI);
}

Position	ACharacter::Get_pos() const
{
  return (_pos);
}

bool		ACharacter::Has_master_bomb() const
{
  return (_has_master_bomb);
}

void		ACharacter::Set_name(const std::wstring &name)
{
  _name = name;
}

void		ACharacter::Set_color(eColor color)
{
  _color = color;
}

void		ACharacter::Set_extra_life(bool extra_life)
{
  _extra_life = extra_life;
}

void		ACharacter::Inc_range_bomb()
{
  _range_bomb += 1;
}

void		ACharacter::Inc_sim_bomb()
{
  _sim_bomb += 1;
}

void		ACharacter::Add_score(size_t score)
{
  _score += score;
}

void		ACharacter::Set_master_bomb(bool has_master_bomb)
{
  _has_master_bomb = has_master_bomb;
}

bool			ACharacter::check_move(eHeading action)
{
  irr::core::vector3df  pos = _node->getPosition();
  Position		pos2 = _pos;

  if (action == eHeading::UP)
    pos2._x = (pos.X - 5) / 10;
  else if (action == eHeading::LEFT)
    pos2._y = (pos.Z - 5) / 10;
  else if (action == eHeading::DOWN)
    pos2._x = (pos.X + 5) / 10;
  else if (action == eHeading::RIGHT)
    pos2._y = (pos.Z + 5) / 10;
  if (_map->Get_element(pos2)->Get_type() == BoxType::eBoxType::BLOCK_BREAKABLE ||
      _map->Get_element(pos2)->Get_type() == BoxType::eBoxType::BLOCK_UNBREAKABLE ||
      (_map->Get_element(pos2)->Get_type() == BoxType::eBoxType::BOMB_REGULAR &&
       &static_cast<Bomb *>(_map->Get_element(pos2))->Get_owner() != this) ||
      (_map->Get_element(pos2)->Get_type() == BoxType::eBoxType::BOMB_MASTER &&
       &static_cast<Bomb *>(_map->Get_element(pos2))->Get_owner() != this))
    return (true);
  return (false);
}

bool		ACharacter::Move(eHeading action)
{
  irr::core::vector3df  pos;

  SetRotation(action);
  if (!check_move(action))
    {
      pos = _node->getPosition();
      if (action == eHeading::UP)
	pos.X--;
      else if (action == eHeading::LEFT)
	pos.Z--;
      else if (action == eHeading::DOWN)
	pos.X++;
      else if (action == eHeading::RIGHT)
	pos.Z++;
      _node->setPosition(pos);
      _pos._x = pos.X / 10;
      _pos._y = pos.Z / 10;
      if (_is_moving != 1)
	{
	  _node->setMD2Animation(irr::scene::EMAT_RUN);
	  _is_moving = 1;
	}
      return (true);
    }
  return (false);
}

void                  ACharacter::SetPosition(int x, int y, int z)
{
  _node->setPosition(irr::core::vector3df(x, y, z));
}

void                  ACharacter::SetRotation(eHeading h)
{
  if (h != _heading)
    {
      irr::core::vector3df rot;
      switch (_heading)
	{
	case eHeading::UP:
	  _heading = eHeading::RIGHT;
	  break ;
	case eHeading::RIGHT:
	  _heading = eHeading::DOWN;
	  break ;
	case eHeading::DOWN:
	  _heading = eHeading::LEFT;
	  break ;
	case eHeading::LEFT:
	  _heading = eHeading::UP;
	  break ;
	}
      rot = _node->getRotation();
      rot.Y += 90;
      _node->setRotation(rot);
      SetRotation(h);
      // on pivote dans le sens horaire jusqu'à ce que le perso soit dans le bon sens
    }
  else
    return ;
}

void		ACharacter::Drop_bomb()
{
  if (_sim_bomb > _active_bombs &&
      _map->Get_element(_pos)->Get_type() == BoxType::eBoxType::EMPTY)
    {
      _active_bombs += 1;
      if (_has_master_bomb)
	{
	  _map->Set_element(_pos, new Bomb(BoxType::eBoxType::BOMB_MASTER, _pos, _range_bomb, *_map, *this, _sound, _meshesLoader, _imagesLoader));
	  _has_master_bomb = false;
	}
      else
	_map->Set_element(_pos, new Bomb(BoxType::eBoxType::BOMB_REGULAR, _pos, _range_bomb, *_map, *this, _sound, _meshesLoader, _imagesLoader));
    }
}

void	ACharacter::Decrement_active_bombs()
{
  if (_active_bombs > 0)
    _active_bombs -= 1;
}

void	ACharacter::Spawn()
{
  if (Am_i_dead())
    {
      _is_moving = 0;
      return ;
    }
  _mesh = _meshesLoader->Get_mesh("indie_ressources/assets/sydney.md2");
  _node = _map->Get_scene_manager().addAnimatedMeshSceneNode(_mesh);
  _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _node->setMD2Animation(irr::scene::EMAT_STAND); // animation du perso STAND || RUN
  _is_moving = 0;
  switch (_color)
    {
    case eColor::RED :
      _node->setMaterialTexture(0, _imagesLoader->Get_texture("indie_ressources/textures/red.png"));
      break ;
    case eColor::BLUE :
      _node->setMaterialTexture(0, _imagesLoader->Get_texture("indie_ressources/textures/blue.png"));
      break ;
    case eColor::GREEN :
      _node->setMaterialTexture(0, _imagesLoader->Get_texture("indie_ressources/textures/green.png"));
      break ;
    case eColor::ORANGE :
      _node->setMaterialTexture(0, _imagesLoader->Get_texture("indie_ressources/textures/yellow.png"));
      break ;
    default:
      break ;
    }
  _node->setScale(irr::core::vector3df(0.25f, 0.25f, 0.25f)); // on divise la taille du perso par 4
  _node->setPosition(irr::core::vector3df(_pos._x * 10 + 5, 5, _pos._y * 10 + 5));
  _node->setTransitionTime(5);
}

void			ACharacter::Take_bonus()
{
  Take_bonus(_pos);
}

void			ACharacter::Take_bonus(const Position &pos)
{
  BoxType::eBoxType	box_type;

  box_type = _map->Get_element(pos)->Get_type();
  switch (box_type)
    {
    case (BoxType::eBoxType::BONUS_EXTRA_LIFE) :
      {
	_sound->Play_sound_powerup();
	_score += 45;
	static_cast<ABonus *>(_map->Get_element(pos))->Apply(*this);
	_map->Set_element(pos, new Empty(pos, *_map, _meshesLoader, _imagesLoader));
	break ;
      }
    case (BoxType::eBoxType::BONUS_MASTER_BOMB) :
      {
	_sound->Play_sound_powerup();
	_score += 35;
	static_cast<ABonus *>(_map->Get_element(pos))->Apply(*this);
	_map->Set_element(pos, new Empty(pos, *_map, _meshesLoader, _imagesLoader));
	break ;
      }
    case (BoxType::eBoxType::BONUS_SIM_BOMB) :
      {
	_sound->Play_sound_powerup();
	_score += 15;
	static_cast<ABonus *>(_map->Get_element(pos))->Apply(*this);
	_map->Set_element(pos, new Empty(pos, *_map, _meshesLoader, _imagesLoader));
	break ;
      }
    case (BoxType::eBoxType::BONUS_UPGRADE_RANGE) :
      {
	_sound->Play_sound_powerup();
	_score += 5;
	static_cast<ABonus *>(_map->Get_element(pos))->Apply(*this);
	_map->Set_element(pos, new Empty(pos, *_map, _meshesLoader, _imagesLoader));
	break ;
      }
    case (BoxType::eBoxType::BONUS_LEGACY) :
      {
	_sound->Play_sound_powerup();
	static_cast<ABonus *>(_map->Get_element(pos))->Apply(*this);
	_map->Set_element(pos, new Empty(pos, *_map, _meshesLoader, _imagesLoader));
	break ;
      }
    default :
      break ;
    }
}

void	ACharacter::Set_characters(std::vector<ACharacter *> &characters)
{
  _characters = &characters;
}

void		ACharacter::Kill_it()
{
  size_t	tmp;

  tmp = (20 * _score) / 100;
  _node->remove();
  _am_i_dead = true;
  _score -= tmp;
  _map->Set_element(Get_pos(), new Legacy{Get_pos(), *_map, tmp + 100, _meshesLoader, _imagesLoader});
}

bool	ACharacter::Am_i_dead() const
{
  return (_am_i_dead);
}

void	ACharacter::Set_am_i_dead(bool am_i_dead)
{
  _am_i_dead = am_i_dead;
}

int	ACharacter::Get_is_moving() const
{
  return (_is_moving);
}

ACharacter::~ACharacter()
{
}
