#include "MainViewEventReceiver.hh"
#include "ViewsInstantiator.hh"
#include "Map.hh"
#include "Settings.hh"
#include "ACharacter.hh"
#include "Player.hh"
#include "Game.hh"

MainViewEventReceiver::MainViewEventReceiver(ViewManager *vm,
					     bool &stop) :
  AViewEventReceiver{vm},
  _stop(stop)
{
}

bool	MainViewEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType != irr::EEVENT_TYPE::EET_GUI_EVENT
      || event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)
    return (false);
  switch (static_cast<ButtonsID::Main>(event.GUIEvent.Caller->getID()))
    {
    case ButtonsID::Main::OPTIONS:
      _view_manager->Set_view(ViewID::OPTIONS);
      return (true);
    case ButtonsID::Main::GAME_PARAMETERS:
      _view_manager->Set_view(ViewID::GAME_PARAMETERS);
      return (true);
    case ButtonsID::Main::GAME:
      _view_manager->Set_view(ViewID::GAME);
      return (true);
    case ButtonsID::Main::HIGHSCORES:
      _view_manager->Set_view(ViewID::HIGHSCORES);
      return (true);
    case ButtonsID::Main::EXIT:
      _stop = true;
      return (true);
    case ButtonsID::Main::HELP:
      _view_manager->Set_view(ViewID::HELP);
      return (true);
    case ButtonsID::Main::SAVES:
      _view_manager->Set_view(ViewID::SAVES);
      return (true);
    }
  return (false);
}
