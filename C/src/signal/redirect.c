#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * redirect a file io to another file
 *
 * this is useful to redirect stdou or stderr to a different file. really
 * required for daemonized jobs.
 *
 * The return value is the old filedescriptors fileno (positive int) or a
 * negative value on error.
 *  -1: failed to open file
 *  -2: failed to duplicate old file handle
 */
int redirect_io(const char *filename, FILE *fh, mode_t mask) {
	//char *file = "var/test.log";

	if (mask == 0)
		mask = 0600;

	fflush(fh);

	int fp = open(filename, O_RDWR|O_CREAT|O_APPEND, mask);
	if (fp == -1)
		return -1;

	int save_out = dup(fileno(fh));
	if (dup2(fp, fileno(fh)) == -1)
		return -2;

	close(fp);
	return save_out;
}


int main() {

	char *file = "var/test.log";

	int old_file_num = redirect_io(file, stdout, 0600);

	puts("doing an ls or something now");

	/*
	fflush(stdout); close(out);

	dup2(save_out, fileno(stdout));

	close(save_out);

	puts("back to normal output");
	*/

	return 0;
}
