//#define _USE_MATH_DEFINES
//#define _BSD_SOURCE

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

typedef struct sphere {
	int diameter;
	void (*volume)(int);
} sphere;

void volume(int);
void volume(int r) {
	double volume = (4/3) * M_PI * pow(r, 3);
	printf( "volume: %f\n", volume);
}

int main(int argc, char **argv) {
	
	// create a sphere
	sphere s;
	s.diameter = 3;
	
	// assign pointer to a function
	s.volume = &volume;
	
	// run referenced function
	s.volume(s.diameter);
	
	return 0;
}

