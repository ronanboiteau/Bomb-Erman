#include <chrono>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Map.hh"
#include "GetRand.hpp"
#include "Empty.hh"
#include "Unbreakable.hh"
#include "Breakable.hh"
#include "Bomb.hh"
#include "Explosion.hh"
#include "ExtraLife.hh"
#include "ImproveBomb.hh"
#include "SimBomb.hh"
#include "UpRange.hh"
#include "ABonus.hh"
#include "SavesException.hh"

Map::Map(size_t size, size_t density, irr::IrrlichtDevice *device, MeshesLoader *meshLoader, ImagesLoader *img_loader) :
  _density(density),
  _device(device),
  _meshLoader(meshLoader),
  _imgLoader(img_loader)
{
  if (size % 2 == 0)
    size += 1;
  _size = size;
  if (density > 100)
    density = 100;

  float	a = _size * 10.0 / 2.0;

  _driver = _device->getVideoDriver();
  _sceneManager = _device->getSceneManager();
  _device->getCursorControl()->setVisible(false);
  _sceneManager->setAmbientLight(irr::video::SColorf(1, 1, 1, 1));
  _sceneManager->addLightSceneNode(_sceneManager->getRootSceneNode(), irr::core::vector3df(a + 5, 100, a));

  _camera = _sceneManager->addCameraSceneNodeFPS(0, 0, 0.0f, -1);
  _camera->setPosition(irr::core::vector3df(a + 5, _size * 10, a));
  _camera->setTarget(irr::core::vector3df(a, 0, a));

  _board = Get_scene_manager().addCubeSceneNode((_size - 1) * 10, Get_scene_manager().getRootSceneNode(), -1);
  _board->setPosition(irr::core::vector3df(a - 5, - (((_size - 1) * 10 * 0.05) / 2), a - 5));
  _board->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _board->setMaterialTexture(0, _imgLoader->Get_texture("indie_ressources/textures/case.jpg"));
  _board->setScale(irr::core::vector3df(1, 0.05f, 1));
  _sceneManager->getMeshManipulator()->makePlanarTextureMapping(_board->getMesh(), 0.1);

  create_map(density);
  irr::scene::IAnimatedMesh *room = _meshLoader->Get_mesh("indie_ressources/assets/room.3ds");
  irr::scene::IMeshSceneNode *Nroom = _sceneManager->addMeshSceneNode(room->getMesh(0));
  Nroom->setPosition(irr::core::vector3df(0, -100, 200));
  Nroom->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _sceneManager->getMeshManipulator()->makePlanarTextureMapping(room->getMesh(0), 0.01f);
  Nroom->setMaterialTexture( 0, _imgLoader->Get_image("indie_ressources/images/space.jpg") );
  Nroom->setScale(irr::core::vector3df(_size / 10, _size / 10, _size / 10));
}

Map::Map(const std::string &file_path, irr::IrrlichtDevice *device, MeshesLoader *meshLoader, ImagesLoader *img_loader) :
  _density(0),
  _device(device),
  _meshLoader(meshLoader),
  _imgLoader(img_loader)
{
  std::ifstream		file(file_path);

  if (!file.is_open())
    throw SavesException("Fatal error: cannot load save file!");
  file >> _size;

  float	a = 11 * 10.0 / 2.0;

  _driver = _device->getVideoDriver();
  _sceneManager = _device->getSceneManager();
  _device->getCursorControl()->setVisible(false);
  _sceneManager->setAmbientLight(irr::video::SColorf(1, 1, 1, 1));
  _sceneManager->addLightSceneNode(_sceneManager->getRootSceneNode(), irr::core::vector3df(a + 5, 100, a));

  _camera = _sceneManager->addCameraSceneNodeFPS(0, 0, 0.0f, -1);
  _camera->setPosition(irr::core::vector3df(a + 5, 11 * 10, a));
  _camera->setTarget(irr::core::vector3df(a, 0, a));

  _board = Get_scene_manager().addCubeSceneNode((11 - 1) * 10, Get_scene_manager().getRootSceneNode(), -1);
  _board->setPosition(irr::core::vector3df(a - 5, - (((11 - 1) * 10 * 0.05) / 2), a - 5));
  _board->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _board->setMaterialTexture(0, _imgLoader->Get_texture("indie_ressources/textures/case.jpg"));
  _board->setScale(irr::core::vector3df(1, 0.05f, 1));
  _sceneManager->getMeshManipulator()->makePlanarTextureMapping(_board->getMesh(), 0.1);

  size_t		idx = 0;
  size_t		idx_line;
  create_map();
  while (idx < 11)
    {
      idx_line = 0;
      while (idx_line < 11)
	{
	  size_t		type;
	  file >> type;
	  if (static_cast<BoxType::eBoxType>(type) != BoxType::eBoxType::EMPTY && static_cast<BoxType::eBoxType>(type) != BoxType::eBoxType::BLOCK_UNBREAKABLE)
	    Set_element(Position(idx_line, idx), static_cast<BoxType::eBoxType>(type));
	  ++idx_line;
	}
      ++idx;
    }

  irr::scene::IAnimatedMesh *room = _meshLoader->Get_mesh("indie_ressources/assets/room.3ds");
  irr::scene::IMeshSceneNode *Nroom = _sceneManager->addMeshSceneNode(room->getMesh(0));
  Nroom->setPosition(irr::core::vector3df(0, -100, 200));
  Nroom->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _sceneManager->getMeshManipulator()->makePlanarTextureMapping(room->getMesh(0), 0.01f);
  Nroom->setMaterialTexture( 0, _imgLoader->Get_image("indie_ressources/images/space.jpg"));
  Nroom->setScale(irr::core::vector3df(11 / 10, 11 / 10, 11 / 10));
}

ABox	*Map::Get_element(const Position &pos) const
{
  return (_map[pos._y][pos._x]);
}

bool	Map::Is_out_of_range(const Position &pos) const
{
  return (pos._x >= _size || pos._y >= _size);
}

void	Map::Set_element(const Position &pos, BoxType::eBoxType type)
{
  ABox	*box;

  delete _map[pos._y][pos._x];
  switch (type)
    {
    case (BoxType::eBoxType::BLOCK_BREAKABLE) :
      box = new Breakable(pos, *this, _meshLoader, _imgLoader);
      break ;
    case (BoxType::eBoxType::BONUS_EXTRA_LIFE) :
      box = new ExtraLife(pos, *this, _meshLoader, _imgLoader);
      break ;
    case (BoxType::eBoxType::BONUS_MASTER_BOMB) :
      box = new ImproveBomb(pos, *this, _meshLoader, _imgLoader);
      break ;
    case (BoxType::eBoxType::BONUS_SIM_BOMB) :
      box = new SimBomb(pos, *this, _meshLoader, _imgLoader);
      break ;
    case (BoxType::eBoxType::BONUS_UPGRADE_RANGE) :
      box = new UpRange(pos, *this, _meshLoader, _imgLoader);
      break ;
    default :
      box = new Empty(pos, *this, _meshLoader, _imgLoader);
      break ;
    }
  _map[pos._y][pos._x] = box;
}

void	Map::Set_element(const Position &pos, ABox *box)
{
  delete _map[pos._y][pos._x];
  _map[pos._y][pos._x] = box;
}

bool	Map::is_safe_block(Position pos)
{
  if (pos == Position(1, 1) || pos == Position(1, 2) || pos == Position(2, 1)
      || pos == Position(_size - 2, _size - 2) || pos == Position(_size - 2, _size - 3) || pos == Position(_size - 3, _size - 2)
      || pos == Position(_size - 2, 1) || pos == Position(_size - 2, 2) || pos == Position(_size - 3, 1)
      || pos == Position(1, _size - 2) || pos == Position(1, _size - 3) || pos == Position(2, _size - 2))
    return (true);
  return (false);
}

void		Map::create_map()
{
  size_t	y = 0;
  size_t	x;

  _nb_unbreakable = 0;
  while (y < _size)
    {
      x = 0;
      std::vector<ABox *>	line;
      while (x < _size)
  	{
	  if (y == 0 || y == _size - 1 || x == 0 || x == _size - 1
	      || (y % 2 == 0 && x % 2 == 0))
	    {
 	      line.emplace_back(new Unbreakable(Position(x, y), *this, _meshLoader, _imgLoader));
	      _nb_unbreakable += 1;
	    }
	  else
	    line.emplace_back(new Empty(Position(x, y), *this, _meshLoader, _imgLoader));
  	  x += 1;
  	}
      _map.push_back(std::move(line));
      y += 1;
    }
}

void		Map::create_map(size_t density)
{
  size_t	y = 0;
  size_t	x;

  _nb_unbreakable = 0;
  while (y < _size)
    {
      x = 0;
      std::vector<ABox *>	line;
      while (x < _size)
  	{
	  if (y == 0 || y == _size - 1 || x == 0 || x == _size - 1
	      || (y % 2 == 0 && x % 2 == 0))
	    {
 	      line.emplace_back(new Unbreakable(Position(x, y), *this, _meshLoader, _imgLoader));
	      _nb_unbreakable += 1;
	    }
	  else
	    line.emplace_back(new Empty(Position(x, y), *this, _meshLoader, _imgLoader));
  	  x += 1;
  	}
      _map.push_back(std::move(line));
      y += 1;
    }
  put_breakable_blocks(density);
}

void		Map::put_breakable_blocks(size_t density)
{
  size_t	idx = 0;
  size_t	randx = 0;
  size_t	randy = 0;

  while (idx < (density * ((_size * _size) - _nb_unbreakable - 12) / 100))
    {
      do
	{
	  GetRand<size_t>	tmpx(0, _size - 1, std::chrono::system_clock::now().time_since_epoch().count() + LONG_MAX / 42);
	  GetRand<size_t>	tmpy(0, _size - 1, std::chrono::system_clock::now().time_since_epoch().count() + LONG_MAX / 42);
	  randx = tmpx();
	  randy = tmpy();
	}
      while (Get_element(Position(randx, randy))->Get_type() != BoxType::eBoxType::EMPTY);
      if (!is_safe_block(Position(randx, randy)))
	{
	  Set_element(Position(randx, randy), new Breakable(Position(randx, randy), *this, _meshLoader, _imgLoader));
	  idx += 1;
	}
    }
}

const std::vector<std::vector<ABox *> >	&Map::Get_map() const
{
  return (_map);
}

Map::~Map()
{
  for (size_t y = 0 ; y < _size ; y += 1)
    {
      for (size_t x = 0 ; x < _size ; x += 1)
	delete _map[y][x];
    }
}

irr::IrrlichtDevice &	Map::Get_device()
{
  return (*_device);
}

irr::video::IVideoDriver &	Map::Get_driver()
{
  return (*_driver);
}

irr::scene::ISceneManager &	Map::Get_scene_manager()
{
  return (*_sceneManager);
}

irr::scene::ICameraSceneNode &	Map::Get_camera()
{
  return (*_camera);
}

size_t		Map::Get_size() const
{
  return (_size);
}

size_t		Map::Get_density() const
{
  return (_density);
}

void	Map::Print_map()
{
  int	idx = 0;

  for (auto &it : _map)
    {
      for (auto &it2 : it)
  	{
	  if (it2->Get_type() == BoxType::eBoxType::BLOCK_BREAKABLE)
	    std::cout << "@";
	  else if (it2->Get_type() == BoxType::eBoxType::BLOCK_UNBREAKABLE)
	    std::cout << "█";
	  else if (it2->Get_type() == BoxType::eBoxType::EXPLOSION)
	    std::cout << "*";
	  else if (it2->Get_type() == BoxType::eBoxType::BOMB_REGULAR ||
		   it2->Get_type() == BoxType::eBoxType::BOMB_MASTER)
	    std::cout << "O";
	  else if (it2->Get_type() == BoxType::eBoxType::EMPTY)
	    std::cout << " ";
	  else if (it2->Is_a_bonus())
	    std::cout << "B";
	  else
	    std::cout << "U";
  	}
      std::cout << std::endl;
      idx += 1;
    }
}

void	Map::Try_explode_bombs()
{
  int	idx = 0;

  for (auto &it : _map)
    {
      for (auto &it2 : it)
  	{
	  if (it2->Get_type() == BoxType::eBoxType::BOMB_REGULAR ||
	      it2->Get_type() == BoxType::eBoxType::BOMB_MASTER)
	    static_cast<Bomb *>(it2)->Check_timer_state();
	  else if (it2->Get_type() == BoxType::eBoxType::EXPLOSION)
	    static_cast<Explosion *>(it2)->Check_timer_state();
	  else if (it2->Is_a_bonus())
	    static_cast<ABonus *>(it2)->Rotate();
  	}
      idx += 1;
    }
}

void	Map::Add_to_timer(std::chrono::milliseconds const &t)
{
  for (auto &it : _map)
    {
      for (auto &it2 : it)
  	{
	  if (it2->Get_type() == BoxType::eBoxType::BOMB_REGULAR ||
	      it2->Get_type() == BoxType::eBoxType::BOMB_MASTER)
	    static_cast<Bomb *>(it2)->Add_to_timer(t);
	  else if (it2->Get_type() == BoxType::eBoxType::EXPLOSION)
	    static_cast<Explosion *>(it2)->Add_to_timer(t);
  	}
    }
}
