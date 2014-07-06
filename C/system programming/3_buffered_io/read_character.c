#include <stdio.h>

int main(int argc, char *argv[]) {
	int c;
	FILE *stream;
	c = fgetc (stream);
	
	if (c == EOF)
		/* error */
		;
	else
		printf ("c=%c\n", (char) c);

	return 0;
}
