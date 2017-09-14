#include "ABox.hh"

ABox::ABox(BoxType::eBoxType type, Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img) :
  _type(type),
  _pos(pos),
  _map(&map),
  _mesh(mesh),
  _img(img)
{
}

ABox::ABox(const ABox &other) :
  _type(other._type),
  _pos(other._pos),
  _map(other._map),
  _mesh(other._mesh),
  _img(other._img)
{
}

ABox		&ABox::operator=(const ABox &other)
{
  if (&other == this)
    return (*this);
  _type = other._type;
  _pos = other._pos;
  _map = other._map;
  return (*this);
}

BoxType::eBoxType	ABox::Get_type() const
{
  return (_type);
}

Position	ABox::Get_pos() const
{
  return (_pos);
}

bool		ABox::Is_a_block() const
{
  return (_type == BoxType::eBoxType::BLOCK_BREAKABLE ||
	  _type == BoxType::eBoxType::BLOCK_UNBREAKABLE);
}

bool		ABox::Is_a_bomb() const
{
  return (_type == BoxType::eBoxType::BOMB_REGULAR ||
	  _type == BoxType::eBoxType::BOMB_MASTER);
}

bool		ABox::Is_a_bonus() const
{
  return (_type == BoxType::eBoxType::BONUS_EXTRA_LIFE ||
	  _type == BoxType::eBoxType::BONUS_MASTER_BOMB ||
	  _type == BoxType::eBoxType::BONUS_SIM_BOMB ||
	  _type == BoxType::eBoxType::BONUS_UPGRADE_RANGE ||
	  _type == BoxType::eBoxType::BONUS_LEGACY);
}

bool		ABox::Is_destroyable() const
{
  return (_type == BoxType::eBoxType::BLOCK_BREAKABLE ||
	  _type == BoxType::eBoxType::EMPTY ||
	  _type == BoxType::eBoxType::EXPLOSION ||
	  _type == BoxType::eBoxType::BONUS_EXTRA_LIFE ||
	  _type == BoxType::eBoxType::BONUS_MASTER_BOMB ||
	  _type == BoxType::eBoxType::BONUS_SIM_BOMB ||
	  _type == BoxType::eBoxType::BONUS_UPGRADE_RANGE ||
	  _type == BoxType::eBoxType::BONUS_LEGACY);
}

void		ABox::Set_pos(const Position &pos)
{
  _pos = pos;
}

void		ABox::Set_type(BoxType::eBoxType type)
{
  _type = type;
}
