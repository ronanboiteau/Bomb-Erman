#include "Map.hh"
#include "Bomb.hh"
#include "Explosion.hh"

Bomb::Bomb(BoxType::eBoxType type, Position pos, size_t range, Map &map, ACharacter &owner, SoundManager *sound_manager, MeshesLoader *mesh, ImagesLoader *img) :
  ABox(type, pos, map, mesh, img),
  _time_created(std::chrono::system_clock::now()),
  _owner(owner),
  _exploded(false),
  _sound_manager(sound_manager)
{
  _meshi = mesh->Get_mesh("indie_ressources/assets/Bomb.md2");
  _node = map.Get_scene_manager().addAnimatedMeshSceneNode(_meshi);
  _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _node->setMaterialTexture(0, img->Get_texture("indie_ressources/textures/bomb.tga"));
  _node->setScale(irr::core::vector3df(0.015f, 0.015f, 0.015f));
  _node->setPosition(irr::core::vector3df(pos._x * 10 + 10, 5, pos._y * 10 + 5));
  _node->setRotation(irr::core::vector3df(75, 0, -75));
  _range = (type == BoxType::eBoxType::BOMB_MASTER ? 0 : range);
}

Bomb::Bomb(const Bomb &other) :
  ABox(other),
  _time_created(other._time_created),
  _owner(other._owner),
  _exploded(other._exploded),
  _range(other._range),
  _sound_manager(other._sound_manager)
{
}

Bomb	&Bomb::operator=(const Bomb &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  _time_created = other._time_created;
  _exploded = other._exploded;
  _sound_manager = other._sound_manager;
  _range = other._range;
  return (*this);
}

bool		Bomb::explode_box(size_t x, size_t y)
{
  Position	pos{x, y};
  bool		ret;

  ret = true;
  if (_map->Is_out_of_range(pos))
    return (false);
  ABox		*elem = _map->Get_element(pos);
  if (elem->Get_type() == BoxType::eBoxType::BLOCK_UNBREAKABLE)
    return (false);
  if (elem->Is_destroyable())
    {
      Explosion	*boom = new Explosion(pos, *_map, _mesh, _img);
      if (elem->Get_type() == BoxType::eBoxType::BLOCK_BREAKABLE)
	boom->Set_can_into_bonus(true);
      ret = !elem->Is_a_block();
      _map->Set_element(pos, boom);
    }
  else if (elem->Is_a_bomb() && static_cast<Bomb*>(elem)->_exploded != true)
    static_cast<Bomb*>(elem)->Explode();
  return (ret);
}



void		Bomb::Check_timer_state()
{
  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _time_created) > std::chrono::milliseconds(1500))
    {
      _sound_manager->Play_sound_explosion();
      Explode();
    }
}

void		Bomb::Add_to_timer(std::chrono::milliseconds const &t)
{
  _time_created += t;
}

void		Bomb::Explode()
{
  size_t	tmp = 0;
  bool		status[4] = {true, true, true, true};

  _owner.Decrement_active_bombs();
  _exploded = true;
  while (Get_type() == BoxType::eBoxType::BOMB_MASTER || tmp < _range)
    {
      if (status[0] == true)
	status[0] = explode_box(Get_pos()._x + tmp, Get_pos()._y);
      if (status[1] == true)
	status[1] = explode_box(Get_pos()._x - tmp, Get_pos()._y);
      if (status[2] == true)
	status[2] = explode_box(Get_pos()._x, Get_pos()._y + tmp);
      if (status[3] == true)
	status[3] = explode_box(Get_pos()._x, Get_pos()._y - tmp);
      if (!status[0] && !status[1] && !status[2] && !status[3])
	break ;
      ++tmp;
    }
  _map->Set_element(Get_pos(), new Explosion{Get_pos(), *_map, _mesh, _img});
}

ACharacter const &	Bomb::Get_owner() const
{
  return (_owner);
}

Bomb::~Bomb()
{
  _node->remove();
}
