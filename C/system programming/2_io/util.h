#include <stdio.h>
#include <string.h>
#include <errno.h>

#define err(msg) fprintf(stderr, "%s; [%d] %s\n", msg, errno, strerror(errno));
