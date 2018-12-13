#include "vm/ExecActions.hpp"

#include "vm/OperandFactory.hpp"

#include <map>

#include <iostream>
namespace exec {

ExecSimpleAction::ExecSimpleAction(const _private_key&, const Action& action)
    : m_action(action) {}

void ExecSimpleAction::execute(Stack& s) const { m_action(s); }

void exit(Stack&) {
  std::cout << "exit...\n";
  std::exit(0);
}

void dump(Stack& s) {
  s.iterate([](const std::unique_ptr<const IOperand>& e) {
    std::cout << e->to_string() << "\n";
  });
}

void pop(Stack& s) {
  if (s.empty())
    throw utils::RuntimeError("Attempt to pop on an empty stack");
  s.pop();
}

std::unique_ptr<IExecElem> ExecSimpleAction::create(
    const std::string& action_name) {
  static const std::map<std::string, Action> actions{{"exit", exit},
                                                     {"dump", dump},
                                                     {"pop", pop}};
  try {
    return std::make_unique<ExecSimpleAction>(_private_key(),
                                              actions.at(action_name));
  } catch (std::out_of_range&) {
    return nullptr;
  }
}

ExecValueAction::ExecValueAction(const _private_key&, const Action& action,
                                 std::unique_ptr<const ExecOperand>&& op)
    : m_action(action), m_value(std::move(op)) {}

void ExecValueAction::execute(Stack& s) const { m_action(s, m_value.get()); }

void push(Stack& s, const ExecOperand* op) {
  try {
    s.push(OperandFactory::instance().create_operand(op->type(), op->value()));
  } catch (const utils::RuntimeError& e) {
    throw e;
  }
}

void assert_value(Stack& e, const ExecOperand* op) {
  const auto& top = e.top();
  const auto maked_op =
      OperandFactory::instance().create_operand(op->type(), op->value());
  if (*top != *maked_op) throw utils::RuntimeError("Assertion failed");
}

std::unique_ptr<IExecElem> ExecValueAction::create(
    const std::string& action_name, Value&& value) {
  static const std::map<std::string, Action> actions{{"push", push},
                                                     {"assert", assert_value}};
  try {
    return std::make_unique<ExecValueAction>(
        _private_key(), actions.at(action_name), std::move(value));
  } catch (std::out_of_range&) {
    return nullptr;
  }
}

}  // namespace exec
