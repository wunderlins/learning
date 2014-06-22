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
	 * There are nuerous flags in the 2nd parameter which control
	 * access to the file, async io and performance.
	 *
	 * When access flags are provided in the flags parameter, the local
	 * umask is taken into account. On BSD systems, some of the flags (gid
	 * upon creation) are inherited by the parent directory.
	 *
	 * While using the 3rd parameter mode, one gets full control over the file's
	 * permission bypassing umask entirely. owning group and user still might
	 * vary over systems. on linux the processes uid/gid are used.
	 */

	// The following typical creat() call,
	char *filename1 = "/tmp/whatever1.txt";
	unlink(filename1);
	int fd;
	fd = creat(filename1, 0644);
	if (fd == -1) {
		/* error */
		;
	}

	// is identical to
	char *filename2 = "/tmp/whatever2.txt";
	unlink(filename2);
	fd = open (filename2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		/* error */
		;
	}


	return 0;
}
