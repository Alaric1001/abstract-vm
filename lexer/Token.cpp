#include "lexer/Token.hpp"

namespace lexer {
Token::Token(Type type, const std::string &val) : m_type(type), m_value(val) {}
Token::Token(Type type) : m_type(type) {}
Token::Token(Type type, std::string &&val) : m_type(type), m_value(std::move(val)) {}

void Token::dump(std::ostream &out, bool verbose) const {
  out << "[";
  if (verbose) {
    switch (m_type) {
      case Type::Unknown: out << "?"; break;
      case Type::Blank: out << "BLANK"; break;
      case Type::Instruction: out << "INSTRUCTION"; break;
      case Type::Value: out << "VALUE"; break;
      case Type::Newline: out << "NEWLINE"; break;
      case Type::Numeric: out << "NUM"; break;
      case Type::OpeningBrace: out << "OBRACE"; break;
      case Type::ClosingBrace: out << "CBRACE"; break;
      case Type::Dot: out << "DOT"; break;
      case Type::Sign: out << "SIGN"; break;
      default: out << "?"; break;
    }
    out << ", ";
  }
  out << '"' << m_value << "\"]";
}

Token::Type Token::type() const { return m_type; }
const std::string &Token::value() const { return m_value; }
bool Token::operator==(const Token &rhs) const {
  return rhs.type() == m_type && rhs.value() == m_value;
}

} // namespace lexer
