.PHONY: all unix_srv  unix_cli doc
end = "================================================"

all: unix_srv unix_cli

unix_srv:
	gcc -std=c99 -Wall -o unix_srv unix_srv.c
	@echo $(end)

unix_cli:
	gcc -std=c99 -Wall -o unix_cli unix_cli.c
	@echo $(end)

doc:
	./bin/doc.sh
