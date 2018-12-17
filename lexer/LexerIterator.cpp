#include "lexer/LexerIterator.hpp"

#include <cctype>

namespace lexer {

LexerIterator::LexerIterator(const std::string& str)
    : m_iterator(str.cbegin()), m_end(str.cend()) {}

void LexerIterator::next_word() {
  for (; m_iterator < m_end && std::isblank(*m_iterator); ++m_iterator)
    ;
}

void LexerIterator::next_blank() {
  for (; m_iterator < m_end && not std::isblank(*m_iterator); ++m_iterator)
    ;
}

LexerIterator::it LexerIterator::iterator() const { return m_iterator; }
LexerIterator::it LexerIterator::end() const { return m_end; }
LexerIterator::it LexerIterator::operator++() { return ++m_iterator; }
const char& LexerIterator::operator*() { return *m_iterator; }

}  // namespace lexer
