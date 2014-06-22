#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "util.h"

/**
 * return file descriptor on success, -1 on error.
 */
int create_empty_file(char *file) {
	int fd = 0;
	ssize_t ret;

	// open the file for writing
	fd = open(file, O_RDWR | O_CREAT, 0600);
	if (fd == -1)
		return fd;

	// write template to file
	char header[10] = {
			0x23, 0x40, 0x30,
			0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
	};

	ret = write(fd, &header, 10);
	if (ret == -1)
		return -1;
	// TODO: check for complete write
	/*
	if (ret != 10) {

	}
	*/

	off_t offset = lseek(fd, (off_t) 20, SEEK_SET);
	if (offset == -1)
		return -1;

	// TODO: set permission

	ret = write(fd, "|\0", 2);
	if (ret == -1)
		return -1;

	return fd;
}

void print_file(int fd) {

	lseek(fd, 0, SEEK_SET);

	int i = 0;
	char data_in[1];
	for(; i<22; i++) {
		read(fd, &data_in[0], 1);
		// TODO: catch premature end
		printf("0x%02x ", (int) data_in[0]);

		if (i && (i+1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
}

/**
 * seeking in files, example.
 *
 * off_t lseek (int fd, off_t pos, int origin);
 */
int main(int argc, char *argv[]) {

	/**
	 * Example file:
	 *
	 * 10 bytes: header
	 *           0,1: 0x23, 0x40 # file type descriptor for mime: "#@"
	 *           2  : length of the payload
	 * 20 bytes: payload
	 *  2 bytes: end delimiter == 0x7C, 0x0 "|\0"
	 *
	 * The example data file shall contain 1 byte integers (uint8_t). it may
	 * or may not exists. If it does not exist, it shall be created
	 * with a permission mask of 0600, regardless of what the umask is
	 * telling us.
	 *
	 * empty bytes in payload and header shall set with \0.
	 */
	off_t offset;
	int fd, len;
	char *file = "/tmp/seek.dat";
	// check if the file exists
	fd = open(file, O_RDWR);
	if (fd == -1) {
		if (errno == ENOENT) {
			printf("File does not exist, creating\n");
			// create empty data file
			fd = create_empty_file(file);
			// TODO: check response, fd must be a file descriptor
		} else {
			err("Opening dat file");
			exit(1);
		}
	}

	// payload is passed in as parameter 1 via argv
	if (argc < 2) {
		fprintf(stderr, "parameter 1 is data\n");
		close(fd);
		exit(2);
	}

	// data must not exceed 10 bytes + null character
	len = strlen(argv[1]);
	if (len > 10) {
		fprintf(stderr, "Data too long, max size is 10 bytes\n");
		close(fd);
		exit(3);
	}
	char data[10];
	int i = 0;
	for(i=0; i<10; i++) {
		if (i<len) data[i] = argv[1][i];
		else data[i] = '\0';
	}

	// update header, set length of payload
	offset = lseek(fd, (off_t) 2, SEEK_SET);
	if (offset == -1) {
		err("Failed to move to length offset");
		exit(4);
	}

	char lenc[1] = "0";
	lenc[0] = len;
	ssize_t ret = write(fd, &lenc, 1);
	if (ret == -1) { // check for errors
		perror("write");
		exit(5);
	} else if (ret != 1) {
		printf("Failed to write header, length %d, written %d\n", 1, (int) ret);
		exit(5);
	}

	// ok fine, if we got so far, we need to write the payload to the file
	offset = lseek(fd, (off_t) 10, SEEK_SET);
	if (offset == -1) {
		err("Failed to move to length offset");
		exit(4);
	}
	ret = write(fd, data, 10);
	if (ret == -1) { // check for errors
		perror("write");
		exit(5);
	} else if (ret != 10) {
		printf("Failed to write data, length %d, written %d\n", 10, (int) ret);
		exit(5);
	}

	// display data
	print_file(fd);

	close(fd);
	// TODO: check for errors on close

	return 0;
}
