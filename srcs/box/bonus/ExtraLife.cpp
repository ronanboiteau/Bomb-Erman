#include "ExtraLife.hh"

ExtraLife::ExtraLife(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABonus(BoxType::eBoxType::BONUS_EXTRA_LIFE, pos, map, mesh, img)
{
  _meshi->setMaterialTexture(0, _img->Get_texture("indie_ressources/textures/coeur.png"));
}

ExtraLife::ExtraLife(const ExtraLife &other) :
  ABonus(other)
{
}

ExtraLife	&ExtraLife::operator=(const ExtraLife &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

void		ExtraLife::Apply(ACharacter &character) const
{
  character.Set_extra_life(true);
}
