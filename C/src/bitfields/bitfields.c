/**
 * Bit-Fields Example
 *
 * (c) 2014, Simon Wunderlin, <swudnerlin()gmailDTcom>
 */

#include <stdio.h>
/**
 * Declare a bit-field that can hold a date
 */
struct Date {
	unsigned int day   : 5;  // 0-31, 32 bits for day of the month
	unsigned int month : 4;  // 0-15, 16 bits for month, 1 is January
	signed int year    : 22; // -2097152-2097151, probably more, check word size
	_Bool isDST        : 1;  // True if daylight saving is in effect
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
	fflush(stdout);

	return 0;
}
