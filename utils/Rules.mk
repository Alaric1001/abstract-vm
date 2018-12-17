## Auto generated make tool, don't edit manually.
utils/$(OBJECT_DIR)/%.o: utils/%.cpp
	$(COMP) $@ $<
utils/$(OBJECT_DIR)/get_invalid_operation_exception.o: \
  utils/get_invalid_operation_exception.cpp \
  utils/get_invalid_operation_exception.hpp utils/RuntimeError.hpp \
  utils/operation_state.hpp
utils/get_invalid_operation_exception.hpp:
utils/RuntimeError.hpp:
utils/operation_state.hpp:
utils/$(OBJECT_DIR)/Logger.o: utils/Logger.cpp utils/Logger.hpp
utils/Logger.hpp:
utils/$(OBJECT_DIR)/RuntimeError.o: utils/RuntimeError.cpp \
  utils/RuntimeError.hpp vm/globals.hpp
vm/globals.hpp:
utils/$(OBJECT_DIR)/to_numeric.o: utils/to_numeric.cpp \
  utils/to_numeric.hpp
utils/to_numeric.hpp:
