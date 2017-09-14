#ifndef IRRLICHT_ENV_FINDER_HH_
# define IRRLICHT_ENV_FINDER_HH_

# include <irrlicht.h>
# include <irrKlang.h>

class	IrrlichtEnvFinder final
{
private:
  irrklang::ISoundEngine		*_engine;
  irr::IrrlichtDevice			*_device;
  irr::video::IVideoDriver		*_video_driver;
  irr::scene::ISceneManager		*_scene_manager;
  irr::ILogger				*_logger;
  irr::gui::IGUIEnvironment		*_gui_env;
  irr::gui::IGUISkin			*_skin;
public:
  IrrlichtEnvFinder();
  irrklang::ISoundEngine		*Get_sound_engine();
  irr::IrrlichtDevice			*Get_device();
  irr::scene::ISceneManager		*Get_scene_manager();
  irr::ILogger				*Get_logger();
  irr::video::IVideoDriver		*Get_video_driver();
  irr::gui::IGUIEnvironment		*Get_gui();
  irr::gui::IGUISkin			*Get_skin();
  const irr::core::dimension2d<irr::s32>		Get_device_dimensions() const;
  ~IrrlichtEnvFinder();
};

#endif /* !IRRLICHT_ENV_FINDER_HH_ */
