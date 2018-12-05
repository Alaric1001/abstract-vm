#ifndef PUNCTUATION_HPP
#define PUNCTUATION_HPP

#include <array>

namespace lexer {
    enum class PunctuationType {OpeningBrace, ClosingBrace, Dot, Plus, Minus, None};
    PunctuationType get_punctuation_type(char);
    const char *get_punctuation_symbols();
} // namespace lexer
#endif // PUNCTUATION_HPP
