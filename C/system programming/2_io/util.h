/**
 * This header file packs a couple of convenience functions.
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#define err(msg) fprintf(stderr, "%s; [%d] %s\n", msg, errno, strerror(errno));

/**
 * try reading all data from fd even when interrupted
 *
 * This example needs to be verified with a socket or pipe
 */
ssize_t sread(int fd, char *buf, size_t len) {
	ssize_t ret;
	ssize_t rd = 0;

	while (len != 0 && (ret = read(fd, buf, len)) != 0) {
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			return -1;
		}
		len -= ret;
		rd += ret;
	}

	return rd;
}

// TODO: implement swrite()
