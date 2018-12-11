#ifndef VALUEHANDLER_HPP
#define VALUEHANDLER_HPP

#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

namespace parser {

class ValueHandler : public Handler {
 private:
  using LexerToken = lexer::Token::Type;
  static const pattern::Pattern s_pattern;
  static std::unique_ptr<ValueHandler> s_instance;

  const pattern::Pattern& get_pattern(const lexer::Token&) const override;
  void do_check(iterator, iterator, iterator) override {}
 public:

  static ValueHandler *instance() { return s_instance.get(); }
};

}  // namespace parser

#endif // VALUEHANDLER_HPP
