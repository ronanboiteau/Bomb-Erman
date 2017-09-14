#ifndef SAVES_VIEW_EVENT_RECEIVER_HH_
# define SAVES_VIEW_EVENT_RECEIVER_HH_

# include "SaveInformation.hh"
# include "AViewEventReceiver.hh"

class			SavesViewEventReceiver final : public AViewEventReceiver
{
private:
  SaveInformation	&_save;
  std::vector<SGuiElem>	&_elements;
public:
  SavesViewEventReceiver(ViewManager *vm, SaveInformation &save);
  bool			OnEvent(const irr::SEvent &event);
  ~SavesViewEventReceiver() = default;
};

#endif /* !SAVES_VIEW_EVENT_RECEIVER_HH_ */
