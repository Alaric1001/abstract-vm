#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

namespace utils {
class Logger {
 private:
  std::ostream& m_stream = std::cout;
  bool m_enabled = false;

  static Logger s_instance;

  Logger() = default;
  Logger(const Logger&) = default;
  Logger& operator=(const Logger&) = default;
 public:

  void enable(bool = true);

  template <typename T>
  Logger& operator<<(const T& t) {
    if (m_enabled)
      m_stream << t;
    return *this;
  }

  static Logger& instance();
};
}  // namespace utils

#endif  // LOGGER_HPP
