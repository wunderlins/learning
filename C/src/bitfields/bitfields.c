/**
 * Bit-Fields Example
 *
 * (c) 2014, Simon Wunderlin, <swunderlin()gmailDTcom>
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/utsname.h>
#include <errno.h>

/**
 * Declare bit-fields that can hold a date
 *
 * Format:
 *   type name : number_of_bits;
 *
 * Types:
 *   _Bool, int, signed int, unsigned int (or implementation dependent).
 */
struct Date {
	/// 0-31, 32 bits for day of the month
	unsigned int day   : 5;
	
	/// 0-15, 16 bits for month, 1 is January
	unsigned int month : 4;
	
	/// -2097152-2097151, probably more, check word size
	signed int year    : 22;
	
	/// True if daylight saving is in effect
	_Bool isDST        : 1;
};

/**
 * Main method
 */
int main(int argc, char **argv) {

	struct Date birthday = {3, 12, 1974};
	printf("%02d.%02d.%04d", birthday.day, birthday.month, birthday.year);
	
	if (birthday.isDST)
		printf("+1DST");
	printf("\n");
	
	//printf("length of birthday.day is %d\n", sizeof(birthday.day));
	printf("size of int is %lu\n", (int) CHAR_BIT * sizeof(int));
	
	// system information
	struct utsname s;
	int res = uname(&s);
	if (res != 0) {
		printf("Error running uname(), return %d, errno: %d '%s'\n", res, errno, strerror(errno));
		return 1;
	}
	
	printf("Sysinfo:\n");
	printf(" - sysname:    %s\n", s.sysname);
	printf(" - nodename:   %s\n", s.nodename);
	printf(" - release:    %s\n", s.release);
	printf(" - version:    %s\n", s.version);
	printf(" - machine:    %s\n", s.machine);
	#ifdef _GNU_SOURCE
	printf(" - domainname: %s\n", s.domainname);
	#endif
	
	fflush(stdout);

	return 0;
}
