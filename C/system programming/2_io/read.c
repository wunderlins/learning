#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	
	/**
	 * int open (const char *name, int flags);
	 * int open (const char *name, int flags, mode_t mode);
	 *
	 */
	int fd = open("data.txt", O_RDONLY);

	// this call is supposed to fail because the file does 
	// not exist
	if (fd == -1) {
		const int e = errno;
		printf("failed to open, %d %s\n", e, strerror(e));
		perror("open");
	}

	// now try again with /dev/null
	fd = open("/dev/null", O_RDONLY);
	if (fd == -1) {
		printf("failed to open, %d %s\n", errno, strerror(errno));	
		exit(1);
	}

	printf("Successfully opened /dev/random\n");

	// let's read some bogus length from the file
	unsigned long word;
	ssize_t nr;
	/* read a couple bytes into 'word' from 'fd' */
	nr = read (fd, &word, sizeof(unsigned long));
	if (nr == -1) {
		perror("read");
	}

	// the above example did not read as many characters as we wanted
	printf("Attempted to read %ld bytes, got %d bytes\n", sizeof(unsigned long), (int) nr);
	close(fd);

	// opening a test file, it's input should be shorter than the attempted
	// length to read
	fd = open("test_input.txt", O_RDONLY);
	if (fd == -1) {
		printf("failed to open, %d %s\n", errno, strerror(errno));
		exit(1);
	}

	// doing it the proper way, handling premature end of input
	#define BUFSIZE 1024
	char buf[BUFSIZE];
	int len = 20;
	ssize_t ret;
	int rd = 0;
	int pass = 0;
	while (len != 0 && (ret = read (fd, buf, len)) != 0) {
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			perror ("read");
			break;
		}
		len -= ret;
		rd += (int) ret;
		pass++;
		//buf += (int) ret;
	}
	printf("Attempted to read %d bytes in %d passes, got %d bytes in buffer\n",
			   (int) rd, pass, (int) strlen(buf));
	printf("Buffer: '%s'\n", buf);

	close(fd);

	return 0;
}
