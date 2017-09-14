#ifndef RESSOURCES_MENU_LOADER_HH_
# define RESSOURCES_MENU_LOADER_HH_

# include <unordered_map>
# include <vector>
# include <string>
# include <irrlicht.h>
# include "MonitoredLoader.hh"

class	RessourcesMenuLoader final : public MonitoredLoader
{
private:
  std::vector<std::string>	_saves;
  std::unordered_map<std::string, irr::gui::IGUIFont*>	_fonts;
  void			loader(irr::gui::IGUIEnvironment *gui_env,
			       const std::string &saves_dir_str,
			       const std::string &fonts_path_str);
public:
  RessourcesMenuLoader(irr::gui::IGUIEnvironment *gui_env);
  RessourcesMenuLoader(const RessourcesMenuLoader &other_copy) = delete;
  RessourcesMenuLoader	&operator=(const RessourcesMenuLoader &other_affectation_copy) = delete;
  irr::gui::IGUIFont*	Get_font(const std::string &font_path);
  const std::vector<std::string>	&Get_saves() const;
  ~RessourcesMenuLoader() = default;
};

#endif /* !RESSOURCES_MENU_LOADER_HH_ */
