## Auto generated make tool, don't edit manually.
lexer/$(OBJECT_DIR)/%.o: lexer/%.cpp
	$(COMP) $@ $<
lexer/$(OBJECT_DIR)/lexer.o: lexer/lexer.cpp lexer/lexer.hpp \
  lexer/Token.hpp utils/Dump.hpp lexer/LexerIterator.hpp \
  lexer/punctuation.hpp
lexer/lexer.hpp:
lexer/Token.hpp:
utils/Dump.hpp:
lexer/LexerIterator.hpp:
lexer/punctuation.hpp:
lexer/$(OBJECT_DIR)/LexerIterator.o: lexer/LexerIterator.cpp \
  lexer/LexerIterator.hpp
lexer/$(OBJECT_DIR)/punctuation.o: lexer/punctuation.cpp \
  lexer/punctuation.hpp
lexer/$(OBJECT_DIR)/Token.o: lexer/Token.cpp lexer/Token.hpp \
  utils/Dump.hpp
