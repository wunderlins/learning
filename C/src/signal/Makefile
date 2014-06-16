.PHONY: all signal clean kill test send
end = "================================================"

all: signal send

signal:
	gcc -std=c99 -Wall -o signal signal.c
	@echo $(end)

send:
	gcc -std=c99 -Wall -o send send.c
	@echo $(end)

clean:
		rm -rf signal || true

kill:
	./bin/kill.sh
	
pid:
	./bin/pid.sh

test:
	./signal&
