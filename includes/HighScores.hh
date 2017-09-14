#ifndef HIGHSCORES_HH_
# define HIGHSCORES_HH_

# include <vector>
# include <string>
# include <irrlicht.h>

struct		Score
{
  std::string	_username;
  size_t	_score;
  Score(const std::string &username, size_t score) :
    _username(username),
    _score(score)
  { };
};

class		HighScores final
{
private:
  std::vector<Score>		_highscores;
  std::string			_file_name;
  irr::ILogger			*_logger;
public:
  HighScores(const std::string &file_name, irr::ILogger *logger);
  void				Add_highscore(const std::string &username, size_t score);
  const std::vector<Score>	&Get_highscores() const;
  void				Refresh_high_scores();
  ~HighScores();
};

#endif /* !HIGHSCORES_HH_ */
