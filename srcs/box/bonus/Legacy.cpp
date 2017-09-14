#include "Legacy.hh"

Legacy::Legacy(Position pos, Map &map, size_t score, MeshesLoader *mesh, ImagesLoader *img) :
  ABonus(BoxType::eBoxType::BONUS_LEGACY, pos, map, mesh, img),
  _score(score)
{
  _meshi->setMaterialTexture(0, _img->Get_texture("indie_ressources/textures/legacy.png"));
}

Legacy::Legacy(const Legacy &other) :
  ABonus(other)
{
}

Legacy	&Legacy::operator=(const Legacy &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

void		Legacy::Apply(ACharacter &character) const
{
  character.Add_score(_score);
}
