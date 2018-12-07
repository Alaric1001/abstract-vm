#pragma once
#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "lexer/Token.hpp"
#include "parser/Pattern.hpp"

#include <deque>

namespace parser {

class Handler {
 protected:
  using iterator = std::deque<lexer::Token>::const_iterator;
  std::size_t m_token_processed = 0;

 private:
  virtual const pattern::Pattern& get_pattern(const lexer::Token&) const = 0;
  virtual void do_check(iterator i, iterator end) = 0;

 public:
  virtual ~Handler() = default;
  void check(iterator i, iterator end);

  auto token_processed() const { return m_token_processed; }

  static Handler* get_handler(const lexer::Token& token);
};

}  // namespace parser
#endif  // HANDLER_HPP
