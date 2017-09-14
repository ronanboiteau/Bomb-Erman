#include "SGuiElem.hh"
#include <iostream>

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiButtonParams &gbp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _BtnParams{gbp}
{
}

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiCheckBoxParams &cbp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _ChkBxParams{cbp}
{
}

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiComboBoxParams &cbp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _CmboBxParams{cbp}
{
}

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiScrollBarParams &sbp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _SBarParams{sbp}
{
}

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiStaticTextParams &sbp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _StaticTextParams{sbp}
{
}

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiListBoxParams &lbp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _LstBxParams{lbp}
{
}

SGuiElem::SGuiElem(GuiType type, irr::s32 id, irr::s32 distance_from_top_border, irr::s32 distance_from_left_border, const SGuiEditBoxParams &ebp) :
  _type{type},
  _id{id},
  _distance_from_top_border{distance_from_top_border},
  _distance_from_left_border{distance_from_left_border},
  _EdtBxParams{ebp}
{
}

SGuiElem::SGuiElem(const SGuiElem &other_copy) :
  _type{other_copy._type},
  _id{other_copy._id},
  _distance_from_top_border{other_copy._distance_from_top_border},
  _distance_from_left_border{other_copy._distance_from_left_border}
{
  switch (_type)
    {
    case GuiType::BUTTON:
      _BtnParams = other_copy._BtnParams;
      break;
    case GuiType::CHECK_BOX:
      _ChkBxParams = other_copy._ChkBxParams;
      break;
    case GuiType::SCROLL_BAR:
      _SBarParams = other_copy._SBarParams;
      break;
    case GuiType::STATIC_TEXT:
      _StaticTextParams = other_copy._StaticTextParams;
      break;
    case GuiType::EDIT_BOX:
      _EdtBxParams = other_copy._EdtBxParams;
      break;
    case GuiType::COMBO_BOX:
      _CmboBxParams = other_copy._CmboBxParams;
      break;
    case GuiType::LIST_BOX:
      _LstBxParams = other_copy._LstBxParams;
      break;
    }
}

SGuiElem	&SGuiElem::operator=(const SGuiElem &other_copy)
{
  if (this == &other_copy)
    return (*this);
  _type = other_copy._type;
  _id = other_copy._id;
  _distance_from_top_border = other_copy._distance_from_top_border;
  _distance_from_left_border = other_copy._distance_from_left_border;
  switch (_type)
    {
    case GuiType::BUTTON:
      _BtnParams = other_copy._BtnParams;
      break;
    case GuiType::CHECK_BOX:
      _ChkBxParams = other_copy._ChkBxParams;
      break;
    case GuiType::SCROLL_BAR:
      _SBarParams = other_copy._SBarParams;
      break;
    case GuiType::STATIC_TEXT:
      _StaticTextParams = other_copy._StaticTextParams;
      break;
    case GuiType::EDIT_BOX:
      _EdtBxParams = other_copy._EdtBxParams;
      break;
    case GuiType::COMBO_BOX:
      _CmboBxParams = other_copy._CmboBxParams;
      break;
    case GuiType::LIST_BOX:
      _LstBxParams = other_copy._LstBxParams;
      break;
    }
  return (*this);
}

SGuiElem::~SGuiElem()
{
}
