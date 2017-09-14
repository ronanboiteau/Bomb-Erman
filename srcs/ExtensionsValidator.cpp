#include "ExtensionsValidator.hh"

ExtensionsValidator::ExtensionsValidator(const std::vector<std::string> &valid_extensions) :
  _valids_extensions{valid_extensions}
{
}

bool	ExtensionsValidator::operator()(const std::string &file_to_test) const
{
  for (auto &it_extensions : _valids_extensions)
    {
      if (file_to_test.size() > it_extensions.size() && file_to_test.substr(file_to_test.size() - it_extensions.size(), it_extensions.size()) == it_extensions)
	return (true);
    }
  return (false);
}
