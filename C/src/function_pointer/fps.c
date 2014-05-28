/**
 * Function Pointer Example
 *
 * (c) 2014, Simon Wudnerlin, <swunderlin()gmailDTcom>
 */

//#define _USE_MATH_DEFINES
//#define _BSD_SOURCE

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

typedef struct sphere {
	int diameter;
	double (*volume)(int);
} sphere_t;

double volume(int);
sphere_t get_sphere(int);
double sphere_volume(sphere_t*);

/**
 * Calculate volume for a sphere
 *
 * Expects parameter 1 to be the diameter.
 */
double volume(int diameter) {
	return (double) ((4/3) * M_PI * pow((diameter/2), 3));
}

/**
 * Constructor for sphere_t
 *
 * Allocates memory and initializes a sphere_t object.
 */
sphere_t get_sphere(int r) {
	sphere_t s;
	s.diameter = r;
	s.volume = volume;
	
	return s;
}

/**
 * Compute a sphere's volume
 *
 * The sphere_t provides a method sphere_t.volume(). Use the diameter and
 * this method to calculate the volume of a sphere.
 */
double sphere_volume(sphere_t *s) {
	return s->volume(s->diameter);
}

/**
 * Main method
 */
int main(int argc, char **argv) {
	
	// create a sphere object
	sphere_t s = get_sphere(3);
	
	// calculate the spere's volume
	double res = sphere_volume(&s);
	printf("%f\n", res);
	
	return 0;
}

