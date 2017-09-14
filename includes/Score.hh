#ifndef SCORE_HH_
# define SCORE_HH_

# include <string>

class	Score final
{
private:
public:
  Score(const std::string &filename)
  {
    (void)filename;
  }
  ~Score() = default;
};

#endif /* !SCORE_HH_ */
