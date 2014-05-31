/**
 * Nested Strcutures Example
 *
 * (c) 2014, Simon Wunderlin, <swudnerlin()gmailDTcom>
 */

#include <stdio.h>
#include <math.h>

typedef struct date {
	int day, month, year; 
} date_t;

typedef struct package {
	
	int version_major, version_minor, version_patchlevel;
	
	struct {
		char* name;
		char* description;
	} meta;
	
	date_t created;
	
} package_t;

/**
 * Main method
 */
int main(int argc, char **argv) {
	
	package_t p = {0, 0, 1, {"test package", "blah blah blah ..."}, {28, 5, 2014}};
	printf("Name:        %s\n", p.meta.name);
	printf("Version:     %d.%d.%d\n", p.version_major, p.version_minor, p.version_patchlevel);
	printf("Description: %s\n", p.meta.description);
	printf("Created:     %02d.%02d.%04d\n", p.created.day, p.created.month, p.created.year);
	
	return 0;
}
