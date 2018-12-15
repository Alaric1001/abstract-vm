## Auto generated make tool, don't edit manually.

OBJ_FILES_parser := Errors.o \
                    Handler.o \
                    InstructionHandler.o \
                    parser.o \
                    Pattern.o \
                    ValueHandler.o

OBJECTS += $(patsubst %, parser/$(OBJECT_DIR)/%, $(OBJ_FILES_parser))