#ifndef IVIEWS_INSTANTIATOR_HH_
# define IVIEWS_INSTANTIATOR_HH_

# include <unordered_map>
# include "IViewManager.hh"
# include "GuiView.hh"

class	IViewsInstantiator
{
private:
public:
  virtual std::unordered_map<ViewID, GuiView>	Get_views() = 0;
  virtual ~IViewsInstantiator() = default;
};

#endif /* !IVIEWS_INSTANTIATOR_HH_ */
