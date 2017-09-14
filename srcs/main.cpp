#include <iostream>
#include <irrlicht.h>
#include <fstream>
#ifdef __unix__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#endif
#include "HighScores.hh"
#include "ViewsInstantiator.hh"
#include "ViewManager.hh"
#include "RessourcesLoader.hh"
#include "MultipleEventReceiver.hh"
#include "RessourcesMissingException.hh"
#include "Game.hh"
#include "Map.hh"
#include "IrrlichtEnvFinder.hh"
#include "SoundManager.hh"
#include "SkipEventReceiver.hh"
#include "Intro.hh"

int					check_requirements()
{
  std::fstream				fs;

  fs.open("./indie_ressources/images/studio_logo.png", std::fstream::in | std::fstream::out);
  if (fs.is_open())
    {
      fs.close();
      return (0);
    }
#ifdef __unix__
  if (0 != chdir("/usr/bin"))
    return (1);
#endif
#ifdef _WIN32
  if (0 == SetCurrentDirectory("/usr/bin"))
    return (1);
#endif
  fs.open("./indie_ressources/assets/studio_logo.png", std::fstream::in | std::fstream::out);
  if (fs.is_open())
    {
      fs.close();
      return (0);
    }
  return (1);
}

int				main()
{
  if (check_requirements() == 1)
    {
      std::cerr << "/ ! \\ You must start the binary from where the ressources are installed."
  		<< std::endl << "Otherwise you need to perform a sudo make install." << std::endl;
      return (1);
    }

  try
    {
      IrrlichtEnvFinder		irr_env;
      RessourcesLoader		ressources{irr_env};
      irr_env.Get_skin()->setFont(ressources.Get_ressources_menu()->Get_font("indie_ressources/fonts/bigfont.png"));
      irr_env.Get_skin()->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,255,255,0));
      SoundManager		sound_manager{irr_env.Get_sound_engine(), ressources.Get_audio_loader()};
      OptionsManager		settings{"indie_persistent_data/options/options.sqo", &sound_manager};
      Intro			intro(irr_env.Get_device(), &sound_manager, &ressources);
      intro.Lemme_splash();
      sound_manager.Play_music_menu();
      RessourcesMenuLoader	*ressources_menu{ressources.Get_ressources_menu()};
      GameParameters		game_parameters{"indie_persistent_data/settings/settings.sqgp"};
      HighScores		high_scores("indie_persistent_data/scores/high_scores", irr_env.Get_logger());
      ViewsInstantiator		views_instantiator{ressources_menu, ressources.Get_images_loader(), game_parameters, settings, high_scores};
      ViewManager		view_manager{irr_env.Get_gui(), views_instantiator.Get_views()};
      bool			stop{false};
      SaveInformation		save_info;
      MultipleEventReceiver	events{&view_manager, &settings, &game_parameters, stop, save_info};
      view_manager.Set_view(ViewID::MAIN_MENU);
      irr_env.Get_device()->setEventReceiver(&events);
      while (irr_env.Get_device()->run() && !stop)
	{
	  irr_env.Get_video_driver()->beginScene(true, true, irr::video::SColor{0, 100, 100, 100});
	  if (view_manager.View_have_changed())
	    {
	      view_manager.Charge_gui_elements_last_view(irr_env.Get_device_dimensions());
	    }
	  if (view_manager.Get_current_view() == ViewID::GAME)
	    {
	      if (!save_info.Is_a_save())
		{
		  Game				a_game{game_parameters, settings, irr_env.Get_device(), &ressources, &sound_manager, &high_scores};
		  a_game.Event_loop();
		}
	      else
		{
		  Game				a_game{save_info.Get_path(), settings, irr_env.Get_device(), &ressources, &sound_manager, &high_scores};
		  a_game.Event_loop();
		}
	      irr_env.Get_device()->setEventReceiver(&events);
	      view_manager.Set_view(ViewID::MAIN_MENU);
	      high_scores.Refresh_high_scores();
	      save_info.Reset_save_info();
	    }
	  irr_env.Get_gui()->drawAll();
	  irr_env.Get_video_driver()->endScene();
	}
      return (0);
    }
  catch (std::exception &e)
    {
      std::cerr << e.what();
      return (1);
    }
  return (0);
}
