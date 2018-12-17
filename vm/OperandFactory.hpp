#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "vm/IOperand.hpp"

namespace exec {
class OperandFactory {
 private:
  static const OperandFactory s_instance;

  OperandFactory() = default;
  OperandFactory(const OperandFactory&) = default;
  OperandFactory& operator=(const OperandFactory&) = default;
 public:

  IOperand::Ptr create_operand(IOperand::OperandType, const std::string&) const;

  static const OperandFactory& instance();
};
}  // namespace exec

#endif  // OPERANDFACTORY_HPP
