.PHONY: diff clean 

CC_OPTS=-Wall
GCC=/usr/bin/gcc
BINDIR=../bin/

all: clean read open creat write fsync seek truncate select poll

poll:
	$(GCC) $(CC_OPTS) -o $(BINDIR)poll poll.c
	
select:
	$(GCC) $(CC_OPTS) -o $(BINDIR)select select.c
	
truncate:
	$(GCC) $(CC_OPTS) -o $(BINDIR)truncate truncate.c

seek:
	$(GCC) $(CC_OPTS) -o $(BINDIR)seek seek.c

fsync:
	$(GCC) $(CC_OPTS) -o $(BINDIR)fsync fsync.c

write:
	$(GCC) $(CC_OPTS) -o $(BINDIR)write write.c

read:
	$(GCC) $(CC_OPTS) -o $(BINDIR)read read.c

open:
	$(GCC) $(CC_OPTS) -o $(BINDIR)open open.c

creat:
	$(GCC) $(CC_OPTS) -o $(BINDIR)creat creat.c


clean:
	rm $(BINDIR)* || true

diff:
	git diff | colordiff | less -R