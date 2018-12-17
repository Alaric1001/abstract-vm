#ifndef ARITHMETIC_OPERATIONS_HPP
#define ARITHMETIC_OPERATIONS_HPP

#include "utils/RuntimeError.hpp"
#include "utils/get_invalid_operation_exception.hpp"
#include "utils/operation_state.hpp"

#include <cmath>

namespace utils {
template <typename T>
T add(T lhs, T rhs) {
  auto state = operation_state<T>(OperationType::Add, lhs, rhs);
  if (state != OperationState::Ok) throw get_invalid_operation_exception(state);
  return lhs + rhs;
}

template <typename T>
T sub(T lhs, T rhs) {
  auto state = operation_state<T>(OperationType::Sub, lhs, rhs);
  if (state != OperationState::Ok) throw get_invalid_operation_exception(state);
  return lhs - rhs;
}

template <typename T>
T mul(T lhs, T rhs) {
  auto state = operation_state<T>(OperationType::Mul, lhs, rhs);
  if (state != OperationState::Ok) throw get_invalid_operation_exception(state);
  return lhs * rhs;
}

template <typename T>
T div(T lhs, T rhs) {
  if (rhs == 0) throw DivisionByZero(DivisionByZero::Type::Div);
  auto state = operation_state<T>(OperationType::Div, lhs, rhs);
  if (state != OperationState::Ok) throw get_invalid_operation_exception(state);
  return lhs / rhs;
}

template <typename T>
T mod(T lhs, T rhs) {
  if (rhs == 0) throw DivisionByZero(DivisionByZero::Type::Mod);
  auto state = operation_state<T>(OperationType::Div, lhs, rhs);
  if (state != OperationState::Ok) throw get_invalid_operation_exception(state);
  return std::fmod(lhs, rhs);
}

}  // namespace utils

#endif  // ARITHMETIC_OPERATIONS_HPP
