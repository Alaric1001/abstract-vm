#pragma once
#ifndef LEXERITERATOR_HPP
#define LEXERITERATOR_HPP

#include <string>

namespace lexer {

class LexerIterator {
 public:
  using it = std::string::const_iterator;

 private:
  it m_iterator;
  it m_end;

 public:
  LexerIterator() = delete;
  LexerIterator(const std::string&);
  LexerIterator(const LexerIterator&) = default;
  LexerIterator& operator=(const LexerIterator&) = default;
  void next_word();
  void next_blank();

  it iterator() const; 
  it end() const; 
  it operator++();
  const char& operator*(); 

  template <typename T>
  const auto& operator+=(const T& t) {
    return m_iterator += t;
  }
};

}  // namespace lexer
#endif  // LEXERITERATOR_HPP
