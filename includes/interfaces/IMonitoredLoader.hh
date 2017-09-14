#ifndef IMONITORED_LOADER_HH_
# define IMONITORED_LOADER_HH_

# include <cstddef>

class	IMonitoredLoader
{
private:
public:
  virtual bool		Get_status(size_t &percentage_to_fill) = 0;
  virtual const std::string	&Get_error_str() const = 0;
  virtual ~IMonitoredLoader() = default;
};

#endif /* !IMONITORED_LOADER_HH_ */
