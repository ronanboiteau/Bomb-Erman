#ifndef MONITORED_LOADER_HH_
# define MONITORED_LOADER_HH_

# include "SafeCopyable.hpp"
# include "IMonitoredLoader.hh"

class	MonitoredLoader : public IMonitoredLoader
{
private:
protected:
  SafeCopyable<size_t>	_loading_percentage;
  SafeCopyable<bool>	_loading_done;
  SafeCopyable<bool>	_loading_status;
  std::string		_error;
public:
  MonitoredLoader();
  bool		Get_status(size_t &percentage_to_fill);
  const std::string	&Get_error_str() const;
  bool		Get_loading_status();
  void			Set_loading_error(const std::string &error);
  void			Set_loading_finished();
  virtual ~MonitoredLoader() = default;
};

#endif /* !MONITORED_LOADER_HH_ */
