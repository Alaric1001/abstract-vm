## Auto generated make tool, don't edit manually.
parser/$(OBJECT_DIR)/%.o: parser/%.cpp
	$(COMP) $@ $<
parser/$(OBJECT_DIR)/Handler.o: parser/Handler.cpp parser/Handler.hpp \
  lexer/Token.hpp utils/Dump.hpp parser/Pattern.hpp parser/Errors.hpp
parser/Handler.hpp:
lexer/Token.hpp:
utils/Dump.hpp:
parser/Pattern.hpp:
parser/Errors.hpp:
parser/$(OBJECT_DIR)/InstructionHandler.o: parser/InstructionHandler.cpp \
  parser/InstructionHandler.hpp parser/Handler.hpp lexer/Token.hpp \
  utils/Dump.hpp parser/Pattern.hpp parser/ValueHandler.hpp
parser/InstructionHandler.hpp:
parser/ValueHandler.hpp:
parser/$(OBJECT_DIR)/parser.o: parser/parser.cpp parser/parser.hpp \
  lexer/Token.hpp utils/Dump.hpp parser/InstructionHandler.hpp \
  parser/Handler.hpp parser/Pattern.hpp
parser/parser.hpp:
parser/$(OBJECT_DIR)/Pattern.o: parser/Pattern.cpp parser/Pattern.hpp \
  lexer/Token.hpp utils/Dump.hpp
parser/$(OBJECT_DIR)/ValueHandler.o: parser/ValueHandler.cpp \
  parser/ValueHandler.hpp parser/Handler.hpp lexer/Token.hpp \
  utils/Dump.hpp parser/Pattern.hpp
