#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include <sys/socket.h>
#include <sys/un.h>

//char *socket_path = "./socket";
char *socket_path = "\0hidden"; // this seems to be a trick to hide the socket in the current working directory (pwd)

int main(int argc, char *argv[]) {
	struct sockaddr_un addr;
	char buf[100];
	int fd,cl,rc;

	if (argc > 1) socket_path=argv[1];

	char realp[4096];
	//char *realp = malloc(sizeof(char) * (strlen(dir) + strlen(b)));
	realpath(socket_path, realp);
	printf("socket@ %s/%s\n", realp, basename(socket_path));
	fflush(stdout);

	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(-1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

	unlink(socket_path);

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("bind error");
		exit(-1);
	}

	if (listen(fd, 5) == -1) {
		perror("listen error");
		exit(-1);
	}

	while (1) {
		if ( (cl = accept(fd, NULL, NULL)) == -1) {
			perror("accept error");
			continue;
		}

		while ( (rc=read(cl,buf,sizeof(buf))) > 0) {
			printf("read %u bytes: %.*s\n", rc, rc, buf);
		}
		if (rc == -1) {
			perror("read");
			exit(-1);
		}
		else if (rc == 0) {
			printf("EOF\n");
			close(cl);
		}
	}


	return 0;
}

