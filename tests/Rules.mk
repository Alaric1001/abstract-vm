TEST_CC			:= clang++
TEST_CFLAGS		:= -I. -std='c++11' -g
TEST_LFLAGS		:= -lcriterion
ifeq ($(shell uname -s), Darwin)
TEST_CFLAGS		+= -I/Users/asenat/.brew/include
TEST_LFLAGS		+= -L/Users/asenat/.brew/Cellar/criterion/2.3.2/lib
endif
COMPLINK		:= $(CC) $(TEST_CFLAGS) $(TEST_LFLAGS) -o

CURR_DIR		:= tests
TEST_FILES		:=

TEST_OBJECTS	:= $(addprefix $(CURR_DIR)/$(OBJECT_DIR)/, $(TEST_FILES:.cpp=.o))
RUN_TEST_RULES	:= $(addprefix run-, $(TEST_FILES:.cpp=))

TEST_FILES	:= $(addprefix $(CURR_DIR)/, $(TEST_FILES))
TEST_TARGETS	:= $(TEST_FILES:.cpp=)
TEST_OBJ_DIR	:= $(CURR_DIR)/$(OBJECT_DIR)

OBJ_DIRS 		+= $(TEST_OBJ_DIR)

.PRECIOUS: $(TEST_TARGETS) $(TEST_OBJECTS)
.PHONY: run-all-tests
run-all-tests: $(RUN_TEST_RULES)

.PHONY: clear-tests
clear-tests:
	rm -rf $(TEST_OBJ_DIR)
	rm -f $(TEST_TARGETS)

run-%: all $(TEST_OBJ_DIR) $(CURR_DIR)/%
	@$(ECHO) $(BLUE)$*":"$(RESET)
	@$(CURR_DIR)/$*

$(CURR_DIR)/%: $(CURR_DIR)/$(OBJECT_DIR)/%.o $(NAME)
	$(TEST_CC) $(TEST_LFLAGS) -o $@ $< $(subst vm/obj/main.o,,$(OBJECTS))

$(CURR_DIR)/$(OBJECT_DIR)/%.o: $(CURR_DIR)/%.cpp
	$(TEST_CC) $(TEST_CFLAGS) -c -o $@ $<
$(TEST_OBJ_DIR):
	mkdir $@
