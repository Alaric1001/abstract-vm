#ifndef GET_INVALID_VALUE_EXCEPTION_HPP
#define GET_INVALID_VALUE_EXCEPTION_HPP

#include "utils/RuntimeError.hpp"
#include "utils/operation_state.hpp"

namespace utils {

RuntimeError get_invalid_operation_exception(OperationState state);

} // namespace utils

#endif // GET_INVALID_VALUE_EXCEPTION_HPP
