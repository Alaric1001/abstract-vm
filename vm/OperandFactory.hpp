#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "vm/Operand.hpp"

namespace exec {
class OperandFactory {
 private:
  static const OperandFactory s_instance;
  template <typename T>
  IOperand::Ptr create_operand(double val) const {
    return std::make_unique<Operand<T>>(static_cast<T>(val));
  }

 public:
  OperandFactory() = default;

  IOperand::Ptr create_operand(IOperand::OperandType, const std::string&) const;

  static const OperandFactory& instance();
};
}  // namespace exec

#endif  // OPERANDFACTORY_HPP
