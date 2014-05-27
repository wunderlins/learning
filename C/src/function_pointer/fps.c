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

double volume(int diameter) {
	return (double) ((4/3) * M_PI * pow((diameter/2), 3));
}

sphere_t get_sphere(int r) {
	sphere_t s;
	s.diameter = r;
	s.volume = volume;
	
	return s;
}

double sphere_volume(sphere_t *s) {
	return s->volume(s->diameter);
}

int main(int argc, char **argv) {
	
	// create a sphere
	sphere_t s = get_sphere(3);
	
	double res = sphere_volume(&s);
	printf("%f\n", res);
	
	return 0;
}

