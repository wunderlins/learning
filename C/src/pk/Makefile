exe_name = pk
CC = gcc
CC_ARGS = -Wall -std=c99
RM = /bin/rm
LN = /bin/ln

clean:
	$(RM) pk || true
	$(RM) pki || true
	$(RM) pks || true
	$(RM) pkl || true

all: clean
	$(CC) $(CC_ARGS) -o $(exe_name) pk.c
	$(LN) $(exe_name) $(exe_name)i
	$(LN) $(exe_name) $(exe_name)s
	$(LN) $(exe_name) $(exe_name)l
