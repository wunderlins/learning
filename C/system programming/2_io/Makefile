.PHONY: 

CC_OPTS=-Wall
GCC=/usr/bin/gcc
BINDIR=../bin/

all: clean read open creat

read:
	$(GCC) $(CC_OPTS) -o $(BINDIR)read read.c

open:
	$(GCC) $(CC_OPTS) -o $(BINDIR)open open.c

creat:
	$(GCC) $(CC_OPTS) -o $(BINDIR)creat creat.c


clean:
	rm $(BINDIR)* || true