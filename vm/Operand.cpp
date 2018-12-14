#include "vm/Operand.hpp"

namespace exec {

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

} // namespace exec
