#include "Breakable.hh"

Breakable::Breakable(Position pos, Map& map, MeshesLoader *mesh, ImagesLoader *img) :
  ABox(BoxType::eBoxType::BLOCK_BREAKABLE, pos, map, mesh, img)
{

  _mesh = _map->Get_scene_manager().addCubeSceneNode(10.0f, _map->Get_scene_manager().getRootSceneNode(), -1);
  _mesh->setPosition(irr::core::vector3df(5 + (pos._x*10), 5, 5 + (pos._y*10)));
  _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _mesh->setMaterialTexture(0, img->Get_texture("indie_ressources/textures/wood.jpg"));
}

Breakable::Breakable(const Breakable &other) :
  ABox(other)
{
}

Breakable	&Breakable::operator=(const Breakable &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

Breakable::~Breakable()
{
  _mesh->remove();
}

irr::scene::IMeshSceneNode const &    Breakable::Get_mesh() const
{
  return (*_mesh);
}
