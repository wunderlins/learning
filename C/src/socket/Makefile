.PHONY: all unix_srv unix_cli doc clean test
end = "================================================"

all: clean unix_srv unix_cli

unix_srv:
	gcc -std=c99 -Wall -o unix_srv unix_srv.c
	@echo $(end)

unix_cli:
	gcc -std=c99 -Wall -o unix_cli unix_cli.c
	@echo $(end)

doc:
	./bin/doc.sh

clean:
		rm -rf a || true
		rm -rf unix_srv || true
		rm -rf unix_cli || true

test: clean all
	./unix_srv ./a&
	./unix_cli