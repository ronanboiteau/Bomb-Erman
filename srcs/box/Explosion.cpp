#include "Empty.hh"
#include "Explosion.hh"
#include "ExtraLife.hh"
#include "ImproveBomb.hh"
#include "SimBomb.hh"
#include "UpRange.hh"
#include "GetRand.hpp"

Explosion::Explosion(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABox(BoxType::eBoxType::EXPLOSION, pos, map, mesh, img),
  _can_into_bonus(false),
  _time_created(std::chrono::system_clock::now())
{
  _meshi = _map->Get_scene_manager().addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(1,1), _map->Get_camera().getPosition());
  _meshi->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _meshi->setMaterialTexture(0, img->Get_image("indie_ressources/images/explosion.png"));
  _meshi->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
  _meshi->setPosition(irr::core::vector3df(5 + (pos._x*10), 5, 5 + (pos._y*10)));
}

Explosion::Explosion(const Explosion &other) :
  ABox(other),
  _can_into_bonus(other._can_into_bonus),
  _time_created(other._time_created),
  _meshi(other._meshi)
{
}

Explosion	&Explosion::operator=(const Explosion &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  Set_mesh(other.Get_mesh());
  return (*this);
}

void					Explosion::Check_timer_state()
{
  irr::core::dimension2d<irr::f32>	size = _meshi->getSize();
  
  if (size.Width != 10)
    _meshi->setSize(irr::core::dimension2d<irr::f32>(size.Height + 1, size.Width + 1));
  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _time_created) > std::chrono::milliseconds(500))
    end_of_explosion();
}

void	Explosion::Set_can_into_bonus(bool can_into_bonus)
{
  _can_into_bonus = can_into_bonus;
}

void	Explosion::put_bonus()
{
  GetRand<unsigned int>	rand{1, 100, static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count() - 42 / 100)};

  if (rand() >= 1 && rand() <= 5)
    _map->Set_element(Get_pos(), new ExtraLife{Get_pos(), *_map, _mesh, _img});
  else if (rand() >= 6 && rand() <= 20)
    _map->Set_element(Get_pos(), new ImproveBomb{Get_pos(), *_map, _mesh, _img});
  else if (rand() >= 21 && rand() <= 55)
    _map->Set_element(Get_pos(), new SimBomb{Get_pos(), *_map, _mesh, _img});
  else if (rand() >= 56 && rand() <= 100)
    _map->Set_element(Get_pos(), new UpRange{Get_pos(), *_map, _mesh, _img});
}

void				Explosion::end_of_explosion()
{
  unsigned int			rand_nbr;

  if (_can_into_bonus)
    {
      if (_map->Get_density() <= 33)
	{
	  GetRand<unsigned int>	rand{0, 1, static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count())};
	  rand_nbr = rand();
	}
      else if (_map->Get_density() > 33 && _map->Get_density() <= 66)
	{
	  GetRand<unsigned int>	rand{0, 2, static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count())};
	  rand_nbr = rand();
	}
      else if (_map->Get_density() > 66 && _map->Get_density() <= 100)
	{
	  GetRand<unsigned int>	rand{0, 3, static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count())};
	  rand_nbr = rand();
	}
      if (rand_nbr == 0)
	{
	  put_bonus();
	  return ;
	}
    }
  _map->Set_element(Get_pos(), new Empty{Get_pos(), *_map, _mesh, _img});
}

Explosion::~Explosion()
{
  _meshi->remove();
}

irr::scene::IBillboardSceneNode const&	Explosion::Get_mesh() const
{
  return (*_meshi);
}

void	Explosion::Set_mesh(irr::scene::IBillboardSceneNode const &mesh)
{
  *_meshi = mesh;
}

void	Explosion::Add_to_timer(std::chrono::milliseconds const &t)
{
  _time_created += t;
}
