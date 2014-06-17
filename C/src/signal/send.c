/**
 * Simple utility program to send signals to a running program
 *
 * This program expects 2 parameters:
 *  1) signal name
 *  2) process id
 *
 * It will check if the process is running and will then send the signal to
 * the process running under that pid.
 *
 * Exit codes:
 *  0) Success
 *  1) Invalid signal name
 *  2) Invalid pid
 *  3) Process not running
 *  4) Failed to send signal
 *
 * TODO: add usage()
 */

// #define _GNU_SOURCE // required by strsignal on linux

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include "sig.h"

/**
 * signal name to int
 *
 * returns the signal number for a signal name. signame might be SIGHUP or
 * HUP for example.
 *
 * returns
 * -2 for too short sig name
 * -1 for unknown signal
 * >0 signal number
 */
int signum(char* signame)	{
	char sigtmp[10] = "";
	char *sig = sigtmp;

	// if the string is less than 3 characters, abort
	if (strlen(signame) < 3)
		return -2;

	// if the first 3 chars are "SIG", remove them
	if (signame[0] == 'S' && signame[0] == 'I' && signame[0] == 'G') {
		memcpy(sig, &(signame[3]), strlen(signame)-3);
		sig[strlen(signame)-3] = '\0';
	} else {
		sig = signame;
	}

	return signame_to_signum(sig);
}

/**
 * converts character array to long (only positive numbers)
 *
 * will return 0 if any char before '\0' is not a digit, otherwise will
 * return an long int representation of the char array.
 */
long char2int(char* str) {

	// check if there are only digits in the char array
	int i = 0;
	size_t l = strlen(str);
	for (i=0; i<l; i++) {
		if (str[i] == '\0')
			break;
		if (str[i] < 48 || str[i] > 57)
			return 0;
		//printf("%d", str[i]);
	}

	// return int representation
	return atol(str);
}

/**
 * send a unix signal to a process
 *
 * expects parameter 1 to be a signal name, parameter 2 to be a valid process
 * id.
 */
int main(int argc, char *argv[]) {

	// convert signal name to a signal number
	int sign = signum(argv[1]);
	// convert string pid to long
	pid_t pid = char2int(argv[2]);

	// validate user input
	if (sign < 1) {
		fprintf(stderr, "Invalid signal name %s, %d, aborting.\n", argv[1], sign);
		exit(1);
	}

	// check if the pid is greater than 1
	if (pid < 2) {
		fprintf(stderr, "Invalid pid %d, aborting.\n", pid);
		exit(2);
	}

	// check if pid exists, this might only work on linux
	if ((kill((pid_t) pid, 0)) == -1) {
		fprintf(stderr, "Process with pid %d not running, aborting.\n", pid);
		exit(3);
	}

	// send signal to pid, if kill returns -1, the process
	printf("Sending SIGNAL %d to PID %d\n", sign, pid);
	int is_active = kill((pid_t) pid, sign);
	if (is_active != 0) {
		fprintf(stderr, "Failed to send signal %d to pid %d, aborting.\n", sign, pid);
		exit(4);
	}

	return EXIT_SUCCESS;
}
