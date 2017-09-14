#include "Intro.hh"

using namespace std::chrono;

Intro::Intro(irr::IrrlichtDevice *device, SoundManager *sound_manager, RessourcesLoader *ressources) :
  _device(device),
  _sound_manager(sound_manager),
  _is_moving(irr::scene::EMAT_WAVE),
  _action(true),
  _step(0),
  _font(ressources->Get_ressources_menu()->Get_font("indie_ressources/fonts/bigfont.png")),
  _audio(ressources->Get_audio_loader()),
  _meshes(ressources->Get_meshes_loader()),
  _images(ressources->Get_images_loader())
{
  _device->getCursorControl()->setVisible(false);
  _device->setWindowCaption(L"Bomb'Erman - The Salty Queens");
  _driver = _device->getVideoDriver();
  _sceneManager = _device->getSceneManager();
  _sceneManager->setAmbientLight(irr::video::SColorf(1, 1, 1, 1));
  _sceneManager->addLightSceneNode(_sceneManager->getRootSceneNode(), irr::core::vector3df(0, 0, 0));
  _device->setEventReceiver(&_event);

  _camera = _sceneManager->addCameraSceneNodeFPS(0, 0, 0.0f, -1);
  _camera->setPosition(irr::core::vector3df(-5, 52, 0));
  _camera->setTarget(irr::core::vector3df(-25, 60, 0));

  _floor = _sceneManager->addCubeSceneNode(100, _sceneManager->getRootSceneNode(), -1);
  _floor->setPosition(irr::core::vector3df(0, 0, 0));
  _floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _floor->setMaterialTexture(0, _images->Get_texture("indie_ressources/textures/grass.jpg"));
  _sceneManager->getMeshManipulator()->makePlanarTextureMapping(_floor->getMesh(), 0.4);

  irr::scene::IAnimatedMesh *nSky = _meshes->Get_mesh("indie_ressources/assets/room.3ds");
  _sky = _sceneManager->addMeshSceneNode(nSky->getMesh(0));
  _sky->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  _sceneManager->getMeshManipulator()->makePlanarTextureMapping(nSky->getMesh(0), 0.04f);
  _sky->setMaterialTexture(0, _images->Get_texture("indie_ressources/textures/sky.jpg") );

  _sydneyMesh = _meshes->Get_mesh("indie_ressources/assets/sydney.md2");
  _sydney = _sceneManager->addAnimatedMeshSceneNode(_sydneyMesh);
  _sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _sydney->setMD2Animation(irr::scene::EMAT_WAVE);
  _sydney->setMaterialTexture(0, _images->Get_texture("indie_ressources/textures/sydney.bmp"));
  _sydney->setScale(irr::core::vector3df(0.075f, 0.075f, 0.075f));
  _sydney->setPosition(irr::core::vector3df(-25, 52, 0));

  _studio_logo = NULL;
  _game_logo = NULL;
  _bomb_node = NULL;
  _bomb_mesh = NULL;
  _explosion = NULL;
}

Intro::~Intro()
{
}

void				Intro::Lemme_splash()
{
  wchar_t			titre[100];
  irr::core::vector3df		posCam;
  time_point<system_clock>	t = system_clock::now();
  time_point<system_clock>	begin = system_clock::now();

  _sound_manager->Play_music_game();
  while (_device->run())
    {
      _sydney_doing_stuff(begin);
      if (_event.IsKeyDown(irr::KEY_SPACE) || begin + milliseconds(12000) <= system_clock::now())
	break ;
      _driver->beginScene(true, true, irr::video::SColor(250, 250, 250, 250));
      if (_step == 5)
	_font->draw("PRESS SPACE TO SKIP", irr::core::rect<irr::s32>(212, 650, 450, 750), irr::video::SColor(255,255,0,0));
      _sceneManager->drawAll();
      _driver->endScene();
    }
  _device->getCursorControl()->setVisible(true);
  switch (_step)
    {
    case 5:
      _studio_logo->remove();
      return ;
    case 4:
      _explosion->remove();
      break ;
    case 3:
      {
	if (_bomb_node != NULL)
	  _bomb_node->remove();
      }
    }
  if (_step != 0)
    _game_logo->remove();
  _floor->remove();
  _sky->remove();
  _sydney->remove();
}

void	Intro::_pop_game_logo()
{
  _game_logo = _sceneManager->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(23,23), _camera->getPosition());
  _game_logo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _game_logo->setMaterialTexture(0, _images->Get_image("indie_ressources/images/game_logo.png"));
  _game_logo->setPosition(irr::core::vector3df(-25, 102, 0));
  _game_logo->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
}

void	Intro::_pop_studio_logo()
{
  _studio_logo = _sceneManager->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(40,100), _camera->getPosition());
  _studio_logo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _studio_logo->setMaterialTexture(0, _images->Get_image("indie_ressources/images/studio_logo.png"));
  _studio_logo->setPosition(irr::core::vector3df(-100, 100, 0));
  _studio_logo->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
}

void	Intro::_pop_explosion()
{
  _bomb_node->remove();
  _sound_manager->Play_sound_explosion();
  _explosion = _sceneManager->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(5,5), _camera->getPosition());
  _explosion->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _explosion->setMaterialTexture(0, _images->Get_image("indie_ressources/images/explosion.png"));
  _explosion->setPosition(irr::core::vector3df(-9, 50, -1));
  _explosion->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
}

void	Intro::_pop_bomb()
{
  _bomb_mesh = _meshes->Get_mesh("indie_ressources/assets/Bomb.md2");
  _bomb_node = _sceneManager->addAnimatedMeshSceneNode(_bomb_mesh);
  _bomb_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _bomb_node->setMaterialTexture(0, _images->Get_texture("indie_ressources/textures/bomb.tga"));
  _bomb_node->setScale(irr::core::vector3df(0.005f, 0.005f, 0.005f));
  _bomb_node->setPosition(irr::core::vector3df(-11, 50, -1));
  _bomb_node->setRotation(irr::core::vector3df(-90, 200, 0));
}

void			Intro::_sydney_doing_stuff(time_point<system_clock> const &t)
{
  irr::core::vector3df	game_pos;
  irr::core::vector3df	studio_pos;
  irr::core::vector3df	sydney_pos;

  _action = (_action == true ? false : true);
  if (t + milliseconds(2000) <= system_clock::now() && _step == 0)
    {
      sydney_pos = _sydney->getPosition();
      _sydney->setRotation(irr::core::vector3df(0, -50, 0));
      if (_action == false)
	_sydney->setPosition(irr::core::vector3df(sydney_pos.X + 1, sydney_pos.Y, sydney_pos.Z + 1));
      if (_is_moving != irr::scene::EMAT_RUN)
	{
	  _sydney->setMD2Animation(irr::scene::EMAT_RUN);
	  _is_moving = irr::scene::EMAT_RUN;
	}
      if (sydney_pos.X == -9)
	_step = 1;
    }
  else if (_step == 1)
    {
      sydney_pos = _sydney->getPosition();
      if (_game_logo == NULL)
	_pop_game_logo();
      game_pos = _game_logo->getPosition();
      _game_logo->setPosition(irr::core::vector3df(game_pos.X, game_pos.Y - 3, game_pos.Z));
      if (game_pos.Y <= 63)
	{
	  _sound_manager->Play_sound_explosion();
	  _step = 2;
	}
    }
  else if (t + milliseconds(5000) <= system_clock::now() && _step == 2)
    {
      sydney_pos = _sydney->getPosition();
      _sydney->setRotation(irr::core::vector3df(0, 50, 0));
      if (_action == false)
	_sydney->setPosition(irr::core::vector3df(sydney_pos.X, sydney_pos.Y, sydney_pos.Z - 1));
      if (sydney_pos.Z == -1)
	{
	  _sydney->setMD2Animation(irr::scene::EMAT_STAND);
	  _is_moving = irr::scene::EMAT_STAND;
	  _sydney->setRotation(irr::core::vector3df(0, 0, 0));
	  _step = 3;
	}
    }
  else if (t + milliseconds(6000) <= system_clock::now() && _step == 3)
    {
      sydney_pos = _sydney->getPosition();
      _sydney->setRotation(irr::core::vector3df(0, -50, 0));
      if (_bomb_node == NULL)
	  _pop_bomb();
      if (_action == false)
      	_sydney->setPosition(irr::core::vector3df(sydney_pos.X, sydney_pos.Y, sydney_pos.Z + 1));
      if (_is_moving != irr::scene::EMAT_RUN)
	{
	  _sydney->setMD2Animation(irr::scene::EMAT_RUN);
	  _is_moving = irr::scene::EMAT_RUN;
	}
      if (sydney_pos.Z == 16)
	_step = 4;
    }
  else if (t + milliseconds(7000) <= system_clock::now() && _step == 4)
    {
      sydney_pos = _sydney->getPosition();
      if (_explosion == NULL)
	_pop_explosion();
      irr::core::dimension2d<irr::f32> size = _explosion->getSize();
      _explosion->setSize(irr::core::dimension2d<irr::f32>(size.Height + 1, size.Width + 1));
      if (size.Height == 80)
	_step = 5;
    }
  else if (_step == 5)
    {
      if (_studio_logo == NULL)
	{
	  _floor->remove();
	  _sky->remove();
	  _sydney->remove();
	  _game_logo->remove();
	  _explosion->remove();
	  _sound_manager->Play_sound_powerup();
	  _pop_studio_logo();
	}
    }
}
