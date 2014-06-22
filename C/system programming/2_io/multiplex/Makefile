.PHONY:

CC_OPTS=-Wall
GCC=/usr/bin/gcc
BINDIR=../../bin/

all: clean multiplex

multiplex:
	$(GCC) $(CC_OPTS) -o $(BINDIR)multiplex multiplex.c

clean:
	rm $(BINDIR)multiplex || true
