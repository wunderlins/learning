#!/usr/bin/env bash

E_PARAM=1

if [[ $# < 2 ]]; then
	f=$(basename "$0")
	echo "usage: $f <SIGNAL> <PID>"
	cat <<-EOT
		
		Available Signals are:
		
		SIGHUP        1       Term    Hangup detected on controlling terminal
		                              or death of controlling process
		SIGINT        2       Term    Interrupt from keyboard
		SIGQUIT       3       Core    Quit from keyboard
		SIGILL        4       Core    Illegal Instruction
		SIGABRT       6       Core    Abort signal from abort(3)
		SIGFPE        8       Core    Floating point exception
		SIGKILL       9       Term    Kill signal
		SIGSEGV      11       Core    Invalid memory reference
		SIGPIPE      13       Term    Broken pipe: write to pipe with no
		                              readers
		SIGALRM      14       Term    Timer signal from alarm(2)
		SIGTERM      15       Term    Termination signal
		SIGUSR1   30,10,16    Term    User-defined signal 1
		SIGUSR2   31,12,17    Term    User-defined signal 2
		SIGCHLD   20,17,18    Ign     Child stopped or terminated
		SIGCONT   19,18,25    Cont    Continue if stopped
		SIGSTOP   17,19,23    Stop    Stop process
		SIGTSTP   18,20,24    Stop    Stop typed at tty
		SIGTTIN   21,21,26    Stop    tty input for background process
		SIGTTOU   22,22,27    Stop    tty output for background process

EOT
	exit $E_PARAM;
fi

#echo "kill -s $1 $2";
kill -s $1 $2