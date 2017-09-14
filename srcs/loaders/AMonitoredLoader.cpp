#include "MonitoredLoader.hh"

MonitoredLoader::MonitoredLoader() :
  _loading_percentage{0},
  _loading_done{false}
{
}

bool	MonitoredLoader::Get_status(size_t &percentage_to_fill)
{
  percentage_to_fill = _loading_percentage.Read_safely_value();
  return (_loading_done.Read_safely_value());
}
