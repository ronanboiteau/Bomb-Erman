#include <iostream>
#include "ViewsInstantiator.hh"
#include "GameParametersViewEventReceiver.hh"

GameParametersViewEventReceiver::GameParametersViewEventReceiver(ViewManager *vm,
								 GameParameters *gp) :
  AViewEventReceiver{vm},
  _game_params{gp},
  _elements{vm->Get_elems_for_view(ViewID::GAME_PARAMETERS)},
  _is_a_player_gui{static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE), static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE) / static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE), static_cast<size_t>(ButtonsID::GameParameters::FOURTH_PLAYER_EXISTENCE) / static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE), static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_SCRIPT_NAME) - static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE)}
{
}

bool	GameParametersViewEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType != irr::EEVENT_TYPE::EET_GUI_EVENT
      || (event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED
	  && event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_CHECKBOX_CHANGED
	  && event.GUIEvent.EventType != irr::gui::EGET_COMBO_BOX_CHANGED
	  && event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_SCROLL_BAR_CHANGED
	  && event.GUIEvent.EventType != irr::gui::EGET_EDITBOX_ENTER
	  && event.GUIEvent.EventType != irr::gui::EGET_EDITBOX_CHANGED
	  && event.GUIEvent.EventType != irr::gui::EGET_EDITBOX_MARKING_CHANGED))
    return (false);
  if (_is_a_player_gui(event.GUIEvent.Caller->getID()))
    {
      size_t	base = _is_a_player_gui.Get_base();
      size_t	caller_id_without_base = event.GUIEvent.Caller->getID() - base;
      size_t	base_demin = base / static_cast<size_t>(ButtonsID::GameParameters::FIRST_PLAYER_EXISTENCE);
      switch (caller_id_without_base)
    	{
    	case (0):
    	  _game_params->Set_a_character_status(base_demin - 1, 0, ((irr::gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked());
	  _elements[((base_demin - 1) * 5) + 1]._ChkBxParams._checked = ((irr::gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
    	  break;
    	case (1):
	  _game_params->Set_a_character_status(base_demin - 1, 1, ((irr::gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked());
	  _elements[((base_demin - 1) * 5) + 2]._ChkBxParams._checked = ((irr::gui::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
    	  break;
    	case (2):
	  _game_params->Set_a_character_name(base_demin - 1, event.GUIEvent.Caller->getText());
	  _elements[((base_demin - 1) * 5) + 3]._EdtBxParams._text->assign(event.GUIEvent.Caller->getText());
	  std::wcout << _elements[((base_demin - 1) * 5) + 3]._EdtBxParams._text->c_str() << std::endl;
    	  break;
    	case (3):
	  {
	    irr::s32	color_option_idx{((irr::gui::IGUIComboBox*)event.GUIEvent.Caller)->getSelected()};
	    std::wstring	color_option_string = (*_elements[((base_demin - 1) * 5) + 4]._CmboBxParams._options)[color_option_idx];
	    _elements[((base_demin - 1) * 5) + 4]._CmboBxParams._option_idx = color_option_idx;
	    _game_params->Set_a_character_color(base_demin - 1, _color_factory.create_color(color_option_string));
	  }
	  break;
    	case (4):
	  {
	    irr::s32	level_option_idx{((irr::gui::IGUIComboBox*)event.GUIEvent.Caller)->getSelected()};
	    std::wstring	level_option_string = (*_elements[((base_demin) * 5)]._CmboBxParams._options)[level_option_idx];
	    _elements[((base_demin) * 5)]._CmboBxParams._option_idx = level_option_idx;
	    _game_params->Set_a_character_level(base_demin - 1, _level_factory.create_level(level_option_string));
	  }
	  break;
	  return (true);
	}
    }
  switch (static_cast<ButtonsID::GameParameters>(event.GUIEvent.Caller->getID()))
    {
    case ButtonsID::GameParameters::RETURN:
      {
	if (!_game_params->Parameters_are_valids())
	  {
	    ((irr::gui::IGUIListBox*)(_view_manager->Get_gui_env()->getRootGUIElement()->getElementFromId(static_cast<irr::s32>(ButtonsID::GameParameters::ERRORS_MESSAGE_BOX))))->addItem(_game_params->Get_last_error().c_str());
	    return (true);
	  }
	_view_manager->Set_view(ViewID::MAIN_MENU);
	return (true);
      }
    case ButtonsID::GameParameters::MAP_DENSITY:
      {
	irr::gui::IGUIScrollBar	*scroll_bar((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller);
	_elements[23]._SBarParams._pos = scroll_bar->getPos();
	_game_params->Set_map_density(_elements[23]._SBarParams._pos);
	return (false);
	break;
      }
    case ButtonsID::GameParameters::MAP_SIZE:
      {
	irr::gui::IGUIScrollBar	*scroll_bar((irr::gui::IGUIScrollBar*)event.GUIEvent.Caller);
	_elements[25]._SBarParams._pos = scroll_bar->getPos();
	_game_params->Set_map_size(_elements[25]._SBarParams._pos);
	break;
      }
    default:
      break;
    }
  return (false);
}
