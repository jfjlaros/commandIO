EXEC := $(basename $(shell ls *.cc))
OBJS := ../../src/error ../../src/plugins/cli/io ../../src/plugins/repl/io


CC := g++
INCLUDE_PATH := ../../src
CC_ARGS := -Wall -Wextra -pedantic -I $(INCLUDE_PATH)


OBJS := $(addsuffix .o, $(OBJS))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(EXEC).cc $(OBJS)
	$(CC) $(CC_ARGS) -o $@ $^

%.o: %.cc
	$(CC) $(CC_ARGS) -o $@ -c $^

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
