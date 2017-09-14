#include "SaveInformation.hh"

SaveInformation::SaveInformation() :
  _save{false},
  _save_path{""}
{
}

bool	SaveInformation::Is_a_save() const
{
  return (_save);
}

const std::string	&SaveInformation::Get_path() const
{
  return (_save_path);
}

void		SaveInformation::Reset_save_info()
{
  _save = false;
  _save_path = "";
}

void		SaveInformation::Set_path(const std::string &path)
{
  _save = true;
  _save_path = path;
}
