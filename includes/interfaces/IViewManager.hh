#ifndef IVIEW_MANAGER_HH_
# define IVIEW_MANAGER_HH_

# include <irrlicht.h>

enum class	ViewID : size_t
  {
    MAIN_MENU,
    OPTIONS,
    GAME_PARAMETERS,
    GAME,
    HELP,
    HIGHSCORES,
    SAVES
  };

class		IViewManager
{
public:
  virtual void	Set_view(ViewID view_id) = 0;
  virtual void	Charge_gui_elements_last_view(const irr::core::dimension2d<irr::s32> &window_dimensions) = 0;
  virtual bool	View_have_changed() const = 0;
  virtual ~IViewManager() = default;
};

#endif /* !IVIEW_MANAGER_HH_ */
