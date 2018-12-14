#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils/Dump.hpp"
#include "utils/Stack.hpp"
#include "vm/IOperand.hpp"

#include <sstream>
#include <iostream>

int main() {
  utils::Stack<std::unique_ptr<const exec::IOperand>> stack;
  std::stringstream input("push int8(126)\npush int32(2)\n add\ndump\n exit");
  auto container = lexer::lexe(input);
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
  parser::syntax_checks(container);
  while (not container.empty()) {
    try {
    parser::parse_line(container)->execute(stack);
    } catch (utils::RuntimeError &e) {
      std::cerr<< e.what()<<"\n";
      return (1);
    }
  }
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
}
