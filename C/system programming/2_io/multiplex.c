/**
 * Multiplexed I/O allows an application to concurrently block on multiple file
 * descriptors and receive notification when any one of them becomes ready to
 * read or write without blocking. Multiplexed I/O thus becomes the pivot
 * point for the application, designed similarly to the following activity:
 *
 * 1. Multiplexed I/O: Tell me when any of these file descriptors become
 *    ready for I/O.
 * 2. Nothing ready? Sleep until one or more file descriptors are ready.
 * 3. Woken up! What is ready?
 * 4. Handle all file descriptors ready for I/O, without blocking.
 * 5. Go back to step 1.
 */

#include <sys/select.h>
#include <sys/time.h>
#include "util.h"

int main(int argc, char *argv[]) {

	return 0;
}
