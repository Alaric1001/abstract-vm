#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "vm/IOperand.hpp"

#include "utils/RuntimeError.hpp"
#include "utils/to_numeric.hpp"
#include "vm/OperandFactory.hpp"

#include <cstdint>
#include <sstream>

namespace exec {

template <typename T>
class Operand : public IOperand {
 private:
  static OperandType s_type;
  T m_val;
  const std::string m_string_val;

  Ptr op(const IOperand &rhs, std::function<T(T lhs, T rhs)> f) const {
    T v = utils::to_numeric<T>(rhs.to_string());
    if (get_precision() < rhs.get_precision())
      return std::make_unique<Operand<T>>(f(m_val, v));
    std::string s_v = std::to_string(f(m_val, v));
    return OperandFactory::instance().create_operand(rhs.get_type(), s_v);
  }

 public:
  Operand() = delete;
  Operand(T val) : m_val(val), m_string_val(std::to_string(val)) {}

  int get_precision() const override { return static_cast<int>(s_type); }
  OperandType get_type() const override { return s_type; }

  IOperand::Ptr operator+(const IOperand &rhs) const override {
    return op(rhs, [](T lhs, T rhs) -> T { return lhs + rhs; });
  }

  IOperand::Ptr operator-(const IOperand &rhs) const override {
    return op(rhs, [](T lhs, T rhs) -> T { return lhs - rhs; });
  }

  IOperand::Ptr operator*(const IOperand &rhs) const override {
    return op(rhs, [](T lhs, T rhs) -> T { return lhs * rhs; });
  }

  IOperand::Ptr operator/(const IOperand &rhs) const override {
    if (rhs.to_string() == "0")
      throw utils::DivisionByZero(utils::DivisionByZero::Type::Div);
    return op(rhs, [](T lhs, T rhs) -> T { return lhs / rhs; });
  }

  IOperand::Ptr operator%(const IOperand &rhs) const override {
    if (rhs.to_string() == "0")
      throw utils::DivisionByZero(utils::DivisionByZero::Type::Mod);
    return op(rhs, [](T lhs, T rhs) -> T {
      return static_cast<intmax_t>(lhs) % static_cast<intmax_t>(rhs);
    });
  }

  bool operator==(const IOperand &rhs) const override {
    return s_type == rhs.get_type() and m_string_val == rhs.to_string();
  }

  bool operator!=(const IOperand &rhs) const override {
    return not operator==(rhs);
  }

  const std::string &to_string() const override { return m_string_val; }
};

template <>
IOperand::OperandType Operand<int8_t>::s_type = IOperand::OperandType::Int8;
template <>
IOperand::OperandType Operand<int32_t>::s_type = IOperand::OperandType::Int16;
template <>
IOperand::OperandType Operand<int64_t>::s_type = IOperand::OperandType::Int32;
template <>
IOperand::OperandType Operand<float>::s_type = IOperand::OperandType::Float;
template <>
IOperand::OperandType Operand<double>::s_type = IOperand::OperandType::Double;

}  // namespace exec

#endif  // OPERAND_HPP
