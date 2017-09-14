#ifndef IMULTIPLE_EVENT_RECEIVER_HH_
# define IMULTIPLE_EVENT_RECEIVER_HH_

# include <irrlicht.h>

class	IMultipleEventReceiver : public irr::IEventReceiver
{
private:
public:
  virtual bool	OnEvent(const irr::SEvent &event) = 0;
  virtual void	Add_new_event_receiver(irr::IEventReceiver *new_event_receiver) = 0;
  virtual ~IMultipleEventReceiver() = default;
};

#endif /* !IMULTIPLE_EVENT_RECEIVER_HH_ */
