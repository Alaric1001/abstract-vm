#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "vm/OperandFactory.hpp"


#include "utils/arithmetic_operations.hpp"
#include "utils/to_numeric.hpp"

#include <cstdint>
#include <functional>
#include <sstream>

namespace exec {

namespace {

template <typename T>
class Operand : public IOperand {
 private:
  static OperandType s_type;
  T m_val;
  const std::string m_string_val;

  Ptr op(const IOperand &rhs, std::function<T(T, T)> f_t, std::function<double(double, double)> f_d) const {
    if (get_precision() > rhs.get_precision()) {
      T v = utils::to_numeric<T>(rhs.to_string());
      try {
      v = f_t(m_val, v);
      } catch (utils::RuntimeError&) {throw;}
      std::string result = std::string(std::to_string(v));
      return OperandFactory::instance().create_operand(get_type(), result);
    }
    double a = utils::to_numeric<double>(rhs.to_string());
    double b = static_cast<double>(m_val);
    double res;
      try {
       res = f_d(a, b);
      } catch (utils::RuntimeError&) {throw;}
      std::string result = std::string(std::to_string(res));
      return OperandFactory::instance().create_operand(rhs.get_type(), result);

    return nullptr;
  }

 public:
  Operand() = delete;
  Operand(T val) : m_val(val), m_string_val(std::to_string(val)) {}

  int get_precision() const override { return static_cast<int>(s_type); }
  OperandType get_type() const override { return s_type; }

  IOperand::Ptr operator+(const IOperand &rhs) const override {
    try {
      return op(rhs, utils::add<T>, utils::add<double>);
    } catch (utils::RuntimeError &) {
      throw;
    }
  }

  IOperand::Ptr operator-(const IOperand &rhs) const override {
    try {
      return op(rhs, utils::sub<T>, utils::sub<double>);
    } catch (utils::RuntimeError &) {
      throw;
    }
  }

  IOperand::Ptr operator*(const IOperand &rhs) const override {
    try {
      return op(rhs, utils::mul<T>, utils::mul<double>);
    } catch (utils::RuntimeError &) {
      throw;
    }
  }

  IOperand::Ptr operator/(const IOperand &rhs) const override {
    try {
      return op(rhs, utils::div<T>, utils::div<double>);
    } catch (utils::RuntimeError &) {
      throw;
    }
  }

  IOperand::Ptr operator%(const IOperand &rhs) const override {
    try {
      return op(rhs, utils::mod<T>, utils::mod<double>);
    } catch (utils::RuntimeError &) {
      throw;
    }
  }

  bool operator==(const IOperand &rhs) const override {
    return s_type == rhs.get_type() and m_string_val == rhs.to_string();
  }

  bool operator!=(const IOperand &rhs) const override {
    return not operator==(rhs);
  }

  Ptr clone() const override { return std::make_unique<Operand<T>>(m_val); }

  T value() const { return m_val; }

  const std::string &to_string() const override { return m_string_val; }
};
template <typename T>
IOperand::OperandType Operand<T>::s_type = IOperand::OperandType::Double;
}  // namespace exec

#endif  // OPERAND_HPP
