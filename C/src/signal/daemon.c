/**
 * daemonize a process
 */
#define _GNU_SOURCE

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

/**
 * Daemonize a process
 *
 * This method will detach stdin, stdout and stderr from a terminal. stdout
 * and stderr will be redirected to log.
 *
 * exe is usually argv[0], this parameter is use to detirmine the absolute
 * path of the executable. from this point, relative paths are resolved in file
 * names. FIXME: this might not be the best option.
 *
 * The main process is fork()'ed twice, detached from process group and
 * parent processes are terminated.
 *
 * the cwd is set to /, however this might be not the best option.
 */
void daemonize(char *exe, const char *log) {

	char realp[1024] = "";
	realpath(dirname(exe), realp);
	strcat(realp, "/");
	char logfile[1024] = "";
	strcpy(logfile, realp);
	strcat(logfile, log);
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
	int fout = open(logfile, O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP);
	if (fout == -1) {
		fprintf(stderr, "failed to open logfile (errno=%d)\n", errno);
	}
	dup2(fout, STDOUT_FILENO);
	dup2(fout, STDERR_FILENO);
	//close(logfile_fileno);
	close(STDIN_FILENO);
	freopen("/dev/null", "w+", stdin);
}

/**
 * Main
 */
int main(int argc, char *argv[]) {

	daemonize(argv[0], logfile_pathname);

	pid_t pid = getpid();
	printf("started %d\n", pid);

	useconds_t usec = 1000000L;
	int i = 0;
	while(1) {
		//printf("--> %d %d\n", pid, i++);
		fflush(stdout);
		usleep(usec);
	}

	return 0;
}
