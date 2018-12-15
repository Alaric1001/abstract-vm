#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "parser/Errors.hpp"
#include "utils/Dump.hpp"
#include "utils/Stack.hpp"
#include "vm/IOperand.hpp"
#include "vm/OptParser.hpp"
#include "vm/globals.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace exec {

int exec_stream(std::istream& stream,
                utils::Stack<std::unique_ptr<const IOperand>>& stack) {
  auto container = lexer::lexe(stream);
  if (not parser::syntax_checks(container)) return (1);
  globals::LineCounter::reset();
  while (not container.empty()) {
    try {
      parser::parse_and_exec_line(container, stack);
    } catch (utils::RuntimeError& e) {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  return 0;
}

int exec_stdin(utils::Stack<std::unique_ptr<const IOperand>>& stack) {
  std::stringstream stream;
  std::string line;
  std::cout << "> ";
  while (std::cin.good() && std::getline(std::cin, line)) {
    if (line == ";;") break;
    stream << line << "\n";
    std::cout << "> ";
  }
  return exec_stream(stream, stack);
}

int exec_interactive(utils::Stack<std::unique_ptr<const IOperand>>& stack) {
  std::string line;
  std::deque<lexer::Token> container;
  std::cout << "Welcome in abstractVM interactive mode!\n> ";
  globals::LineCounter::reset();
  while (std::cin.good() && std::getline(std::cin, line)) {
    lexer::lexe_line(line, container);
    try {
      parser::check_line(container.cbegin(), container.cend());
      parser::parse_and_exec_line(container, stack);
    } catch (utils::RuntimeError& e) {
      std::cerr << e.what() << "\n";
    }
    catch (parser::ParseError &e) {
      std::cerr << "Syntax error: ";
      e.display_err(std::cerr);
    }
    container.clear();
    std::cout << "> ";
  globals::LineCounter::increment();
  }
  return 1;
}

int main(int ac, char* const av[]) {
  utils::Stack<std::unique_ptr<const IOperand>> stack;
  OptParser opts;

  try {
    opts.parse(ac, av);
  } catch (OptParser::UnknownOpt& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (not opts.filename().empty()) {
    std::ifstream stream(opts.filename());
    return exec_stream(stream, stack);
  }
  if (opts.has_opt(OptParser::Interactive)) return exec_interactive(stack);
  return exec_stdin(stack);
  // std::stringstream input(
  //     "\n\n \npush int8(126)  \n\n\npush int32(1)\n mod\ndump\n exit a\n
  //     dump");
  // auto container = lexer::lexe(input);
  // std::cout << "Lexed tokens (s=" << container.size() << ") = ";
  // utils::dump_objects(std::cout, container);
  // if (not parser::syntax_checks(container)) return (1);
  // globals::LineCounter::reset();
  // while (not container.empty()) {
  //   try {
  //     parser::parse_and_exec_line(container, stack);
  //   } catch (utils::RuntimeError &e) {
  //     std::cerr << e.what() << "\n";
  //     return 1;
  //   }
  // }
  // return 0;
}

}  // namespace exec

int main(int ac, char* const av[]) { return exec::main(ac, av); }
