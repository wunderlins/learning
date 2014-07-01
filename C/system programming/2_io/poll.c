/**
 * poll()
 *
 * The poll() system call is System V’s multiplexed I/O solution. It solves
 * several deficiencies in select(), although select() is still often used
 * (most likely out of habit, or in the name of portability):
 *
 * #include <poll.h>
 *
 * int poll (struct pollfd *fds, nfds_t nfds, int timeout);
 *
 * Unlike select(), with its inefficient three bitmask-based sets of file
 * descriptors, poll() employs a single array of nfds pollfd structures,
 * pointed to by fds. The structure is defined as follows:
 *
 * #include <poll.h>
 *
 * struct pollfd {
 *   int fd;
 *   short events;
 *   short revents;
 * };
 *
 * / * file descriptor * /
 * / * requested events to watch * /
 * / * returned events witnessed * /
 *
 * Each pollfd structure specifies a single file descriptor to watch.
 * Multiple structures may be passed, instructing poll() to watch multiple
 * file descriptors. The events field of each structure is a bitmask of
 * events to watch for on that file descriptor. The user sets this field.
 *
 * The revents field is a bitmask of events that were witnessed on the
 * file descriptor. The kernel sets this field on return. All of the
 * events requested in the events field may be returned in the revents
 * field. Valid events are as follows:
 *
 * POLLIN
 *   There is data to read.
 *
 * POLLRDNORM
 *   There is normal data to read.
 *
 * POLLRDBAND
 *   There is priority data to read.
 *
 * POLLPRI
 *   There is urgent data to read.
 *
 * POLLOUT
 *   Writing will not block.
 *
 * POLLWRNORM
 *   Writing normal data will not block.
 *
 * POLLWRBAND
 *   Writing priority data will not block.
 *
 * POLLMSG
 *   A SIGPOLL message is available.
 *
 * In addition, the following events may be returned in the revents field:
 *
 * POLLER
 *   Error on the given file descriptor.
 *
 * POLLHUP
 *   Hung up event on the given file descriptor.
 *
 * POLLNVAL
 *   The given file descriptor is invalid.
 *
 *
 * Return values and error codes
 *
 * On success, poll() returns the number of file descriptors whose structures
 * have nonzero revents fields. It returns 0 if the timeout occurred
 * before any events occurred. On failure, −1 is returned, and errno is set
 * to one of the following:
 *
 * EBADF
 *   An invalid file descriptor was given in one or more of the structures.
 *
 * EFAULT
 *   The pointer to fds pointed outside of the process’s address space.
 *
 * EINTR
 *   A signal occurred before any requested event. The call may be reissued.
 *
 * EINVAL
 *   The nfds parameter exceeded the RLIMIT_NOFILE value.
 *
 * ENOMEM
 *   Insufficient memory was available to complete the request.
 */

#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#define TIMEOUT 5

/* poll timeout, in seconds */
int main(void) {
	struct pollfd fds[2];
	int ret;

	/* watch stdin for input */
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	/* watch stdout for ability to write (almost always true) */
	fds[1].fd = STDOUT_FILENO;
	fds[1].events = POLLIN;

	/* All set, block! */
	ret = poll(fds, 2, TIMEOUT * 1000);
	if (ret == -1) {
		perror("poll");
		return 1;
	}

	if (!ret) {
		printf("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}

	if (fds[0].revents & POLLIN)
		printf("stdin is readable\n");
	if (fds[1].revents & POLLOUT)
		printf("stdout is writable\n");

	return 0;
}
