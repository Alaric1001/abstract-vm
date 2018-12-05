#include "lexer/punctuation.hpp"

namespace lexer {

const char *get_punctuation_symbols() {
  static const char symbols[] = "().+-";
  return symbols;
}

PunctuationType get_punctuation_type(char c) {
  int i = 0;
  const char *symbols = get_punctuation_symbols();
  for (; symbols[i]; ++i)
    if (symbols[i] == c) break;
  return static_cast<PunctuationType>(i);
}

}  // namespace lexer

