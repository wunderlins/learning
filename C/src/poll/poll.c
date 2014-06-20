#include <stdio.h>
#include <poll.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	
	ssize_t n = 0;
	char buf[1024] = "";
	struct pollfd fds[1];

	while (1) {

		printf("new iteration\n");

		fds[0].fd = STDIN_FILENO;
		fds[0].events = POLLIN;

		// poll will trigger an revent if "\n" is sent on stdin. probably also
		// with other characters/events ... need to figure out what
		// triggers events
		//
		// -1 timeout == wait for inifite time, blocking?
		poll(fds, 1, 1000L);

		if (fds[0].revents & POLLIN) {
			n = read(fds[0].fd, buf, 1024);
			if (!n) {
				printf("stdin closed\n");
				return 0;
			}

			fprintf(stdout, "--> %s\n", buf);
		}
	}

	return 0;
}
