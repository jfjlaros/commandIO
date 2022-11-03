EXEC := run_tests
MAIN := test_lib
TESTS := test_examples_cli test_examples_repl
OBJS := ../src/error
FIXTURES := plugins/cli/io plugins/repl/io


CC := g++
INCLUDE := -I fixtures -I ../src
CC_ARGS := -Wall -Wextra -pedantic


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES) $(OBJS))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) $(CC_ARGS) -o $@ $^

%.o: %.cc
	$(CC) $(CC_ARGS) $(INCLUDE) -o $@ -c $<

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
