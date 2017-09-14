#include <iostream>
#include <fstream>
#include <sstream>
#include "HighScores.hh"

HighScores::HighScores(const std::string &file_name, irr::ILogger *logger) :
  _file_name(file_name),
  _logger(logger)
{
  std::ifstream		file(_file_name);
  std::string		player;
  std::string		score_raw;
  size_t		score = 0;
  std::vector<Score>	scores;

  if (!file.is_open())
    return ;
  while (getline(file, player) && getline(file, score_raw))
    {
      std::stringstream	stream(score_raw);
      stream >> score;
      Add_highscore(player, score);
    }
}

void			HighScores::Refresh_high_scores()
{
  std::cout << "On refresh les highscores" << std::endl;
  std::stringstream	scores_flux;

  scores_flux << "score_up: " << std::flush;
  scores_flux << _highscores.size() << std::endl;
  for (auto &it : _highscores)
    {
      scores_flux << it._username << std::endl;
      scores_flux << it._score << std::endl;
    }
  _logger->log(scores_flux.str().c_str());
}

void	HighScores::Add_highscore(const std::string &username, size_t score)
{
  if (_highscores.empty())
    {
      _highscores.push_back(Score(username, score));
      return ;
    }
  for (auto it = _highscores.begin() ; it != _highscores.end() ; ++it)
    {
      if (score >= it->_score)
	{
	  _highscores.emplace(it, Score(username, score));
	  if (_highscores.size() > 5)
	    _highscores.pop_back();
	  return ;
	}
    }
  if (_highscores.size() < 5)
    _highscores.push_back(Score(username, score));
}

const std::vector<Score>	&HighScores::Get_highscores() const
{
  return (_highscores);
}

HighScores::~HighScores()
{
  std::ofstream		file(_file_name);

  if (!file.is_open())
    return ;
  for (auto &it : _highscores)
    {
      file << it._username;
      file << std::endl;
      file << it._score;
      file << std::endl;
    }
}
