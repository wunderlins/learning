/**
 * Bit shift example for LED matrix
 * 
 * This example shows how to store on/off states of an
 * 8*8 LED matrix in 8 8 bit int values using bit shifting.
 * 
 * Every row in our 8 int array has 8 bits which can be 0 or 1:
 * 
 *	   1 2 3 4 5 6 7 8  <-- bits per row
 * 	  +-+-+-+-+-+-+-+-+
 * 	1 | | | | l | | | | matrix[0]
 * 	  +-+-+-+-+-+-+-+-+
 * 	2 | | | | l | | | | matrix[1]
 * 	  +-+-+-+-+-+-+-+-+
 * 	3 | | | | l | | | | matrix[2]
 * 	  +-+-+-+-+-+-+-+-+
 * 	4 | | | | l | | | | matrix[3]
 * 	  +·+·+·+·+·+·+·+·+
 * 	5 | | | | l | | | | matrix[4]
 * 	  +-+-+-+-+-+-+-+-+
 * 	6 | | | | l | | | | matrix[5]
 * 	  +-+-+-+-+-+-+-+-+
 * 	7 | | | | l | | | | matrix[6]
 * 	  +-+-+-+-+-+-+-+-+
 * 	8 | | | | l | | | | matrix[7]
 * 	  +-+-+-+-+-+-+-+-+
 *
 * Compile:
 * me@myrig$ gcc -std=c99 -o bits bits.c
 *
 * See:
 * http://en.wikipedia.org/wiki/Bitwise_operations_in_C
 * 
 * Author:
 * 2013, Simon Wunderlin, <swunderlin@gmail.com>
 * 
 */

#include <stdio.h>    // used with printf
#include <inttypes.h> // required for uintN_t with gcc
#include <stdbool.h>

// declarations
void print_matrix(char*);
bool set_point(uint8_t x, uint8_t y, bool state, uint8_t *matrix);

// this is our matrix array. It contians 8 integer with 8 bits.
// we do initialize every int to 0 which means all LEDs are off.
uint8_t matrix[8] = {1, 0, 0, 0, 0, 0, 0, 0};

int main(int argc, char* argv) {
	
	// let's look at the initial state of our matrix, the first 
	// LED on the 2nd row should be on, evreything else should be off
	//
	// check the print_matrix function's comments carefully for a first 
	// introduction on bit shifting
	print_matrix("intial state");
	
	// check if bit 1 in row 1 is set:
	printf("bit 1,1: %d\n", (1<<0 & matrix[0]));
	matrix[0] = 0;
	printf("bit 1,1: %d\n\n", (1<<0 & matrix[0]));
	
	// set bit 4 in row 0
	matrix[0] = 8; // directly, this wil lreset all other bits to 8
	matrix[0] = matrix[0] | (1<<3); // only set bit 4, don't touch the rest
	
	print_matrix("set bit 4 in row 0");
	
	// let's set a couple of other bits in row 0
	matrix[0] = matrix[0] | (1<<0);
	matrix[0] = matrix[0] | (1<<1);
	matrix[0] = matrix[0] | (1<<2);
		
	print_matrix("set bit 1,2,3 in row 0");
	
	// now make sure that bit 3 is 0. if it is 0 leave it zero, else set it to 0
	//matrix[0] = ((1<<2 & matrix[0]) != 0) ? (~(1<<2) & matrix[0]) : matrix[0];
	matrix[0] = (~(1<<2) & matrix[0]);
	
	// the above line is very confusing and this is where I first hit a wall 
	// with bitwise operators
	// 
	// to make sure a bit is not set, the easiest way is to compare with 
	// binary AND (~) against a reversed mask.
	//
	// let's say we want to make sure bit 3 is unset. Create a bitmask that has
	// bit 3 set to 1:
	// (1<<2)  == b00100000
	//
	// now reverse the mask:
	// ~(1<<2) == b11011111
	//
	// in this form, it is now very easy to use binary AND, the result will be 
	// that bit 3 is alwas zero, because it is zero in the mask 
	// and 1 & 0 is 0, 0 & 0 is 0 (the only 2 possibilites):
	// 
	//   11110000   matrix[0]
	// & 11011111   our inverted mask
	//   ........
	//   11010000   result
	
	print_matrix("make sure that bit 3 is 0");
	
	// making it easier, with the above knowledge we can now create a function
	// that will manipulate one bit in our matrix. see comments in the function 
	// implementation for more etails.
	
	// set bit 4 in row 4
	set_point(3, 3, true, &matrix); // remember, we start to count at 0
	print_matrix("4, 4 set");
	
	set_point(3, 3, false, &matrix); // remember, we start to count at 0
	print_matrix("4, 4 unset");
	
	// set 1 row high
	matrix[0] = 255;
	matrix[1] = 255;
	print_matrix("row 1 and 2 high, ya mann");
	
	// set 1 row low
	matrix[0] = 0;
	print_matrix("row 1 low, hangover");
	
	// set 1 col high
	for (uint8_t r=0; r<8; r++)
		set_point(7, r, true, &matrix); // remember, we start to count at 0
	
	print_matrix("col 8 high");
	
	return 0;
}

/**
 * Print LED matrix
 *
 * A simple method to print an 8*8 LED matrix on a terminal. On is 
 * represented by 1, off by 0.
 *
 */
void print_matrix(char* comment) {
	
	printf("%s\n\n", comment);
	printf("   0 1 2 3 4 5 6 7\n");
	printf("   ---------------\n");
	
	// loop over all rows, from top to bottom, used
	// use option -std=c99 or -std=gnu99 to compile with gcc
	for (uint8_t r=0; r<8; r++) {
		
		printf("%d: ", r);
		
		// now loop bit by bit over this integer, find out if bit is high or low.
		for (uint8_t c=0; c<8; c++) {
			
			/**
			 * let's find the bits in one row.
			 *  
			 * the row we are checking is matrix[r], where 
			 * r is the row index, 0-7 (real programmers start counting at 0 ;)
			 * 
			 * before we can compare a single bit in a row, we need to set 
			 * another int's bit we want to compare.
			 * 
			 * (1<<2) will do the following, the value 1 represented as 
			 * bits in a 8 bit integer looks like this:
			 * 00000001. We use bit shift to shift it 2 positions to the left.
			 * (1<<2) will result in:
			 * 00000100
			 * 
			 * The bitwise AND operator (&) is then used to compare the two bits.
			 * let's say matrix[r] is 1, this would be
			 * 00000001 in binary.
			 * let's assume c is the 3rd bit (1<<2) which is 00000100 in binary,
			 * then the comparision works like this:
			 *
			 *   00000001   1
			 * & 00000100   4
			 *   --------
			 *   00000000   0
			 *
			 * we don't have any common bits.
			 *
			 * let's compare (int) 3 to (int) 2 in binary
			 *
			 *   00000011   3
			 * & 00000010   2
			 *   --------
			 *   00000010   2
			 *
			 * So if bit 1 is set in both bytes, we get a positive result.
			 */
			printf("%d ", (bool) (1<<c & matrix[r]));
		}
		
		printf("\n");
	}
	printf("\n");
}

/**
 * set a bit in an 8x8 matrix. matrix is an array of 8 8bit integer passed 
 * by reference. x axis is horizontal (left to right), y axis is vertical 
 * (top to bottom).
 */
bool set_point(uint8_t x, uint8_t y, bool state, uint8_t *matrix) {
	// bounds checking
	if (x>7) return false;
	if (y>7) return false;
	
	if (state) // set a bit
		matrix[y] = matrix[y] | (1<<x);
	else // unset a bit
		matrix[y] = (~(1<<x) & matrix[y]);
	
	return true;
}

