#ifndef OPTPARSER_HPP
#define OPTPARSER_HPP

#include <exception>
#include <string>

namespace exec {
class OptParser {
 private:
  int m_opt = 0;
  std::string m_filename;

 public:
  enum Opt { Interactive = 1, Verbose = 2 };

  class UnknownOpt : std::exception {
   public:
    UnknownOpt() = default;
    UnknownOpt(const UnknownOpt &) = default;
    UnknownOpt &operator=(const UnknownOpt &) = delete;
    const char *what() const noexcept override;
  };

  OptParser() = default;
  OptParser(const OptParser &) = delete;
  OptParser &operator=(const OptParser &) = delete;

  bool has_opt(Opt) const;
  const std::string &filename() const;
  void parse(int ac, char *const av[]);
};
}  // namespace exec

#endif  // OPTPARSER_HPP
