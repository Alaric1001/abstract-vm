#ifndef EXECACTIONS_HPP
#define EXECACTIONS_HPP

#include "utils/Stack.hpp"
#include "vm/IExecElems.hpp"
#include "vm/IOperand.hpp"

namespace exec {

using Stack = utils::Stack<std::unique_ptr<const IOperand>>;

class IExecAction : public IExecElem {
 protected:
  struct _private_key {
    explicit _private_key() = default;
  };

 public:
  virtual ~IExecAction() = default;
  virtual void execute(Stack &) const = 0;
};

class ExecSimpleAction : public IExecAction {
 private:
  using Action = std::function<void(Stack &)>;
  const Action m_action;

 public:
  ExecSimpleAction() = delete;
  ExecSimpleAction(const ExecSimpleAction &) = delete;
  explicit ExecSimpleAction(const _private_key &, const Action &action);

  void execute(Stack &) const override;
  static std::unique_ptr<IExecElem> create(const std::string &action_name);
};

class ExecValueAction : public IExecAction {
 private:
  using Action = std::function<void(Stack &, const ExecOperand *)>;
  using Value = std::unique_ptr<const ExecOperand>;
  const Action m_action;
  Value m_value;

 public:
  ExecValueAction() = delete;
  ExecValueAction(const ExecValueAction &) = delete;
  explicit ExecValueAction(const _private_key &, const Action &,
                           std::unique_ptr<const ExecOperand> &&);

  void execute(Stack &) const override;
  static std::unique_ptr<IExecElem> create(const std::string &action_name,
                                           Value &&value);
};

}  // namespace exec

#endif  // EXECACTIONS_HPP
