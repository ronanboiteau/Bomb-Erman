#include <iostream>
#include "IrrlichtEnvFinderException.hh"
#include "IrrlichtEnvFinder.hh"

IrrlichtEnvFinder::IrrlichtEnvFinder() :
  _engine{nullptr},
  _device{nullptr},
  _video_driver{nullptr},
  _scene_manager{nullptr},
  _logger{nullptr},
  _gui_env{nullptr},
  _skin{nullptr}
{
  irr::core::dimension2d<irr::u32>	dimensions;
  irr::IrrlichtDevice			*nulldevice;

  std::cerr << "On va creer le null device" << std::endl;
  if ((nulldevice = irr::createDevice(irr::video::EDT_NULL)) == nullptr)
    throw IrrlichtEnvFinderException("Cannot get desktop resolution :/");
  std::cerr << "Creation du null fini" << std::endl;
  dimensions = nulldevice->getVideoModeList()->getDesktopResolution();
  nulldevice->drop();
  if ((_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>{800,800}, 32)) == nullptr)
    throw IrrlichtEnvFinderException("Cannot instantiate an OpenGL window");
  else if ((_engine = irrklang::createIrrKlangDevice()) == nullptr)
    throw IrrlichtEnvFinderException("Cannot use sounds :/");
  else if ((_video_driver = _device->getVideoDriver()) == nullptr
	   || (_scene_manager = _device->getSceneManager()) == nullptr
	   || (_gui_env = _device->getGUIEnvironment()) == nullptr
	   || (_logger = _device->getLogger()) == nullptr
	   || (_skin = _gui_env->getSkin()) == nullptr)
  std::cerr << "fin du irrlicht env finder" << std::endl;
}

irrklang::ISoundEngine		*IrrlichtEnvFinder::Get_sound_engine()
{
  return (_engine);
}

irr::ILogger			*IrrlichtEnvFinder::Get_logger()
{
  return (_logger);
}

irr::IrrlichtDevice		*IrrlichtEnvFinder::Get_device()
{
  return (_device);
}

irr::scene::ISceneManager	*IrrlichtEnvFinder::Get_scene_manager()
{
  return (_scene_manager);
}

irr::video::IVideoDriver	*IrrlichtEnvFinder::Get_video_driver()
{
  return (_video_driver);
}

irr::gui::IGUIEnvironment	*IrrlichtEnvFinder::Get_gui()
{
  return (_gui_env);
}

irr::gui::IGUISkin		*IrrlichtEnvFinder::Get_skin()
{
  return (_skin);
}

const irr::core::dimension2d<irr::s32>	IrrlichtEnvFinder::Get_device_dimensions() const
{
  irr::core::dimension2d<irr::u32>	ret_b{_device->getVideoModeList()->getDesktopResolution()};
  irr::core::dimension2d<irr::s32>	ret;

  ret.Width = ret_b.Width;
  ret.Height = ret_b.Height;
  return (irr::core::dimension2d<irr::s32>{800,800});
}

IrrlichtEnvFinder::~IrrlichtEnvFinder()
{
  if (_engine)
    _engine->drop();
  if (_device)
    _device->drop();
}
