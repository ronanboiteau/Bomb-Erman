#include <iostream>
#include "GuiViewException.hh"
#include "GuiView.hh"

GuiView::GuiView(std::vector<SGuiElem> &&elements, irr::video::ITexture *background_img) :
  _elems{std::move(elements)},
  _background_img(background_img)
{};

GuiView&	GuiView::operator=(GuiView &&other_affectation_movement) noexcept
{
  _elems = std::move(other_affectation_movement._elems);
  _background_img = other_affectation_movement._background_img;
  return (*this);
}

std::vector<SGuiElem>	&GuiView::Get_elems()
{
  return (_elems);
}

void	GuiView::Charge_gui_elements(irr::gui::IGUIEnvironment *env, const irr::core::dimension2d<irr::s32> &window_dimensions)
{
  if (env->addImage(_background_img, irr::core::position2d<irr::s32>(0,0)) == 0)
    throw GuiViewException("Could not add image to the background");
  for (auto & it : _elems)
    {
      irr::core::position2d<irr::s32>	position{(it._distance_from_left_border * window_dimensions.Width) / 100,
	  (it._distance_from_top_border * window_dimensions.Height) / 100};
      switch (it._type)
	{
	case GuiType::BUTTON:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{(it._BtnParams._dimensions.Width * window_dimensions.Width) / 100,
		(it._BtnParams._dimensions.Height * window_dimensions.Height) / 100};
	    env->addButton(irr::core::rect<irr::s32>{position,dimension}, nullptr, it._id, it._BtnParams._text);
	  }
	  break;
	case GuiType::CHECK_BOX:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{(it._ChkBxParams._dimensions.Width * window_dimensions.Width) / 100,
		(it._ChkBxParams._dimensions.Height * window_dimensions.Height) / 100};
	    irr::gui::IGUICheckBox	*box{env->addCheckBox(it._ChkBxParams._checked, irr::core::rect<irr::s32>{position, dimension}, nullptr, it._id, it._ChkBxParams._text)};
	    box->setChecked(it._ChkBxParams._checked);
	  }
	  break;
	case GuiType::SCROLL_BAR:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{(it._SBarParams._dimensions.Width * window_dimensions.Width) / 100,
		(it._SBarParams._dimensions.Height * window_dimensions.Height) / 100};

	    irr::gui::IGUIScrollBar	*sbar{env->addScrollBar(it._SBarParams._horizontal, irr::core::rect<irr::s32>{position, dimension}, nullptr, it._id)};
	    std::cout << it._SBarParams._min << "/" << it._SBarParams._pos << "/" <<  it._SBarParams._max << std::endl;
	    sbar->setPos(it._SBarParams._pos);
	    sbar->setMin(it._SBarParams._min);
	    sbar->setSmallStep(it._SBarParams._small_step);
	    sbar->setMax(it._SBarParams._max);
	    sbar->setLargeStep(it._SBarParams._large_step);
	  }
	  break;
	case GuiType::STATIC_TEXT:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{200, 30};
	    env->addStaticText(it._StaticTextParams._text->c_str(), irr::core::rect<irr::s32>{position, dimension}, it._StaticTextParams._border, it._StaticTextParams._wordwrap, nullptr, it._id, it._StaticTextParams._fill_background);
	  }
	  break;
	case GuiType::LIST_BOX:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{(it._LstBxParams._dimensions.Width * window_dimensions.Width) / 100,
		(it._LstBxParams._dimensions.Height * window_dimensions.Height) / 100};
	    env->addListBox(irr::core::rect<irr::s32>{position, dimension}, nullptr, it._id, false);
	  }
	  break;
	case GuiType::EDIT_BOX:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{(it._EdtBxParams._dimensions.Width * window_dimensions.Width) / 100,
		(it._EdtBxParams._dimensions.Height * window_dimensions.Height) / 100};
	    env->addEditBox(it._EdtBxParams._text->c_str(), irr::core::rect<irr::s32>{position, dimension}, it._EdtBxParams._border, nullptr, it._id);
	  }
	  break;
	case GuiType::COMBO_BOX:
	  {
	    irr::core::dimension2d<irr::s32>	dimension{(it._CmboBxParams._dimensions.Width * window_dimensions.Width) / 100,
		(it._CmboBxParams._dimensions.Height * window_dimensions.Height) / 100};
	    irr::gui::IGUIComboBox	*ptr{env->addComboBox(irr::core::rect<irr::s32>{position, dimension}, nullptr, it._id)};
	    size_t	idx{0};

	    while (idx < it._CmboBxParams._options->size())
	      {
		ptr->addItem((*it._CmboBxParams._options)[idx].c_str(), idx);
		++idx;
	      }
	    ptr->setSelected(it._CmboBxParams._option_idx);
	  }
	  break;
	}
    }
  (void)env;
  (void)window_dimensions;
}
