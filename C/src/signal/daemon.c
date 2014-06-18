/**
 * daemonize a process
 */

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>

const char logfile_pathname[50] = "var/daemon.log";

void daemonise(char **argv) {

	char realp[1024] = "";
	realpath(dirname(argv[0]), realp);
	strcat(realp, "/");
	char logfile[1024] = "";
	strcpy(logfile, realp);
	strcat(logfile, logfile_pathname);
	//printf("%s\n", logfile);

	// Fork, allowing the parent process to terminate.
	pid_t pid = fork();
	if (pid == -1) {
		fprintf(stderr, "failed to fork while daemonising (errno=%d)\n", errno);
	} else if (pid != 0) {
		_exit(0);
	}

	// Start a new session for the daemon.
	if (setsid()==-1) {
		fprintf(stderr, "failed to become a session leader while daemonising(errno=%d)\n", errno);
	}

	// Fork again, allowing the parent process to terminate.
	signal(SIGHUP,SIG_IGN);
	pid=fork();
	if (pid == -1) {
		fprintf(stderr, "failed to fork while daemonising (errno=%d)\n", errno);
	} else if (pid != 0) {
		_exit(0);
	}

	// Set the current working directory to the root directory.
	if (chdir("/") == -1) {
		fprintf(stderr, "failed to change working directory while daemonising (errno=%d)\n", errno);
	}

	printf("pid: %d\n", (int) getpid());

	// Set the user file creation mask to zero.
	umask(0);

	// Close then reopen standard file descriptors.
	/*
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (open("/dev/null",O_RDONLY) == -1) {
		fprintf(stderr, "failed to reopen stdin while daemonising (errno=%d)",errno);
	}
	if (open("/dev/null",O_WRONLY) == -1) {
		fprintf(stderr, "failed to reopen stdout while daemonising (errno=%d)",errno);
	}
	if (open("/dev/null",O_RDWR) == -1) {
		fprintf(stderr, "failed to reopen stderr while daemonising (errno=%d)",errno);
	}
	*/

	/*
	if (open("/dev/null", O_RDONLY) == -1) {
		fprintf(stderr, "failed to reopen stdin while daemonising (errno=%d)\n",errno);
	}
	*/

	int logfile_fileno = open(logfile, O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP);
	if (logfile_fileno == -1) {
		fprintf(stderr, "failed to open logfile (errno=%d)\n", errno);
	}
	dup2(logfile_fileno, STDOUT_FILENO);
	dup2(logfile_fileno, STDERR_FILENO);
	//close(logfile_fileno);
	close(STDIN_FILENO);
}

/**
 * Main
 */
int main(int argc, char *argv[]) {

	daemonise(argv);

	printf("done\n");

	while(1);

	return 0;
}
