#include "HelpViewEventReceiver.hh"
#include "ViewsInstantiator.hh"

HelpViewEventReceiver::HelpViewEventReceiver(ViewManager *vm) :
  AViewEventReceiver{vm},
  _elements{vm->Get_elems_for_view(ViewID::HELP)}
{
}

bool	HelpViewEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType != irr::EEVENT_TYPE::EET_GUI_EVENT
      || event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)
    return (false);
  if (static_cast<ButtonsID::Help>(event.GUIEvent.Caller->getID()) == ButtonsID::Help::RETURN)
    {
      _view_manager->Set_view(ViewID::MAIN_MENU);
      return (true);
    }
  return (false);
}
