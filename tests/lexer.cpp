#include "lexer/lexer.hpp"

#include <criterion/criterion.h>

#include <array>
#include <iostream>
#include <sstream>

using Token = lexer::Token;

Test(lexer, unknown) {
  {
    std::stringstream input("a");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Unknown, "a"));
  }
  {
    std::stringstream input("bsaaa");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Unknown, "bsaaa"));
  }
  {
    std::stringstream input("b aaa");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Unknown, "b"));
    cr_assert(res[1] == Token(Token::Type::Blank, " "));
    cr_assert(res[2] == Token(Token::Type::Unknown, "aaa"));
  }
}

Test(lexer, blanks) {
  {
    std::stringstream input(" ");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Blank, " "));
  }
  {
    std::stringstream input(" \t ");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Blank, " \t "));
  }
  {
    std::stringstream input("");
    auto res = lexer::lexe(input);
    if (not res.empty())
      cr_assert(!(res[0] == Token(Token::Type::Blank, " \t ")));
  }
}

Test(lexer, keywords) {
  static const std::array<lexer::Token, 16> tokens{{
      {Token::Type::Instruction, "push"},
      {Token::Type::Instruction, "pop"},
      {Token::Type::Instruction, "dump"},
      {Token::Type::Instruction, "assert"},
      {Token::Type::Instruction, "add"},
      {Token::Type::Instruction, "sub"},
      {Token::Type::Instruction, "mul"},
      {Token::Type::Instruction, "div"},
      {Token::Type::Instruction, "mod"},
      {Token::Type::Instruction, "print"},
      {Token::Type::Instruction, "exit"},
      {Token::Type::Value, "int8"},
      {Token::Type::Value, "int16"},
      {Token::Type::Value, "int32"},
      {Token::Type::Value, "float"},
      {Token::Type::Value, "double"},
  }};

  {
    std::stringstream input;
    for (const auto& tok : tokens) {
      input << tok.value();
      auto res = lexer::lexe(input);
      cr_assert(res[0] == tok);
      input.str("");
      input.clear();
    }
  }
  {
    std::stringstream input("pus");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Unknown, "pus"));
  }
}

Test(lexer, newlines) {
  {
    std::stringstream input("\n");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Newline, "\\n"));
  }
  {
    std::stringstream input("\n\n\n\n");
    auto res = lexer::lexe(input);
    for (int i = 0; i < 4; ++i)
      cr_assert(res[i] == Token(Token::Type::Newline, "\\n"));
  }
}

Test(lexer, comments) {
  {
    std::stringstream input(";   ");
    auto res = lexer::lexe(input);
    if (not res.empty())
      cr_assert(!(res[0] == Token(Token::Type::Blank, " \t ")));
  }
  {
    std::stringstream input(" ;   ");
    auto res = lexer::lexe(input);
    cr_assert(res[0] == Token(Token::Type::Blank, " "));
    cr_assert(!(res[1] == Token(Token::Type::Blank, " ")));
  }
}

Test(lexer, punctuation) {
  const char symbols[] = "().+-";
  std::stringstream input(symbols);
  auto res = lexer::lexe(input);
  for (int i = 0; symbols[i]; ++i)
    cr_assert(res[i] ==
              Token(Token::Type::Punctuation, std::string(1, symbols[i])));
}
