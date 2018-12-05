#include "lexer/Token.hpp"

namespace lexer {
  Token::Token(Type type, const std::string &val) : m_type(type), m_value(val) {}
  
  void Token::dump(std::ostream &out) const {
    out << "{Token ";
    switch (m_type) {
      case Type::Blank: out << "BLANK"; break;
      case Type::Instruction: out << "INSTRUCTION"; break;
      case Type::Value: out << "VALUE"; break;
      case Type::Separator: out << "SEP"; break;
      case Type::Numeric: out << "NUM"; break;
      case Type::Brace: out << "BRACE"; break;
      default: out << "?"; break;
    }
    out << ", value=\"" << m_value << "\"}";
  }
} // namespace lexer
