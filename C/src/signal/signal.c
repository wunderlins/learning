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

#include "sig.h"

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
			printf("Caught SIGTERM, exiting.\n");
			exit(0);
			break;
		case SIGQUIT:
			printf("Caught SIGQUIT, exiting.\n");
			exit(0);
			break;
		case SIGINT:
			printf("Caught SIGINT, exiting.\n");
			exit(0);
			break;
	}
}

/**
 * main function, register signal handlers
 *
 * registers all known signals from sig.h as signal handler.
 */
int main(int argc, char *argv[]) {

	int n = 0;
	for (n = 0; n < ARRAY_SIZE(sys_signame); n++) {
		printf("Registering %02d %s\n", sys_signame[n].val, sys_signame[n].name);
		signal(sys_signame[n].val, sig_handler);
	}

	/*
	signal(SIGHUP, sig_handler); //        1       Term    Hangup detected on controlling terminal or death of controlling process
	signal(SIGINT, sig_handler); //        2       Term    Interrupt from keyboard
	signal(SIGQUIT, sig_handler); //       3       Core    Quit from keyboard
	signal(SIGILL, sig_handler); //        4       Core    Illegal Instruction
	signal(SIGABRT, sig_handler); //       6       Core    Abort signal from abort(3)
	signal(SIGFPE, sig_handler); //        8       Core    Floating point exception
	signal(SIGKILL, sig_handler); //       9       Term    Kill signal
	signal(SIGSEGV, sig_handler); //      11       Core    Invalid memory reference
	signal(SIGPIPE, sig_handler); //      13       Term    Broken pipe: write to pipe with no readers
	signal(SIGALRM, sig_handler); //      14       Term    Timer signal from alarm(2)
	signal(SIGTERM, sig_handler); //      15       Term    Termination signal
	signal(SIGUSR1, sig_handler); //   30,10,16    Term    User-defined signal 1
	signal(SIGUSR2, sig_handler); //   31,12,17    Term    User-defined signal 2
	signal(SIGCHLD, sig_handler); //   20,17,18    Ign     Child stopped or terminated
	signal(SIGCONT, sig_handler); //   19,18,25    Cont    Continue if stopped
	signal(SIGSTOP, sig_handler); //   17,19,23    Stop    Stop process
	signal(SIGTSTP, sig_handler); //   18,20,24    Stop    Stop typed at tty
	signal(SIGTTIN, sig_handler); //   21,21,26    Stop    tty input for background process
	signal(SIGTTOU, sig_handler); //   22,22,27    Stop    tty output for background process
	*/

	printf("Process id: %d\n", getpid());
	printf("Capturing signals ...\n");

	useconds_t usec = 1000000L;
	while(1) {
		usleep(usec);
	}

	return 0;
}
