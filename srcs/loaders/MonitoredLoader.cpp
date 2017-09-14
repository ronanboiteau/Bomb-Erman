#include <iostream>
#include "MonitoredLoader.hh"

MonitoredLoader::MonitoredLoader() :
  _loading_percentage{0},
  _loading_done{false},
  _loading_status{true},
  _error{"No error occured"}
{
}

bool	MonitoredLoader::Get_status(size_t &percentage_to_fill)
{
  percentage_to_fill = _loading_percentage.Read_safely_value();
  return (_loading_done.Read_safely_value());
}

bool	MonitoredLoader::Get_loading_status()
{
  return (_loading_status.Read_safely_value());
}

const std::string	&MonitoredLoader::Get_error_str() const
{
  return (_error);
}

void			MonitoredLoader::Set_loading_finished()
{
  _loading_percentage.Set_safely_value(100);
  _loading_done.Set_safely_value(true);
  _loading_status.Set_safely_value(true);
  _error = "everything load successfully !";
}

void			MonitoredLoader::Set_loading_error(const std::string &error)
{
  _loading_percentage.Set_safely_value(100);
  _loading_done.Set_safely_value(true);
  _loading_status.Set_safely_value(false);
  _error = error;
}
