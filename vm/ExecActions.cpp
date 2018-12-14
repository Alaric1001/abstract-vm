#include "vm/ExecActions.hpp"

#include "vm/Operand.hpp"
#include "vm/globals.hpp"

#include <cassert>
#include <iostream>
#include <map>

namespace exec {

ExecSimpleAction::ExecSimpleAction(const _private_key&, const Action& action)
    : m_action(action) {}

void ExecSimpleAction::execute(Stack& s) const { m_action(s); }

void exit(Stack&) {
  std::cout << "exit...\n";
  std::exit(0);
}

void dump(Stack& s) {
  if (s.empty()) {
    std::cout << "- Stack is empty -\n";
    return;
  }
  std::cout << "- Stack of size " << s.size() << " -\n";
  s.iterate([](const std::unique_ptr<const IOperand>& e) {
    int i = static_cast<int>(e->get_type());
    assert(i < globals::operand_count);
    std::cout << "- " << globals::operand_names[i] << '(' << e->to_string()
              << ')' << "\n";
  });
}

void pop(Stack& s) {
  if (s.empty()) throw utils::RuntimeError("Attempt to pop on an empty stack");
  s.pop();
}

void print(Stack& s) {
  if (s.empty()) throw utils::RuntimeError("Stack is empty");
  const auto& top = s.top();
  if (top->get_type() != IOperand::OperandType::Int8)
    throw utils::RuntimeError("Top stack operand isn't a int8");
  const auto* ptr = top.get();
  char c = static_cast<const Operand<int8_t>*>(ptr)->value();
  std::cout << c;
}

void operation(
    Stack& s,
    std::function<IOperand::Ptr(const IOperand&, const IOperand&)> op) {
  if (s.size() < 2) throw utils::RuntimeError("Stack has less than 2 values");
  auto top = s.top()->clone();
  s.pop();
  try {
    auto new_elem = op(*s.top(), *top);
    s.pop();
    s.push(std::move(new_elem));
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

void add(Stack& s) {
  try {
    operation(s, [](const IOperand& a, const IOperand& b) -> IOperand::Ptr {
      return a + b;
    });
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

void sub(Stack& s) {
  try {
    operation(s, [](const IOperand& a, const IOperand& b) -> IOperand::Ptr {
      return a - b;
    });
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

void mul(Stack& s) {
  try {
    operation(s, [](const IOperand& a, const IOperand& b) -> IOperand::Ptr {
      return a * b;
    });
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

void div(Stack& s) {
  try {
    operation(s, [](const IOperand& a, const IOperand& b) -> IOperand::Ptr {
      return a / b;
    });
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

void mod(Stack& s) {
  try {
    operation(s, [](const IOperand& a, const IOperand& b) -> IOperand::Ptr {
      return a % b;
    });
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

std::unique_ptr<IExecElem> ExecSimpleAction::create(
    const std::string& action_name) {
  static const std::map<std::string, Action> actions{
      {"exit", exit},   {"dump", dump}, {"pop", pop},
      {"print", print}, {"add", add},   {"sub", sub},
      {"mul", mul},     {"div", div},   {"mod", mod}};
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
  } catch (utils::RuntimeError& e) {
    throw e;
  }
}

void assert_value(Stack& s, const ExecOperand* op) {
  if (s.empty()) throw utils::RuntimeError("Stack is empty");
  const auto& top = s.top();
  IOperand::Ptr maked_op;
  try {
    maked_op =
        OperandFactory::instance().create_operand(op->type(), op->value());
  } catch (utils::RuntimeError& e) {
    throw e;
  }
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
