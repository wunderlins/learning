.PHONY: all bitfields doc
end = "================================================"

all: bitfields

bitfields:
	gcc -std=c99 -Wall -o bitfields bitfields.c
	@echo $(end)

doc:
	./bin/doc.sh
