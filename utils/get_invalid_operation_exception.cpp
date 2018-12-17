#include "utils/get_invalid_operation_exception.hpp"

#include <cassert>

namespace utils {

RuntimeError get_invalid_operation_exception(OperationState state) {
  switch(state) {
    case OperationState::Overflow:
      return RuntimeError("Operation overflow");
    case OperationState::Underflow:
      return RuntimeError("Operation underflow");
    case OperationState::Invalid:
      return RuntimeError("Invalid operation result");
    default:
        assert(false);
  }
}

} // namespace utils
