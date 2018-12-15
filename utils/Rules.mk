## Auto generated make tool, don't edit manually.
utils/$(OBJECT_DIR)/%.o: utils/%.cpp
	$(COMP) $@ $<
utils/$(OBJECT_DIR)/get_invalid_value_exception.o: \
  utils/get_invalid_value_exception.cpp \
  utils/get_invalid_value_exception.hpp utils/RuntimeError.hpp \
  utils/operation_state.hpp
utils/get_invalid_value_exception.hpp:
utils/RuntimeError.hpp:
utils/operation_state.hpp:
utils/$(OBJECT_DIR)/to_numeric.o: utils/to_numeric.cpp \
  utils/to_numeric.hpp
utils/to_numeric.hpp:
utils/$(OBJECT_DIR)/RuntimeError.o: utils/RuntimeError.cpp \
  utils/RuntimeError.hpp vm/globals.hpp
vm/globals.hpp:
