#include "vm/IExecElems.hpp"

namespace exec {

ExecOperand::ExecOperand(std::string &&val, IOperand::OperandType type)
    : m_value(std::move(val)), m_type(type) {}
ExecOperand::ExecOperand(const std::string &val, IOperand::OperandType type)
    : m_value(val), m_type(type) {}

const std::string &ExecOperand::value() const { return m_value; }
IOperand::OperandType ExecOperand::type() const { return m_type; }
}  // namespace exec
