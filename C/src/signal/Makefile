.PHONY: all signal clean
end = "================================================"

all: signal

signal:
	gcc -std=c99 -Wall -o signal signal.c
	@echo $(end)

clean:
		rm -rf signal || true
