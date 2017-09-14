#ifndef VIEWS_INSTANTIATOR_HH_
# define VIEWS_INSTANTIATOR_HH_

# include <cstddef>
# include "RessourcesMenuLoader.hh"
# include "OptionsManager.hh"
# include "GameParameters.hh"
# include "IViewsInstantiator.hh"
# include "IViewManager.hh"
# include "RessourcesLoader.hh"
# include "HighScores.hh"

namespace ButtonsID
{
  enum class	Main : irr::s32
    {
      GAME = 1,
	OPTIONS = 2,
	HIGHSCORES = 3,
	SAVES = 4,
	GAME_PARAMETERS = 5,
	HELP = 6,
      EXIT = 7
	};

  enum class	Game : irr::s32
    {
      PAUSE = 0
	};

  enum class	Options : irr::s32
    {
      RETURN = 10,
	VSYNC = 11,
	SOUNDS_TEXT = 12,
	SOUNDS_VOLUME = 13,
	MUSICS_TEXT = 14,
	MUSICS_VOLUME = 15
	};

  enum class	Scores : irr::s32
    {
      RETURN = 40,
      SCORE_TEXT = 41
	};

  enum class	Help : irr::s32
    {
      RETURN = 50
	};

  enum class	Saves : irr::s32
    {
      RETURN = 60,
	CONTINUE = 61,
	REMOVE = 62,
	SAVES = 63,
	ERRORS_MESSAGE_BOX = 64
	};

  enum class	GameParameters : irr::s32
    {
      ERRORS_MESSAGE_BOX = 98,
      RETURN = 99,
	FIRST_PLAYER_EXISTENCE = 100,
	FIRST_PLAYER_IS_IA = 101,
	FIRST_PLAYER_NAME = 102,
	FIRST_PLAYER_COLOR = 103,
	FIRST_PLAYER_SCRIPT_NAME = 104,

	SECOND_PLAYER_EXISTENCE = 200,
	SECOND_PLAYER_IS_IA = 201,
	SECOND_PLAYER_NAME = 202,
	SECOND_PLAYER_COLOR = 203,
	SECOND_PLAYER_SCRIPT_NAME = 204,

	THIRD_PLAYER_EXISTENCE = 300,
	THIRD_PLAYER_IS_IA = 301,
	THIRD_PLAYER_NAME = 302,
	THIRD_PLAYER_COLOR = 303,
	THIRD_PLAYER_SCRIPT_NAME = 304,

	FOURTH_PLAYER_EXISTENCE = 400,
	FOURTH_PLAYER_IS_IA = 401,
	FOURTH_PLAYER_NAME = 402,
	FOURTH_PLAYER_COLOR = 403,
	FOURTH_PLAYER_SCRIPT_NAME = 404,

	MAP_DENSITY_TEXT = 139,
	MAP_DENSITY = 140,
	MAP_SIZE_TEXT = 141,
	MAP_SIZE = 142
	};
}

class	ViewsInstantiator final : public IViewsInstantiator
{
private:
  std::unordered_map<ViewID, GuiView>	_views;
public:
  ViewsInstantiator(RessourcesMenuLoader *ressources_menu_loader,
		    ImagesLoader *images_loader,
		    const GameParameters &game_parameters,
		    const OptionsManager &settings,
		    const HighScores &high_scores);
  std::unordered_map<ViewID, GuiView>	Get_views();
  ~ViewsInstantiator() = default;
};

#endif /* !VIEWS_INSTANTIATOR_HH_ */
