## Auto generated make tool, don't edit manually.

OBJ_FILES_parser := ValueHandler.o \
                    Pattern.o \
                    InstructionHandler.o \
                    Handler.o \
                    parser.o

OBJECTS += $(patsubst %, parser/$(OBJECT_DIR)/%, $(OBJ_FILES_parser))