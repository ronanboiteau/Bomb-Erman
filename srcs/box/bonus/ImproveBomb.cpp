#include "ImproveBomb.hh"

ImproveBomb::ImproveBomb(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABonus(BoxType::eBoxType::BONUS_MASTER_BOMB, pos, map, mesh, img)
{
  _meshi->setMaterialTexture(0, _img->Get_texture("indie_ressources/textures/master.jpg"));
}

ImproveBomb::ImproveBomb(const ImproveBomb &other) :
  ABonus(other)
{
}

ImproveBomb	&ImproveBomb::operator=(const ImproveBomb &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

void		ImproveBomb::Apply(ACharacter &character) const
{
  character.Set_master_bomb(true);
}
