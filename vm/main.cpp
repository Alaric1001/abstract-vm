#include "lexer/lexer.hpp"
#include "utils/Dump.hpp"

#include <sstream>
#include <iostream>

int main() {
  std::stringstream input("  aa  a  aaa ");
  auto container = lexer::lexe(input);
  std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  utils::dump_objects(std::cout, container);
  std::cout << std::endl;
}
