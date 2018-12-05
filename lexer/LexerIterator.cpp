#include "lexer/LexerIterator.hpp"

#include <cctype>

namespace lexer {

LexerIterator::LexerIterator(const std::string& str)
    : m_iterator(str.cbegin()), m_end(str.cend()) {}

void LexerIterator::next_word() {
  for (; m_iterator < m_end && std::isblank(*m_iterator); ++m_iterator);
}
void LexerIterator::next_blank() {
  for (; m_iterator < m_end && not std::isblank(*m_iterator); ++m_iterator);
}

} // namespace lexer
