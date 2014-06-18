/**
 * from man 7 signal (Debian GNU/Linux 7):
 *
 * Standard Signals
 *
 * Linux  supports the standard signals listed below.  Several signal num‐
 * bers are architecture-dependent, as indicated in  the  "Value"  column.
 * (Where three values are given, the first one is usually valid for alpha
 * and sparc, the middle one for x86, arm, and most  other  architectures,
 * and  the  last one for mips.  (Values for parisc are not shown; see the
 * Linux kernel source for signal numbering on that  architecture.)   A  -
 * denotes that a signal is absent on the corresponding architecture.)
 *
 * First the signals described in the original POSIX.1-1990 standard.
 *
 * Signal     Value     Action   Comment
 * ──────────────────────────────────────────────────────────────────────
 * SIGHUP        1       Term    Hangup detected on controlling terminal
 *                               or death of controlling process
 * SIGINT        2       Term    Interrupt from keyboard
 * SIGQUIT       3       Core    Quit from keyboard
 * SIGILL        4       Core    Illegal Instruction
 * SIGABRT       6       Core    Abort signal from abort(3)
 * SIGFPE        8       Core    Floating point exception
 * SIGKILL       9       Term    Kill signal
 * SIGSEGV      11       Core    Invalid memory reference
 * SIGPIPE      13       Term    Broken pipe: write to pipe with no
 *                               readers
 * SIGALRM      14       Term    Timer signal from alarm(2)
 * SIGTERM      15       Term    Termination signal
 * SIGUSR1   30,10,16    Term    User-defined signal 1
 * SIGUSR2   31,12,17    Term    User-defined signal 2
 * SIGCHLD   20,17,18    Ign     Child stopped or terminated
 * SIGCONT   19,18,25    Cont    Continue if stopped
 * SIGSTOP   17,19,23    Stop    Stop process
 * SIGTSTP   18,20,24    Stop    Stop typed at tty
 * SIGTTIN   21,21,26    Stop    tty input for background process
 * SIGTTOU   22,22,27    Stop    tty output for background process
 *
 * The signals SIGKILL and SIGSTOP cannot be caught, blocked, or ignored.
 *
 * Next  the  signals  not  in  the POSIX.1-1990 standard but described in
 * SUSv2 and POSIX.1-2001.
 *
 * Signal       Value     Action   Comment
 * ────────────────────────────────────────────────────────────────────
 * SIGBUS      10,7,10     Core    Bus error (bad memory access)
 * SIGPOLL                 Term    Pollable event (Sys V).
 *                                 Synonym for SIGIO
 * SIGPROF     27,27,29    Term    Profiling timer expired
 * SIGSYS      12,31,12    Core    Bad argument to routine (SVr4)
 * SIGTRAP        5        Core    Trace/breakpoint trap
 * SIGURG      16,23,21    Ign     Urgent condition on socket (4.2BSD)
 * SIGVTALRM   26,26,28    Term    Virtual alarm clock (4.2BSD)
 * SIGXCPU     24,24,30    Core    CPU time limit exceeded (4.2BSD)
 * SIGXFSZ     25,25,31    Core    File size limit exceeded (4.2BSD)

 * Up to and including Linux 2.2, the default behavior for  SIGSYS,  SIGX‐
 * CPU,  SIGXFSZ,  and (on architectures other than SPARC and MIPS) SIGBUS
 * was to terminate the process (without a core  dump).   (On  some  other
 * UNIX systems the default action for SIGXCPU and SIGXFSZ is to terminate
 * the  process  without  a  core  dump.)   Linux  2.4  conforms  to   the
 * POSIX.1-2001  requirements  for  these signals, terminating the process
 * with a core dump.
 *
 * Next various other signals.
 *
 * Signal       Value     Action   Comment
 * ────────────────────────────────────────────────────────────────────
 * SIGIOT         6        Core    IOT trap. A synonym for SIGABRT
 * SIGEMT       7,-,7      Term
 * SIGSTKFLT    -,16,-     Term    Stack fault on coprocessor (unused)
 * SIGIO       23,29,22    Term    I/O now possible (4.2BSD)
 * SIGCLD       -,-,18     Ign     A synonym for SIGCHLD
 * SIGPWR      29,30,19    Term    Power failure (System V)
 * SIGINFO      29,-,-             A synonym for SIGPWR
 * SIGLOST      -,-,-      Term    File lock lost (unused)
 * SIGWINCH    28,28,20    Ign     Window resize signal (4.3BSD, Sun)
 * SIGUNUSED    -,31,-     Core    Synonymous with SIGSYS
 *
 * (Signal 29 is SIGINFO / SIGPWR on an alpha but SIGLOST on a sparc.)
 *
 * SIGEMT is not specified in POSIX.1-2001, but  nevertheless  appears  on
 * most  other UNIX systems, where its default action is typically to ter‐
 * minate the process with a core dump.
 *
 * SIGPWR (which is not specified in POSIX.1-2001) is typically ignored by
 * default on those other UNIX systems where it appears.
 *
 * SIGIO (which is not specified in POSIX.1-2001) is ignored by default on
 * several other UNIX systems.
 *
 * Where defined, SIGUNUSED is synonymous with SIGSYS  on  most  architec‐
 * tures.
 *
 * 2014, Simon Wunderlin, swunderlinATgmailDTcom, GPL2+
 */

#define _GNU_SOURCE // required by strsignal on linux

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>

#include "sig.h"

void shutdown() {
	//fclose(fout);
	int ret = unlink(signals_pid);
	if(ret < 0) {
		printf("Error %d, %s\n", errno, strerror(errno));
		fprintf(stderr, "Failed to remove pid file %s\n", signals_pid);
		exit(4);
	}
}

/**
 * handle signal
 *
 * will always exit upon SIGQUIT, SIGTERM, SIGINT. Cannot catch SIGKILL and
 * SIGSTOP.
 */
void sig_handler(int sig) {

	const char *signame = signum_to_signame(sig);
	printf("Signal [%d] %s, %s\n", sig, signame, strsignal(sig));

	switch (sig) {
		case SIGTERM:
			shutdown();
			printf("Caught SIGTERM, exiting.\n");
			exit(0);
			break;
		case SIGQUIT:
			shutdown();
			printf("Caught SIGQUIT, exiting.\n");
			exit(0);
			break;
		case SIGINT:
			shutdown();
			printf("Caught SIGINT, exiting.\n");
			exit(0);
			break;
	}
	fflush(stdout);
}

/**
 * redirect a file io to another file
 *
 * this is useful to redirect stdou or stderr to a different file. really
 * required for daemonized jobs.
 *
 * The return value is the old filedescriptors fileno (positive int) or a
 * negative value on error.
 *  -1: failed to open file
 *  -2: failed to duplicate old file handle
 */
int redirect_io(const char *filename, FILE *fh, mode_t mask) {
	//char *file = "var/test.log";

	if (mask == 0)
		mask = 0600;

	fflush(fh);

	int fp = open(filename, O_RDWR|O_CREAT|O_APPEND, mask);
	if (fp == -1)
		return -1;

	int save_out = dup(fileno(fh));
	if (dup2(fp, fileno(fh)) == -1)
		return -2;

	close(fp);
	return save_out;
}

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

	/*
	char realp[1024] = "";
	realpath(dirname(exe), realp);
	strcat(realp, "/");
	*/
	char logfile[1024] = "";
	//strcpy(logfile, realp);
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
		fprintf(stderr, "failed to become a session leader while "
				            "daemonising(errno=%d)\n", errno);
	}

	// Fork again, allowing the parent process to terminate.
	signal(SIGHUP, SIG_IGN);
	pid=fork();
	if (pid == -1) {
		fprintf(stderr, "failed to fork while daemonising (errno=%d)\n", errno);
	} else if (pid != 0) {
		_exit(0);
	}

	// Set the current working directory to the root directory.
	if (chdir("/") == -1) {
		fprintf(stderr, "failed to change working directory while "
				            "daemonising (errno=%d)\n", errno);
	}

	printf("pid: %d\n", (int) getpid());

	// Set the user file creation mask to zero.
	umask(0);

	// Close then reopen standard file descriptors.
	int logfile_fileno = open(logfile, O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP);
	if (logfile_fileno == -1) {
		fprintf(stderr, "failed to open logfile (errno=%d), %s\n", errno, logfile);
	}
	dup2(logfile_fileno, STDOUT_FILENO);
	dup2(logfile_fileno, STDERR_FILENO);
	//close(logfile_fileno);
	close(STDIN_FILENO);
	freopen("/dev/null", "w+", stdin);
}

/**
 * main function, register signal handlers
 *
 * registers all known signals from sig.h as signal handler.
 */
int main(int argc, char *argv[]) {

	// check if we have a signal description in var/signals.dat, if not create
	// the file
	char realp[1024] = "";
	char realp_signals_dat[1024] = "";
	char realp_signals_pid[1024] = "";
	char realp_signals_out[1024] = "";
	
	realpath(dirname(argv[0]), realp);
	strcat(realp, "/");
	
	strcpy(realp_signals_dat, realp);
	strcpy(realp_signals_pid, realp);
	strcpy(realp_signals_out, realp);
	strcat(realp_signals_dat, signals_dat);
	strcat(realp_signals_pid, signals_pid);
	strcat(realp_signals_out, signals_out);

	// check if var directory exists
	char var_dir[] = "var";
	struct stat var_dir_s = {0};

	if (stat(var_dir, &var_dir_s)) {
		// if not, create it

		printf("%s %d\n", var_dir, (var_dir_s.st_mode & S_IFDIR));
		//printf("'%s' is %sa directory.\n", var_dir, (var_dir_s.st_mode & S_IFDIR)  : "" ? "not ");

		mode_t process_mask = umask(0);
		int ret = mkdir((const char *) var_dir, S_IRWXU);
		//int result_code = mkdir("/usr/local/logs", S_IRWXU | S_IRWXG | S_IRWXO)
		umask(process_mask);

		// if fails, handle error
		if (ret == -1) {
			fprintf(stderr, "failed to create var directory.\n");
			exit(1);
		} else
			fprintf(stdout, "Created directory var.\n");
	}

	// open var/signals.dat
	printf("Openging '%s'\n", realp_signals_dat);
	fps = fopen(realp_signals_dat, "w");

	if(fps == NULL) {
		printf("Error %d, %s\n", errno, strerror(errno));
		fprintf(stderr, "Failed to open %s\n", signals_dat);
		exit(2);
	}

	// done initializing
	printf("Detatching from terminal ...\n");
	
	// daemonize the process, detach it from TTY
	daemonize(argv[0], realp_signals_out);

	// write pid file
	fpp = fopen(realp_signals_pid, "w");
	if(fpp == NULL) {
		printf("Error %d, %s\n", errno, strerror(errno));
		fprintf(stderr, "Failed to open %s\n", signals_pid);
		exit(4);
	}
	fprintf(fpp, "%d", getpid());
	fclose(fpp);

	// subscribe to all known signals and write the signal num=>name to fps
	printf("Capturing signals ...\n");
	int n = 0;
	for (n = 0; n < ARRAY_SIZE(sys_signame); n++) {
		printf("Registering %02d %s\n", sys_signame[n].val, sys_signame[n].name);
		fprintf(fps, "%d %s\n", sys_signame[n].val, sys_signame[n].name);
		signal(sys_signame[n].val, sig_handler);
	}
	fclose(fps);

	/*
	// fork the process
	pid_t pid = fork();
	if (pid == -1)
		fprintf(stderr, "Failed to fork\n");
	else if (pid != 0) 
		exit(0); // exit the original process

	// Start a new session for the daemon. This is important so that we
	// detatch the new forked process from the process tree
	if (setsid()==-1) {
		fprintf(stderr, "failed to become a session leader while "
		                "daemonising(errno=%d)",errno);
		exit(5);
	}
	
	// WTF: don't know why I have to send this signal, but it seems to be
	//      required
	signal(SIGHUP,SIG_IGN);
	close(STDIN_FILENO);

	// Fork again, allowing the parent process to terminate.
	signal(SIGHUP,SIG_IGN);
	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "failed to fork while daemonising (errno=%d)",errno);
		exit(2);
	} else if (pid != 0) {
		exit(0);
	}
	//printf("Process id: %d\n", getpid());
	// successfully started, write pid file
	fpp = fopen(realp_signals_pid, "w");
	if(fpp == NULL) {
		printf("Error %d, %s\n", errno, strerror(errno));
		fprintf(stderr, "Failed to open %s\n", signals_pid);
		exit(4);
	}
	fprintf(fpp, "%d", getpid());
	fclose(fpp);
	printf("Process id: %d\n", getpid());
	
	if (chdir("/") == -1) {
		fprintf(stderr, "failed to change working directory "
	                  "while daemonizing (errno=%d)", errno);
		exit(2);
	}
	
	// Set the user file creation mask to zero.
	umask(0);

	// detach stdout, stderr and redirect them to a file. also
	// close stdin, because it is of no use for us.
	/ * int old_stdout = * / redirect_io(realp_signals_out, stdout, 0600);
	/ * int old_stderr = * / redirect_io(realp_signals_out, stderr, 0600);
	close(STDIN_FILENO);
	*/

	/*
	// Close then reopen stdin, stdout and stderr
	if (open("/dev/null",O_RDONLY) == -1) {
		fprintf(stderr,"failed to reopen stdin while daemonising (errno=%d)", errno);
		exit(3);
	}
	if ((fout = freopen(realp_signals_out, "w+", stdout)) == NULL) {
		fprintf(stderr, "failed to reopen stdout while daemonising (errno=%d)", errno);
		exit(3);
	}
	if (open("/dev/null",O_RDWR) == -1) {
		fprintf(stderr, "failed to reopen stderr while daemonising (errno=%d)", errno);
		exit(3);
	}
	*/

	printf("started %d\n", getpid());
	useconds_t usec = 1000000L;
	int i = 0;
	pid_t pid = getpid();
	while(1) {
		//printf("%d %d\n", i++, pid);
		usleep(usec);
	}
	
	//fclose(fout);

	return 0;
}
