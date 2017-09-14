#include <iostream>
#include "ViewManager.hh"

ViewManager::ViewManager(irr::gui::IGUIEnvironment *env, std::unordered_map<ViewID, GuiView> &&views) :
  _env{env},
  _have_changed{false},
  _views{std::move(views)},
  _correct_view{false}
{
}

ViewID		ViewManager::Get_current_view() const
{
  return (_current_view);
}

std::vector<SGuiElem>	&ViewManager::Get_elems_for_view(ViewID id)
{
  return (_views.at(id).Get_elems());
}

irr::gui::IGUIEnvironment	*ViewManager::Get_gui_env()
{
  return (_env);
}

void	ViewManager::Set_view(ViewID view_id)
{
  // faire une verification de la value
  _current_view = view_id;
  _correct_view = true;
  _have_changed = true;
}

void	ViewManager::Charge_gui_elements_last_view(const irr::core::dimension2d<irr::s32> &window_dimensions)
{
  if (!_correct_view)
    return ;
  _env->clear();
  // _views.at(_current_view).Charge_background_elements(_env, window_dimensions);
  _views.at(_current_view).Charge_gui_elements(_env, window_dimensions);
  _have_changed = false;
}

bool	ViewManager::View_have_changed() const
{
  return (_have_changed);
}
