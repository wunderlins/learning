// #define _GNU_SOURCE // required by strsignal on linux

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// #include <string.h>
// #include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
//#include <fcntl.h>

int main(int argc, char *argv[]) {

	int signal_map[1024];
	for(int n=1; n < NSIG; ++n)
		signal_map[strsignal(n)] = n;

	// TODO: implement signal sending
	printf("Parameters: <SIGNAL>%s <PID>%d\n", argv[1], atoi(argv[2]));

	return 0;
}
