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
	} else {
		printf("Successfully opened /dev/null");
		close(fd);
	}

	return 0;
}
