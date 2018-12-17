#ifndef VALUEHANDLER_HPP
#define VALUEHANDLER_HPP

#include "parser/Handler.hpp"
#include "parser/Pattern.hpp"

#include "vm/ExecActions.hpp"

namespace parser {

class ValueHandler : public Handler {
 private:
  using LexerToken = lexer::Token::Type;
  static const pattern::Pattern s_pattern;
  static ValueHandler s_instance;

  const pattern::Pattern& get_pattern(const lexer::Token&) const override;
  void do_check(iterator, iterator) override;

 public:
  std::unique_ptr<const exec::IExecElem> parse(iterator,
                                               iterator) const override;
  static ValueHandler& instance();
};

}  // namespace parser

#endif  // VALUEHANDLER_HPP
