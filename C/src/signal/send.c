// #define _GNU_SOURCE // required by strsignal on linux

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
//#include <fcntl.h>

#include "sig.h"
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int signame_to_signum(char *sig) {
	size_t n;
	for (n = 0; n < ARRAY_SIZE(sys_signame); n++) {
		if (!strcasecmp(sys_signame[n].name, sig))
			return sys_signame[n].val;
	}
	return -1;
}

int main(int argc, char *argv[]) {

	/*
	int signal_map[1024];
	for(int n=1; n < NSIG; ++n)
		signal_map[strsignal(n)] = n;
	*/

	// TODO: implement signal sending
	char subsig[10];
	memcpy(subsig, &(argv[1][3]), strlen(argv[1])-3);
	subsig[strlen(argv[1])-3] = '\0';
	int sign = signame_to_signum(subsig);
	int pid = atoi(argv[2]);
	//printf("sig: %d, %d, %s\n", sign, (int)strlen(argv[1]), subsig);
	printf("Parameters: <SIGNAL>%d <PID>%d\n", sign, pid);

	return 0;
}
