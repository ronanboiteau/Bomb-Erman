#ifndef EXTENSIONS_VALIDATOR_HH_
# define EXTENSIONS_VALIDATOR_HH_

# include <string>
# include <vector>

class			ExtensionsValidator final
{
private:
  const std::vector<std::string>	_valids_extensions;
public:
  ExtensionsValidator(const std::vector<std::string> &valid_extensions);
  ExtensionsValidator(const ExtensionsValidator &other_copy) = delete;
  ExtensionsValidator	&operator=(const ExtensionsValidator &other_affectation_copy) = delete;
  bool	operator()(const std::string &file_to_test) const;
  ~ExtensionsValidator() = default;
};

#endif /* !EXTENSIONS_VALIDATOR_HH_ */
