#include "SimBomb.hh"

SimBomb::SimBomb(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABonus(BoxType::eBoxType::BONUS_SIM_BOMB, pos, map, mesh, img)
{
  _meshi->setMaterialTexture(0, _img->Get_texture("indie_ressources/textures/SimBomb.png"));
}

SimBomb::SimBomb(const SimBomb &other) :
  ABonus(other)
{
}

SimBomb		&SimBomb::operator=(const SimBomb &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}

void		SimBomb::Apply(ACharacter &character) const
{
  character.Inc_sim_bomb();
}
