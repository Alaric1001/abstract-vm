#include "vm/OptParser.hpp"

extern "C" {
#include "getopt.h"
}

namespace exec {

bool OptParser::has_opt(Opt o) const { return m_opt & o; }
const std::string& OptParser::filename() const { return m_filename; }

void OptParser::parse(int ac, char* const av[]) {
  int opt;
  while ((opt = getopt(ac, av, "iv")) != -1) {
    switch (opt) {
      case 'i':
        m_opt |= Interactive;
        break;
      case 'v':
        m_opt |= Verbose;
        break;
      default:
        throw UnknownOpt();
    }
  }
  if (ac > 1 and av[ac - 1][0] != '-') m_filename = av[ac - 1];
}

const char* OptParser::UnknownOpt::what() const noexcept {
  return "Options available: \n\t-i intercative mode\n\t-v verbose mode";
}
}  // namespace exec
