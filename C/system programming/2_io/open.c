#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * int open (const char *name, int flags);
 * int open (const char *name, int flags, mode_t mode);
 */

int main(int argc, char* argv[]) {

	/**
	 * There are numerous flags in the 2nd parameter which control
	 * access to the file, async io and performance.
	 */

	int fd;

	char *filename1 = "/tmp/whatever1.txt";
	unlink(filename1);
	fd = open(filename1, O_WRONLY | O_CREAT | O_TRUNC,
	                     S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("open");
	}

	// a less portable example (in theory) but easier to read. POSIX does allow
	// the permission bits to be set to other vlaues than 4,2,1. however in
	// practice all unix systems adhere to this. i wonder how Microsoft Unix
	// services and cygwin are dealing with this.
	char *filename2 = "/tmp/whatever3.txt";
	unlink(filename2);
	fd = open(filename2, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1) {
		perror("open");
	}

	return 0;
}
