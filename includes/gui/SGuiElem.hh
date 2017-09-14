#ifndef SGUI_ELEM_HH_
# define SGUI_ELEM_HH_

# include <irrlicht.h>
# include <vector>
# include <string>

enum class	GuiType : size_t
  {
    BUTTON,
    CHECK_BOX,
    SCROLL_BAR,
    STATIC_TEXT,
    EDIT_BOX,
    COMBO_BOX,
    LIST_BOX
  };

struct					SGuiButtonParams
{
  irr::core::dimension2d<irr::s32>	_dimensions;
  const wchar_t				*_text;
};

struct					SGuiCheckBoxParams
{
  irr::core::dimension2d<irr::s32>	_dimensions;
  bool					_checked;
  const wchar_t				*_text;
};

struct					SGuiScrollBarParams
{
  irr::core::dimension2d<irr::s32>	_dimensions;
  bool					_horizontal;
  irr::s32				_large_step;
  irr::s32				_small_step;
  irr::s32				_pos;
  irr::s32				_min;
  irr::s32				_max;
};

struct					SGuiStaticTextParams
{
  std::wstring				*_text;
  bool					_border;
  bool					_wordwrap;
  bool					_fill_background;
};

struct					SGuiEditBoxParams
{
  std::wstring				*_text;
  irr::core::dimension2d<irr::s32>	_dimensions;
  bool					_border;
};

struct					SGuiComboBoxParams
{
  irr::core::dimension2d<irr::s32>	_dimensions;
  bool					_draw_background;
  size_t				_option_idx;
  irr::core::array<std::wstring>	*_options;
};

struct					SGuiListBoxParams
{
  irr::core::dimension2d<irr::s32>	_dimensions;
};

struct				SGuiElem
{
  GuiType			_type;
  irr::s32			_id;
  irr::s32			_distance_from_top_border;
  irr::s32			_distance_from_left_border;
  union
  {
    struct SGuiButtonParams	_BtnParams;
    struct SGuiCheckBoxParams	_ChkBxParams;
    struct SGuiScrollBarParams	_SBarParams;
    struct SGuiStaticTextParams	_StaticTextParams;
    struct SGuiComboBoxParams	_CmboBxParams;
    struct SGuiEditBoxParams	_EdtBxParams;
    struct SGuiListBoxParams	_LstBxParams;
  };
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiButtonParams &gbp);
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiStaticTextParams &sbp);
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiScrollBarParams &sbp);
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiCheckBoxParams &cbp);
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiEditBoxParams &ebp);
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiComboBoxParams &cpb);
  SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiListBoxParams &lbp);
  SGuiElem(const SGuiElem &other_copy);
  SGuiElem	&operator=(const SGuiElem &other_copy);
  ~SGuiElem();
};

#endif /* !SGUI_ELEM_HH_ */
