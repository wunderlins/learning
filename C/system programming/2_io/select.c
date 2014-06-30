/**
 * Multiplexed I/O allows an application to concurrently block on multiple file
 * descriptors and receive notification when any one of them becomes ready to
 * read or write without blocking. Multiplexed I/O thus becomes the pivot
 * point for the application, designed similarly to the following activity:
 *
 * 1. Multiplexed I/O: Tell me when any of these file descriptors become
 *    ready for I/O.
 * 2. Nothing ready? Sleep until one or more file descriptors are ready.
 * 3. Woken up! What is ready?
 * 4. Handle all file descriptors ready for I/O, without blocking.
 * 5. Go back to step 1.
 *
 * This example checks for user input continously on stdio. all i/o handling
 * is non-blocking. The CPU usage of this process should stay close to 0.
 */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define TIMEOUT 5
#define BUF_LEN 32

struct timeval tv;
fd_set readfds;


int check() {

	int ret;

	/* Wait on stdin for input. */
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	/* Wait up to five seconds. */
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	/* All right, now block! */
	//ret = select (STDIN_FILENO + 1, &readfds,	NULL, NULL, &tv);
	ret = select (STDIN_FILENO + 1, &readfds,	NULL, NULL, NULL);
	if (ret == -1) {
		perror ("select");
		if (ret == EBADF)
			printf("An invalid file descriptor was provided in one of the sets.\n");
		if (ret == EINTR)
			printf("A signal was caught while waiting, and the call can "
		         "be reissued.\n");
		if (ret == EINVAL)
			printf("The parameter n is negative, or the given timeout is "
		         "invalid.\n");
		if (ret == ENOMEM)
			printf("Insufficient memory was available to complete the request.\n");
		return 1;
	} else if (!ret) {
		printf ("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}

	/*
	 * Is our file descriptor ready to read?
	 * (It must be, as it was the only fd that
	 * we provided and the call returned
	 * nonzero, but we will humor ourselves.)
	 */
	if (FD_ISSET(STDIN_FILENO, &readfds)) {
		char buf[BUF_LEN+1];
		int len;

		/* guaranteed to not block */
		len = read (STDIN_FILENO, buf, BUF_LEN);
		if (len == -1) {
			perror ("read");
			return 1;
		}

		if (len) {
			buf[len] = '\0';
			printf ("read[%d]: %s\n", len, buf);

			if (buf[0] == 'q' && buf[1] == '\n')
				return 2;
		}
		return 0;
	}

	fprintf (stderr, "This should not happen!\n");
	return 1;
}

/* select timeout in seconds */
/* read buffer in bytes */
int main (void) {
	int ret;

	int count = 0;
	printf("Insert some text (quit with q\n");
	while (1) {
		ret = check();
		if (ret) {
			if (ret == 2) {
				printf("quiting\n");
				break;
			}

			printf("Error, aborting.\n");
			return ret;
		}
		printf("next iteration in while %d\n", count++);
	}

	return 0;
}
