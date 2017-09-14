#include "UpRange.hh"

UpRange::UpRange(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABonus(BoxType::eBoxType::BONUS_UPGRADE_RANGE, pos, map, mesh, img)
{
  _meshi->setMaterialTexture(0, _img->Get_texture("indie_ressources/textures/range.png"));
}

UpRange::UpRange(const UpRange &other) :
  ABonus(other)
{
}

UpRange		&UpRange::operator=(const UpRange &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

void		UpRange::Apply(ACharacter &character) const
{
  character.Inc_range_bomb();
}
