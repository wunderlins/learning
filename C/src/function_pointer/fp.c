#include <stdio.h>

void void_int(int x);
void void_int(int x) {
	printf( "void_int: %d\n", x);
}

int main(int argc, char **argv) {
	printf("Hello world\n");
	
	// declare a function pointer
	void (*by_ref_void_int)(int);
	
	// assign pointer to a function
	by_ref_void_int = &void_int;
	
	// run referenced function
	by_ref_void_int(2);
	
	return 0;
}
