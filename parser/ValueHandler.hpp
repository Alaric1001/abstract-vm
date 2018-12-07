#ifndef VALUEHANDLER_HPP
#define VALUEHANDLER_HPP


#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

namespace parser {

class ValueHandler : public Handler {
 private:
  using LexerToken = lexer::Token::Type;
  static const pattern::Pattern s_pattern;

 public:
  void check(Handler::iterator i, Handler::iterator end) override;
};

}  // namespace parser

#endif // VALUEHANDLER_HPP
