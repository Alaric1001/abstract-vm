#pragma once
#ifndef LEXERITERATOR_HPP
#define LEXERITERATOR_HPP

#include <string>

namespace lexer {

class LexerIterator {
  private:
  std::string::const_iterator m_iterator;
  std::string::const_iterator m_end;

  public:
  LexerIterator(const std::string&);
  void next_word();

  const auto& iterator() const { return m_iterator; }
  const auto& end() const { return m_end; }
  const auto& operator++() { return ++m_iterator; }
  const auto& operator*() { return *m_iterator; }
};

} // namespace lexer
#endif // LEXERITERATOR_HPP
