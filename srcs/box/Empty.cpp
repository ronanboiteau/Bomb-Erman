#include "Empty.hh"

Empty::Empty(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  ABox(BoxType::eBoxType::EMPTY, pos, map, mesh, img)
{
}

Empty::Empty(const Empty &other) :
  ABox(other)
{
}

Empty	&Empty::operator=(const Empty &other)
{
  if (&other == this)
    return (*this);
  Set_type(other.Get_type());
  Set_pos(other.Get_pos());
  return (*this);
}
