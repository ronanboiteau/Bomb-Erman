#ifndef GUI_VIEW_HH_
# define GUI_VIEW_HH_

# include <irrlicht.h>
# include <vector>
# include "SGuiElem.hh"

class			GuiView final
{
private:
  std::vector<SGuiElem>	_elems;
  irr::video::ITexture	*_background_img;
public:
  GuiView() = default;
  GuiView(std::vector<SGuiElem> &&elements, irr::video::ITexture *background_img);
  void	Charge_gui_elements(irr::gui::IGUIEnvironment *env, const irr::core::dimension2d<irr::s32> &window_dimensions);
  void	Charge_background_elements(irr::gui::IGUIEnvironment *env, const irr::core::dimension2d<irr::s32> &window_dimensions);
  GuiView	&operator=(const GuiView &other_affectation_copy) = delete;
  GuiView(const GuiView &other_copy) = default;
  std::vector<SGuiElem>	&Get_elems();
  GuiView	&operator=(GuiView &&other_affectation_movement) noexcept;
  ~GuiView() = default;
};

#endif /* !GUI_VIEW_HH_ */
