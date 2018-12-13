#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

#include "utils/RuntimeError.hpp"

namespace utils {

template <typename T>
class Stack {
 public:
  using Container = std::vector<T>;
  using const_iterator = typename Container::const_iterator;

 private:
  static constexpr size_t size = 4096 / sizeof(T);
  Container m_container;

 public:
  explicit Stack() { m_container.reserve(size); }
  Stack(const Stack&) = delete;

  T& top() { return m_container.back(); }
  const T& top() const { return m_container.back(); }

  bool empty() const { return m_container.empty(); }

  void push(T&& value) {
    if (m_container.size() == size - 1) throw RuntimeError("Stack overflow");
    m_container.push_back(std::move(value));
  }

  void pop() {
    m_container.pop_back();
  }

  void iterate(std::function<void(const T&)> f) const {
    for (const auto& e : m_container)
      f(e);
  }
};
}  // namespace utils

#endif  // STACK_HPP
