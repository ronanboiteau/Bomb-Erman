#include "OptionsViewEventReceiver.hh"
#include "ViewsInstantiator.hh"

OptionsViewEventReceiver::OptionsViewEventReceiver(ViewManager *vm, OptionsManager *om) :
  AViewEventReceiver{vm},
  _options_manager{om},
  _elements{vm->Get_elems_for_view(ViewID::OPTIONS)}
{
}

bool	OptionsViewEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType != irr::EEVENT_TYPE::EET_GUI_EVENT
      || (event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED
      && event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_SCROLL_BAR_CHANGED))
    return (false);
  switch (static_cast<ButtonsID::Options>(event.GUIEvent.Caller->getID()))
    {
    case ButtonsID::Options::RETURN:
      _view_manager->Set_view(ViewID::MAIN_MENU);
      return (true);
    case ButtonsID::Options::VSYNC:
      {
	bool	vsync_status{_options_manager->Get_vsync()};
	vsync_status = vsync_status ^ 1;
	_options_manager->Set_vsync(vsync_status);
	_elements[2]._ChkBxParams._checked = vsync_status;
	return (true);
      }
    case ButtonsID::Options::SOUNDS_VOLUME:
      {
	irr::gui::IGUIScrollBar	*scroll_bar((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller);
	_elements[1]._SBarParams._pos = scroll_bar->getPos();
	_options_manager->Set_sounds_volume(_elements[1]._SBarParams._pos);
	break;
      }
    case ButtonsID::Options::MUSICS_VOLUME:
      {
	irr::gui::IGUIScrollBar	*scroll_bar((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller);
	_elements[3]._SBarParams._pos = scroll_bar->getPos();
	_options_manager->Set_musics_volume(_elements[3]._SBarParams._pos);
	break;
      }
    default:
      break;
    }
  return (false);
}
