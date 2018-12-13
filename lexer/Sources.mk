## Auto generated make tool, don't edit manually.

OBJ_FILES_lexer := LexerIterator.o \
                   Token.o \
                   lexer.o \
                   punctuation.o

OBJECTS += $(patsubst %, lexer/$(OBJECT_DIR)/%, $(OBJ_FILES_lexer))