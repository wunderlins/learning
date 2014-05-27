.PHONY: fp fps
end = "================================================"

all: fp fps

fp:
	gcc -std=c99 -Wall -o fp fp.c
	@echo $(end)

# WTF of the day, use -lm if you include <math.h>
fps:
	gcc -lm -std=c99 -Wall -o fps fps.c
	@echo $(end)

