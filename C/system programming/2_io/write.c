#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

/**
 * write example, interface:
 * ssize_t write (int fd, const void *buf, size_t count);
 */

int main(int argc, char *argv[]) {

	int fd;
	const char *filename1 = "test_input.txt";
	const char *buf = "0123456789";
	ssize_t nr;

	fd = open(filename1, O_WRONLY | O_CREAT | O_TRUNC,
	                     S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("open");
	}

	/* write the string in 'buf' to 'fd' */
	nr = write (fd, buf, strlen(buf));
	if (nr == -1) { // check for errors
		perror("write");
	}
	int r = close(fd);
	if (r == -1)
		perror("close");

	// write partial data to a file
	fd = open("/tmp/short.txt", O_WRONLY | O_CREAT | O_TRUNC,
	                     S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("open");
	}

	unsigned long word = 1720;
	size_t count;
	nr = 0;
	count = sizeof(word);

	nr = write (fd, &word, word);
	if (nr == -1) { // check for errors
		perror("write");
	} else if (nr != count) {
		printf("Failed to write data, length %d, written %d\n",
				   (int) count, (int) nr);
	}
	/*
	if ((unlink("/tmp/short.txt")) == -1)
		perror("unlink");
	*/

	// for preventing partial writes simmilar techniques as for rad can be used.
	// however, this makes most sense on pipes and sockets.

	return 0;
}
