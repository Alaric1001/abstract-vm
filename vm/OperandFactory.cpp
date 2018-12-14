#include "vm/OperandFactory.hpp"

#include "utils/RuntimeError.hpp"
#include "vm/Operand.hpp"

#include <functional>
#include <limits>

template <typename T>
exec::IOperand::Ptr create_operand(double val) {
  if (val > std::numeric_limits<T>::max())
    throw utils::RuntimeError("Numeric overflow");
  if (val < std::numeric_limits<T>::min())
    throw utils::RuntimeError("Numeric underflow");
  return std::make_unique<exec::Operand<T>>(static_cast<T>(val));
}

namespace exec {

const OperandFactory OperandFactory::s_instance = OperandFactory();
const OperandFactory& OperandFactory::instance() { return s_instance; }

IOperand::Ptr OperandFactory::create_operand(IOperand::OperandType type,
                                             const std::string& v) const {
  static const std::function<IOperand::Ptr(double)> arr[5] = {
      ::create_operand<int8_t>, ::create_operand<int32_t>,
      ::create_operand<int64_t>, ::create_operand<float>,
      ::create_operand<double>};
  IOperand::Ptr ret;
  try {
    ret = arr[static_cast<int>(type)](std::stod(v));
  } catch (utils::RuntimeError& e) {
    throw e;
  }
  catch (std::out_of_range& e) {
    throw utils::RuntimeError(e.what());
  }
  return ret;
}
}  // namespace exec
