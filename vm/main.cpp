#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "utils/Dump.hpp"

#include <sstream>
#include <iostream>

int main() {
  //std::stringstream input(" int32(543.3). push;   a\n;\n\nexit");
  std::stringstream input("; -------------\n; exemple.avm -\n; -------------\n\npush int32(42)\npush int32(33)\n\nadd\n\npush float(44.55)\n\nmul\n   \n push double(42.42) \npush int32(42)\n\ndump\n\npop\n\nassert double(42.42)\n\nexit");
  auto container = lexer::lexe(input);
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
  std::cout << std::endl;
  parser::parse(container);
}
