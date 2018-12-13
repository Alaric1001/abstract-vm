#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils/Dump.hpp"
#include "utils/Stack.hpp"
#include "vm/IOperand.hpp"

#include <sstream>
#include <iostream>

int main() {
  utils::Stack<std::unique_ptr<const exec::IOperand>> stack;
  std::stringstream input("  push double(+.6)\n assert double(0.6)\npush int8(-3)\ndump");
  auto container = lexer::lexe(input);
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
  parser::syntax_checks(container);
  while (not container.empty())
    parser::parse_line(container)->execute(stack);
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
}
