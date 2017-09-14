#include <iostream>
#include "MyDirectory.hh"
#include "MyDirectoryException.hh"
#include "RessourcesMenuLoader.hh"
#include "RessourcesMenuLoaderException.hh"
#include "ExtensionsValidator.hh"

void	RessourcesMenuLoader::loader(irr::gui::IGUIEnvironment *gui_env,
				     const std::string &saves_dir_str,
				     const std::string &fonts_path_str)
{
  try
    {
      bool		finished{false};
      MyDirectory	saves_dir{saves_dir_str};
      MyDirectory	fonts_dir{fonts_path_str};
      ExtensionsValidator	saves_extensions{std::vector<std::string>{".sqg"}};
      ExtensionsValidator	fonts_extensions{std::vector<std::string>{".bmp", ".png"}};

      while (finished == false)
	{
	  std::string	tmp_path{saves_dir_str};

	  tmp_path += saves_dir.Get_next_filepath(finished);
	  if (!finished && saves_extensions(tmp_path))
	    _saves.push_back(tmp_path);
	}
      finished = false;
      _loading_percentage.Set_safely_value(50);
      while (finished == false)
      	{
      	  std::string	tmp_path{fonts_path_str};

      	  tmp_path += fonts_dir.Get_next_filepath(finished);
      	  if (!finished && fonts_extensions(tmp_path)
      	      && (_fonts[tmp_path] = gui_env->getFont(std::move(tmp_path.c_str()))) == nullptr)
      	    throw (RessourcesMenuLoaderException("Font invalid :/"));
      	}
      Set_loading_finished();
      return ;
    }
  catch (std::exception &e)
    {
      Set_loading_error(e.what());
    }
}

RessourcesMenuLoader::RessourcesMenuLoader(irr::gui::IGUIEnvironment *gui_env)
{
  loader(gui_env, "indie_persistent_data/saves/", "indie_ressources/fonts/");
}

const std::vector<std::string>	&RessourcesMenuLoader::Get_saves() const
{
  return (_saves);
}

irr::gui::IGUIFont	*RessourcesMenuLoader::Get_font(const std::string &font_path)
{
  return (_fonts.at(font_path));
}
