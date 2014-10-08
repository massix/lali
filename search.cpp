#include "search.h"

std::string todo::highlight_search_term(std::string const & p_search_term, std::string const & p_text)
{
  auto l_result = p_text;

  auto l_pos = l_result.find(p_search_term);
  if (l_pos != std::string::npos)
  {
    l_result.insert(l_pos + p_search_term.size(), "$END$");
    l_result.insert(l_pos, "$BEGIN$");
  }

  return l_result;
}

