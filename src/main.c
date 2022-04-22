/*
* Author: Stundner Marco
* Filename: main.c
* Task: Parallel Image Filter
* Date 20.04.22
*/


#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include "readimg.h"

struct pixel 
{
	int r;
	int g;
	int b;
};

struct workPackage {
    struct pixel pixels[3][3];  // pixels to multiply with the kernel
    unsigned int pixel_index;   // linear index of the pixel
                                // (i.e., y*width+x) to be processed
                                // (for identifying the result)
};

struct resultPackage {
    struct pixel pixel;         // result of matrix multiplication of kernel and pixels from workPackage
    unsigned int pixel_index;   // linear index of the pixel
                                // (i.e., y*width+x) to be processed
                                // (for identifying the result)
};

/*
*MSG queue erstellen
*
*/

void print_help (void);

int main(int argc, char **argv) 
{
    int opt;
	const char *iarg = NULL;
	const char *oarg = NULL;
    const char *karg = NULL;
	const char *parg = NULL;

	if (argc == 1) {
		fprintf (stderr, "This program needs arguments....\n\n");
		print_help();
	}

	while ( (opt = getopt (argc, argv, "p:k:i:o:h")) != -1) {
		switch (opt) {
		case 'p':
			parg = optarg;
			break;
		case 'k':
			karg = optarg;
			break;
        case 'i':
			iarg = optarg;
			break;
        case 'o':
			oarg = optarg;
			break;
		case 'h': 
			write_ppm();
			//print_help();
			break;
		case ':':
			fprintf (stderr, "Option requires an argument.\n");
			print_help ();
			break;
		case '?':
			fprintf (stderr, "Unknown option character %c.\n", optopt);
			print_help ();
		}
	}
	for (; optind < argc; optind++)
	{
		printf ("Positional argument %d: %s\n", optind, argv[optind]);
	}
	
	return 0;
}

void print_help (void)
{
	printf ("\nPI_Filter: prog.exe [-p NUMBER_OF_PROCESSES] -k KERNEL -i INPUT_IMAGE -o OUTPUT_IMAGE [-h]\n");
	exit (EXIT_FAILURE);
}