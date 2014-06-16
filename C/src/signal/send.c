// #define _GNU_SOURCE // required by strsignal on linux

#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
 #include <signal.h>
// #include <unistd.h>

int main(int argc, char *argv[]) {

	// TODO: implement signal sending
	printf("Parameters: <SIGNAL>%s <PID>%d\n", argv[1], atoi(argv[2]));

	return 0;
}
