#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * Neither function guarantees that any updated directory entries containing
 * the file are synchronized to disk. This implies that if a file’s link
 * has recently been updated, the file’s data may successfully reach the
 * disk but not the associated directory entry, rendering the file
 * unreachable. To ensure that any updates to the directory entry are
 * also committed to disk, fsync() must also be called on a
 * file descriptor opened against the file’s directory.
 *
 * Return values and error codes
 * On success, both calls return 0. On failure, both calls
 * return −1 and set errno to one of the following three values:
 * EBADF
 *   The given file descriptor is not a valid file descriptor open for
 *   writing.
 *
 * EINVAL
 *   The given file descriptor is mapped to an object that does not
 *   support synchronization.
 *
 * EIO
 *   A low-level I/O error occurred during synchronization. This represents
 *   a real I/O	error, and is often the place where such errors are caught.
 */

int main(int argc, char *argv[]) {

	int fd;

	fd = open("/tmp/sync.txt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
      S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("open");
	}

	int i, n = 0;
	size_t nri, nrn = 0;
	char cc[2] = "0";
	for (i=0; i<10; i++) {
		for (n=0; n<10; n++) {
			cc[0] = (n + 0x30);
			nrn = write(fd, cc, 1);
			if (nrn == -1) { // check for errors
				perror("write");
			} else if (nrn != 1) {
				printf("Failed to write all data, expected %d, wrote %d\n",
						    (int) sizeof(int), (int) nrn);
			}
		}

		nri = write(fd, "\n", 1);
		if (nri == -1) { // check for errors
			printf("failed to write, [%d] %s\n", errno, strerror(errno));
		} else if (nri != 1) {
			printf("Failed to write all data, expected %d, wrote %d\n",
					    (int) sizeof(char), (int) nri);
		}
	}

	int ret;
	ret = fsync (fd);
	if (ret == -1) {
		printf("Failed to fsync(), errno %d: %s", errno, strerror(errno));
	}

	// or when using fdatasync()
	ret = 0;
	/* same as fsync, but won't flush non-essential metadata */
	ret = fdatasync (fd);
	if (ret == -1) {
		printf("Failed to fdatasync(), errno %d: %s", errno, strerror(errno));
	}

	close(fd);

	return 0;
}
