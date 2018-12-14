#include "vm/globals.hpp"
namespace globals {
uint32_t LineCounter::s_count = 1;

void LineCounter::reset() { s_count = 1;}
void LineCounter::increment() { ++s_count;}
uint32_t LineCounter::count() { return s_count;}

const char *operand_names[operand_count] = { "int8", "int16", "int32", "float", "double" };
} // namespace globals
