#include "utils/Logger.hpp"

namespace utils {

Logger Logger::s_instance = Logger();

void Logger::enable(bool b) { m_enabled = b; }

Logger & Logger::instance() { return s_instance; }
}  // namespace utils
