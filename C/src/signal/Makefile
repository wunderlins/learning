# 2014, Simon Wunderlin, swunderlinATgmailDTcom, GPL2+

.PHONY: all signal clean kill test send redirect daemon
end = "================================================"

all: clean signal send

signal:
	gcc -std=c99 -Wall -o signal signal.c
	@echo $(end)

redirect:
	gcc -std=c99 -Wall -o redirect redirect.c
	@echo $(end)

daemon:
	gcc -std=c99 -Wall -o daemon daemon.c
	@echo $(end)

send:
	gcc -std=c99 -Wall -o send send.c
	@echo $(end)

clean:
	rm -rf signal || true
	rm -rf send || true
	@echo $(end)

kill:
	./bin/kill.sh
	@echo $(end)
	
pid:
	./bin/pid.sh
	@echo $(end)

test:
	./signal&
	@echo $(end)

diff:
	git diff | colordiff | less -R
	