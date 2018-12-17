## Auto generated make tool, don't edit manually.

OBJ_FILES_vm := ExecActions.o \
                globals.o \
                IExecElems.o \
                main.o \
                Operand.o \
                OperandFactory.o \
                OptParser.o

OBJECTS += $(patsubst %, vm/$(OBJECT_DIR)/%, $(OBJ_FILES_vm))