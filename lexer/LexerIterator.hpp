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
  void next_blank();

  const auto& iterator() const { return m_iterator; }
  const auto& end() const { return m_end; }
  const auto& operator++() { return ++m_iterator; }
  const auto& operator*() { return *m_iterator; }

  template <typename T>
  const auto& operator+=(const T& t) {
    return m_iterator += t;
  }
};

}  // namespace lexer
#endif  // LEXERITERATOR_HPP
