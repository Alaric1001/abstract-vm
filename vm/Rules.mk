## Auto generated make tool, don't edit manually.
vm/$(OBJECT_DIR)/%.o: vm/%.cpp
	$(COMP) $@ $<
vm/$(OBJECT_DIR)/main.o: vm/main.cpp lexer/lexer.hpp lexer/Token.hpp \
  utils/Dump.hpp
lexer/lexer.hpp:
lexer/Token.hpp:
utils/Dump.hpp:
