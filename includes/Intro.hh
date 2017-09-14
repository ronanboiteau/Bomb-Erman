#ifndef INTRO_HH_
# define INTRO_HH_

# include <chrono>
# include <thread>
# include <irrlicht.h>
# include <iostream>
# include "SoundManager.hh"
# include "RessourcesLoader.hh"
# include "SkipEventReceiver.hh"

class Intro {
public:
  Intro(irr::IrrlichtDevice *device, SoundManager *sound_manager, RessourcesLoader *ressources);
  ~Intro();

  void				Lemme_splash();

private:
  irr::IrrlichtDevice			*_device;
  irr::video::IVideoDriver		*_driver;
  irr::scene::ISceneManager		*_sceneManager;
  SkipEventReceiver			_event;
  irr::scene::ICameraSceneNode		*_camera;
  SoundManager				*_sound_manager;

  irr::scene::IMeshSceneNode		*_floor;
  irr::scene::IMeshSceneNode		*_sky;
  irr::scene::IAnimatedMesh		*_sydneyMesh;
  irr::scene::IAnimatedMeshSceneNode	*_sydney;
  irr::scene::EMD2_ANIMATION_TYPE	_is_moving;
  bool					_action;

  irr::scene::ISceneNode		*_studio_logo;
  irr::scene::ISceneNode		*_game_logo;
  irr::scene::IAnimatedMesh		*_bomb_mesh;
  irr::scene::IAnimatedMeshSceneNode	*_bomb_node;
  irr::scene::IBillboardSceneNode	*_explosion;
  int					_step;
  irr::gui::IGUIFont			*_font;
  AudioLoader				*_audio;
  MeshesLoader				*_meshes;
  ImagesLoader				*_images;

  void					_pop_studio_logo();
  void					_pop_game_logo();
  void					_pop_bomb();
  void					_pop_explosion();
  void					_sydney_doing_stuff(std::chrono::time_point
							    <std::chrono::system_clock> const &t);
};

#endif
