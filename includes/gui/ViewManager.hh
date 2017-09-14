#ifndef VIEW_MANAGER_HH_
# define VIEW_MANAGER_HH_

# include <unordered_map>
# include <string>
# include "IViewManager.hh"
# include "GuiView.hh"

class	ViewManager final : public IViewManager
{
private:
  irr::gui::IGUIEnvironment			*_env;
  bool						_have_changed;
  std::unordered_map<ViewID, GuiView>		_views;
  bool						_correct_view;
  ViewID					_current_view;
public:
  ViewManager(irr::gui::IGUIEnvironment *env,
	      std::unordered_map<ViewID, GuiView> &&views);
  void	Set_view(ViewID view_id);
  std::vector<SGuiElem>	&Get_elems_for_view(ViewID id);
  ViewID	Get_current_view() const;
  void	Charge_gui_elements_last_view(const irr::core::dimension2d<irr::s32> &window_dimensions);
  irr::gui::IGUIEnvironment			*Get_gui_env();
  bool	View_have_changed() const;
  ~ViewManager() = default;
};

#endif /* !VIEW_MANAGER_HH_ */
