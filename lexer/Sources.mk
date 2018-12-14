## Auto generated make tool, don't edit manually.

OBJ_FILES_lexer := lexer.o \
                   LexerIterator.o \
                   punctuation.o \
                   Token.o

OBJECTS += $(patsubst %, lexer/$(OBJECT_DIR)/%, $(OBJ_FILES_lexer))