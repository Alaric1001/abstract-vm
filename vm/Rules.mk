## Auto generated make tool, don't edit manually.
vm/$(OBJECT_DIR)/%.o: vm/%.cpp
	$(COMP) $@ $<
vm/$(OBJECT_DIR)/ExecActions.o: vm/ExecActions.cpp vm/ExecActions.hpp \
  utils/Stack.hpp utils/RuntimeError.hpp vm/IExecElems.hpp \
  vm/IOperand.hpp vm/Operand.hpp vm/OperandFactory.hpp \
  utils/to_numeric.hpp vm/globals.hpp
vm/ExecActions.hpp:
utils/Stack.hpp:
utils/RuntimeError.hpp:
vm/IExecElems.hpp:
vm/IOperand.hpp:
vm/Operand.hpp:
vm/OperandFactory.hpp:
utils/to_numeric.hpp:
vm/globals.hpp:
vm/$(OBJECT_DIR)/globals.o: vm/globals.cpp vm/globals.hpp
vm/$(OBJECT_DIR)/main.o: vm/main.cpp lexer/lexer.hpp lexer/Token.hpp \
  utils/Dump.hpp parser/parser.hpp vm/ExecActions.hpp utils/Stack.hpp \
  utils/RuntimeError.hpp vm/IExecElems.hpp vm/IOperand.hpp
lexer/lexer.hpp:
lexer/Token.hpp:
utils/Dump.hpp:
parser/parser.hpp:
vm/$(OBJECT_DIR)/Operand.o: vm/Operand.cpp vm/Operand.hpp vm/IOperand.hpp \
  vm/OperandFactory.hpp utils/RuntimeError.hpp utils/to_numeric.hpp
vm/$(OBJECT_DIR)/OperandFactory.o: vm/OperandFactory.cpp \
  vm/OperandFactory.hpp vm/IOperand.hpp vm/Operand.hpp \
  utils/RuntimeError.hpp utils/to_numeric.hpp
