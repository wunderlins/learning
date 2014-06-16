.PHONY: libbitshift bitshift
CC_OPTS=-Wall -std=c99
LIBNAME=bitshift
RM=/bin/rm
GCC=/usr/bin/gcc

all: clean libbitshift bitshift
	$(MAKE) -C bitfields
	$(MAKE) -C function_pointer
	$(MAKE) -C pk
	$(MAKE) -C struct
	$(MAKE) -C signal

clean:
	$(RM) $(LIBNAME) lib$(LIBNAME).o lib$(LIBNAME).so *~ 2>/dev/null || true

bitshift:
	$(GCC) $(CC_OPTS) -o $(LIBNAME) $(LIBNAME).c

libbitshift:
	$(GCC) $(CC_OPTS) -c -fPIC $(LIBNAME).c -o lib$(LIBNAME).o
	$(GCC) $(CC_OPTS) -shared -Wl,-soname,lib$(LIBNAME).so -o lib$(LIBNAME).so lib$(LIBNAME).o
	$(RM) lib$(LIBNAME).o
