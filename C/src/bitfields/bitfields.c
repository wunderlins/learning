/**
 * Bit-Fields Example
 *
 * (c) 2014, Simon Wunderlin, <swunderlin()gmailDTcom>
 */

#include <stdio.h>

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
	fflush(stdout);

	return 0;
}
