#pragma once
#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "lexer/Token.hpp"

#include <deque>

namespace parser {

class Handler {
 protected:
  using iterator = std::deque<lexer::Token>::const_iterator;
  std::size_t m_token_processed = 0;

 public:
  virtual ~Handler() = default;
  virtual void check(iterator i, iterator end) = 0;

  auto token_processed() const { return m_token_processed; }

  static Handler* get_handler(const lexer::Token& token);
};

}  // namespace parser
#endif  // HANDLER_HPP
