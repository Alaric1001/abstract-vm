#include "vm/OperandFactory.hpp"

namespace exec {
const OperandFactory OperandFactory::s_instance = OperandFactory();
const OperandFactory& OperandFactory::instance() { return s_instance; }

IOperand::Ptr OperandFactory::create_operand(IOperand::OperandType type,
                                                   const std::string& v) const {
  static const std::function<IOperand::Ptr(const OperandFactory&, double)> arr[5] = {
    &OperandFactory::create_operand<int8_t>,
    &OperandFactory::create_operand<int32_t>,
    &OperandFactory::create_operand<int64_t>,
    &OperandFactory::create_operand<float>,
    &OperandFactory::create_operand<double>
  };
  double val = std::stod(v);
  return arr[static_cast<int>(type)](*this, val);
}

}  // namespace exec
