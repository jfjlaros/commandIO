EXEC := run_tests
MAIN := test_lib
TESTS := test_examples
FIXTURES := plugins/cli/io plugins/repl/io


CC := g++
INCLUDE := -I . -I ../src
CC_ARGS := -Wno-pmf-conversions -std=c++11


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
