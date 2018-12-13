#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <string>

namespace exec {

class IOperand {
 public:
   using Ptr = std::unique_ptr<const IOperand>;
  enum class OperandType { Int8, Int16, Int32, Float, Double };

  virtual int get_precision() const = 0;
  virtual OperandType get_type() const = 0;

  virtual Ptr operator+(const IOperand &rhs) const = 0;
  virtual Ptr operator-(const IOperand &rhs) const = 0;
  virtual Ptr operator*(const IOperand &rhs) const = 0;
  virtual Ptr operator/(const IOperand &rhs) const = 0;
  virtual Ptr operator%(const IOperand &rhs) const = 0;

  virtual bool operator==(const IOperand &rhs) const = 0;
  virtual bool operator!=(const IOperand &rhs) const = 0;

  virtual const std::string &to_string() const = 0;

  virtual ~IOperand() = default;
};
}  // namespace exec

#endif  // IOPERAND_HPP
