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
  ExecOperand(const ExecOperand&) = delete;
  ExecOperand &operator=(const ExecOperand&) = delete;

  ExecOperand(std::string &&val, IOperand::OperandType type);
  ExecOperand(const std::string &val, IOperand::OperandType type);

  const std::string &value() const;
  decltype(m_type) type() const;
};

}  // namespace exec

#endif  // IEXECELEMS_HPP
