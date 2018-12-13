#ifndef IEXECELEMS_HPP
#define IEXECELEMS_HPP

#include <string>

#include "vm/IOperand.hpp"

namespace exec {
class IExecElem {
 public:
  virtual ~IExecElem() = default;
};

class ExecOperand : public IExecElem {
 private:
  std::string m_value;
  IOperand::OperandType m_type;

 public:
  ExecOperand() = delete;
  ExecOperand(std::string &&val, IOperand::OperandType type)
      : m_value(std::move(val)), m_type(type) {}
  ExecOperand(const std::string &val, IOperand::OperandType type)
      : m_value(val), m_type(type) {}

  const auto &value() const { return m_value; }
  auto type() const { return m_type; }
};

}  // namespace exec

#endif  // IEXECELEMS_HPP
