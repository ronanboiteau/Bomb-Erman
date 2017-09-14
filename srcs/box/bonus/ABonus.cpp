#include "ABonus.hh"

ABonus::ABonus(BoxType::eBoxType type, Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABox(type, pos, map, mesh, img)
{
  _meshi = _map->Get_scene_manager().addCubeSceneNode(5.0f, _map->Get_scene_manager().getRootSceneNode(), -1);
  _meshi->setPosition(irr::core::vector3df(5 + (pos._x*10), 5, 5 + (pos._y*10)));
  _meshi->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _meshi->setRotation(irr::core::vector3df(0, 180, 0));
}

ABonus::ABonus(const ABonus &other) :
  ABox(other)
{
}

ABonus		&ABonus::operator=(const ABonus &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

void	ABonus::Rotate()
{
  irr::core::vector3df	rot = _meshi->getRotation();
  rot.Y += 1;
  _meshi->setRotation(rot);
}

ABonus::~ABonus()
{
  _meshi->remove();
}
