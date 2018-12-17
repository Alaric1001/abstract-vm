#ifndef OPERATION_STATE_HPP
#define OPERATION_STATE_HPP

#include <cfenv>
#include <cmath>
#include <functional>
#include <limits>

#include <iostream>

namespace utils {

enum class OperationState { Ok, Overflow, Underflow, Invalid };
enum class OperationType { Add, Sub, Mul, Div };

namespace {
template <typename T, bool = std::is_floating_point<T>::value>
struct wrapper {
  static OperationState add(T, T);
  static OperationState sub(T, T);
  static OperationState div(T, T);
  static OperationState mul(T, T);
};

template <typename T>
OperationState generic_floating_point_check(std::function<T(void)> f) {
  std::feclearexcept(FE_ALL_EXCEPT);
  T tmp = f();
  int except = std::fetestexcept(FE_UNDERFLOW | FE_OVERFLOW);
  if (except & FE_UNDERFLOW) return OperationState::Underflow;
  if (except & FE_OVERFLOW) return OperationState::Overflow;
  if (std::isfinite(tmp)) return OperationState::Ok;
  return OperationState::Invalid;
}

template <typename T>
struct wrapper<T, true> {
  static OperationState add(T a, T b) {
    return generic_floating_point_check<T>([a, b]() -> T { return a + b; });
  }
  static OperationState sub(T a, T b) {
    return generic_floating_point_check<T>([a, b]() -> T { return a - b; });
  }
  static OperationState div(T a, T b) {
    return generic_floating_point_check<T>([a, b]() -> T { return a / b; });
  }
  static OperationState mul(T a, T b) {
    return generic_floating_point_check<T>([a, b]() -> T { return a * b; });
  }
};

template <typename T>
struct wrapper<T, false> {
  static OperationState add(T a, T b) {
    double r = static_cast<double>(a) + static_cast<double>(b);
    if (r > std::numeric_limits<T>::max()) return OperationState::Overflow;
    if (r < std::numeric_limits<T>::min()) return OperationState::Underflow;
    return OperationState::Ok;
  }

  static OperationState sub(T a, T b) {
    double r = static_cast<double>(a) - static_cast<double>(b);
    if (r > std::numeric_limits<T>::max()) return OperationState::Overflow;
    if (r < std::numeric_limits<T>::min()) return OperationState::Underflow;
    return OperationState::Ok;
  }

  static OperationState mul(T a, T b) {
    double r = static_cast<double>(a) * static_cast<double>(b);
    if (r > std::numeric_limits<T>::max()) return OperationState::Overflow;
    if (r < std::numeric_limits<T>::min()) return OperationState::Underflow;
    return OperationState::Ok;
  }

  static OperationState div(T a, T b) {
    if ((a == -1 && b == std::numeric_limits<T>::min()) or
        (b == -1 && a == std::numeric_limits<T>::min()))
      return OperationState::Overflow;
    return OperationState::Ok;
  }
};
}  // namespace

template <typename T>
OperationState operation_state(OperationType type, T a, T b) {
  switch (type) {
    case OperationType::Add:
      return wrapper<T>::add(a, b);
    case OperationType::Sub:
      return wrapper<T>::sub(a, b);
    case OperationType::Mul:
      return wrapper<T>::mul(a, b);
    case OperationType::Div:
      return wrapper<T>::div(a, b);
  }
}

}  // namespace utils

#endif  // OPERATION_STATE_HPP
