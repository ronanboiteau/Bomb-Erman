#ifndef SCORES_VIEW_EVENT_EXCEPTION_HH_
# define SCORES_VIEW_EVENT_EXCEPTION_HH_

# include <exception>
# include <string>

class		ScoresViewEventReceiverException : public std::exception
{
private:
  std::string	_msg;
public:
  ScoresViewEventReceiverException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~ScoresViewEventReceiverException() = default;
};

#endif /* !SCORES_VIEW_EVENT_EXCEPTION */
