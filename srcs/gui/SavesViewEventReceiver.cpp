#include <cstdio>
#include "SavesViewEventReceiver.hh"
#include "ViewsInstantiator.hh"

SavesViewEventReceiver::SavesViewEventReceiver(ViewManager *vm, SaveInformation &save) :
  AViewEventReceiver{vm},
  _save(save),
  _elements{vm->Get_elems_for_view(ViewID::SAVES)}
{
}

bool	SavesViewEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType != irr::EEVENT_TYPE::EET_GUI_EVENT
      || (event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED
	  && event.GUIEvent.EventType != irr::gui::EGUI_EVENT_TYPE::EGET_COMBO_BOX_CHANGED))
    return (false);
  switch(static_cast<ButtonsID::Saves>(event.GUIEvent.Caller->getID()))
    {
    case ButtonsID::Saves::RETURN:
      _view_manager->Set_view(ViewID::MAIN_MENU);;
      return (true);
    case ButtonsID::Saves::CONTINUE:
      {
	irr::gui::IGUIComboBox	*combo_box{(irr::gui::IGUIComboBox*)(_view_manager->Get_gui_env()->getRootGUIElement()->getElementFromId(static_cast<irr::s32>(ButtonsID::Saves::SAVES)))};
	irr::s32		id_save_selected{combo_box->getSelected()};
	irr::gui::IGUIListBox	*list_box{(irr::gui::IGUIListBox*)(_view_manager->Get_gui_env()->getRootGUIElement()->getElementFromId(static_cast<irr::s32>(ButtonsID::Saves::ERRORS_MESSAGE_BOX)))};
      if (id_save_selected == -1)
	{
	  list_box->addItem(L"No save file selected");
	  return (true);
	}
	std::wstring		file_name_w{combo_box->getItem(id_save_selected)};
	std::string		file_name{file_name_w.begin(), file_name_w.end()};
	std::cout << "On veut load en " << file_name << std::endl;
	_save.Set_path(file_name);
	_view_manager->Set_view(ViewID::GAME);
	return (true);
      }
    case ButtonsID::Saves::REMOVE:
      {
	irr::gui::IGUIComboBox	*combo_box{(irr::gui::IGUIComboBox*)(_view_manager->Get_gui_env()->getRootGUIElement()->getElementFromId(static_cast<irr::s32>(ButtonsID::Saves::SAVES)))};
	irr::s32		id_save_selected{combo_box->getSelected()};
	irr::gui::IGUIListBox	*list_box{(irr::gui::IGUIListBox*)(_view_manager->Get_gui_env()->getRootGUIElement()->getElementFromId(static_cast<irr::s32>(ButtonsID::Saves::ERRORS_MESSAGE_BOX)))};
      if (id_save_selected == -1)
	{
	  list_box->addItem(L"No save file selected");
	  return (true);
	}
      std::wstring		file_name_w{combo_box->getItem(id_save_selected)};
      std::string		file_name{file_name_w.begin(), file_name_w.end()};
      _elements[2]._CmboBxParams._options->erase(_elements[2]._CmboBxParams._options->binary_search(file_name_w));
      _view_manager->Charge_gui_elements_last_view(irr::core::dimension2d<irr::s32>{800,800});
      list_box = (irr::gui::IGUIListBox*)(_view_manager->Get_gui_env()->getRootGUIElement()->getElementFromId(static_cast<irr::s32>(ButtonsID::Saves::ERRORS_MESSAGE_BOX)));
      if (std::remove(file_name.c_str()) != 0)
      	list_box->addItem(L"can't delete :/");
      else
      	list_box->addItem(L"Successfully deleted !");;
      return (true);
      }
    default:
      break;
    }
  return (false);
}
