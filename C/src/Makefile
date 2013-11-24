.PHONY: libbitshift bitshift
CC_OPTS=-Wall -std=c99
LIBNAME=bitshift
rm=/bin/rm

clean:
	$(rm) $(LIBNAME) lib$(LIBNAME).o lib$(LIBNAME).so *~ || true

bitshift:
	gcc $(CC_OPTS) -o $(LIBNAME) $(LIBNAME).c

libbitshift:
	gcc $(CC_OPTS) -c -fPIC $(LIBNAME).c -o lib$(LIBNAME).o
	gcc $(CC_OPTS) -shared -Wl,-soname,lib$(LIBNAME).so -o lib$(LIBNAME).so lib$(LIBNAME).o
