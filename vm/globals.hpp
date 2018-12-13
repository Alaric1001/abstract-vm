#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <cstdint>

namespace globals {
class LineCounter {
  private:
    static uint32_t s_count;

  public:
    static void reset();
    static uint32_t count();
    static void increment();
};
static constexpr int operand_count = 5;
extern const char *operand_names[operand_count];
} // namespace globals

#endif // GLOBALS_HPP
