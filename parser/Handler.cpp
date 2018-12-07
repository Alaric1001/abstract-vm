#include "parser/Handler.hpp"
#include "parser/Errors.hpp"

namespace parser {

void Handler::check(iterator i, iterator end) {
  assert(i != end);
  const auto& pattern = get_pattern(*i);
  for (m_token_processed = 0; m_token_processed < pattern.size();
       ++m_token_processed) {
    const auto& ptoken = pattern[m_token_processed];
    if (i == end) throw ParseError(ParseError::Err::UnexpectedEOF);
    if (ptoken->optional()) {
      if (*ptoken == *i)
        ++i;
      else
        --m_token_processed;
    } else {
      if (*ptoken != *i) throw ParseError(ParseError::Err::UnexpectedToken);
      ++i;
    }

    try {
      do_check(i, end);
    } catch (std::exception& e) {
      throw e;
    }
    ++m_token_processed;
  }
}

}  // namespace parser
