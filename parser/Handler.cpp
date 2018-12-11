#include "parser/Handler.hpp"
#include "parser/Errors.hpp"

namespace parser {

void Handler::check(iterator i, iterator end) {
  assert(i != end);
  const auto& pattern = get_pattern(*i);
  iterator begin = i;
  m_token_processed = 0;
  for (const auto* ptoken : pattern) {
    if (i == end) throw ParseError(ParseError::Err::UnexpectedEOF);
    try {
      do_check(begin, i, end);
      if (m_token_processed) {
        i += m_token_processed;
        m_token_processed = 0;
        continue;
      }
    } catch (const ParseError& e) {
      throw e;
    }
    if (ptoken->optional()) {
      if (*ptoken == *i) ++i;
    } else {
      if (*ptoken != *i) throw ParseError(ParseError::Err::UnexpectedToken, *i);
      ++i;
    }
  }
  m_token_processed = i - begin;
}

}  // namespace parser
