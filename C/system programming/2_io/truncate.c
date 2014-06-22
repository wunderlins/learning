/**
 * Linux provides two system calls for truncating the length of a file, both of
 * which are defined and required (to varying degrees) by various POSIX
 * standards. They are:
 *
 * #include <unistd.h>
 * #include <sys/types.h>
 * int ftruncate (int fd, off_t len);
 *
 * and:
 * #include <unistd.h>
 * #include <sys/types.h>
 * int truncate (const char *path, off_t len);
 */

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "util.h"

char *file = "/tmp/truncate.dat";

/**
 * this example shows how to tuncate files on file drescriptors and
 * file names.
 */
int main(int argc, char *argv[]) {
	int fd;
	off_t len;

	// first create a file, if it doesn't exist and delete it's content
	fd = open(file, O_RDWR | O_CREAT, 0600);
	if (fd == -1) {
		err("Failed to open file.");
		return 1;
	}

	// truncate file on fd
	len = 0;
	int ret = ftruncate(fd, len);
	if (ret == -1) {
		err("Failed to ftruncate");
		return 2;
	}

	// now fill the file with some data.
	char *text = "This is a line, it could be very long but it isn't.";
	ret = write(fd, text, strlen(text)+1);
	if (ret == -1) {
		err("Failed to write to file");
		return 3;
	}

	// now close the file

	// truncate it to 200, check file size. the characters beyond the text
	// should be filled with \0 oes.
	len = 200;
	ret = truncate(file, len);
	if (ret == -1) {
		err("Failed to truncate");
		return 4;
	}



	return 0;
}
