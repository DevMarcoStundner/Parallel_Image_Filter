/*
* Author: Stundner Marco
* Filename: main.c
* Task: Parallel Image Filter
* Date 20.04.22
*/


#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <malloc.h>
#include "readimg.h"

#define len 80
#define MSG 4

struct pixel 
{
	char r;
	char g;
	char b;
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


void print_help (void);

int main(int argc, char *argv[]) 
{
    int opt;
	int x, y;
	int ft;
	int pid, ppid;
	long int qP2C, qC2P;
	char *input_img;
	char ppm6Id[len];
	char comment[len];
	FILE *pImg1;

	/* const char *iarg = NULL;
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
			//parg = optarg;
			break;
		case 'k':
		//	karg = optarg;
			break;
        case 'i':
		//	iarg = optarg;
			break;
        case 'o':
		//	oarg = optarg;
			break;
		case 'h': 	
			print_help();
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
	} */ 
	
	pImg1 = fopen("img1.ppm","r");
	if (pImg1 == NULL)
	{
		printf("fopen error\n");
		exit(EXIT_FAILURE);
	}
	fscanf(pImg1, "%s\n", ppm6Id);
	int c = fgetc(pImg1);
	if (c != '#')
	{
		ungetc(c, pImg1);
	}
	else
	{
		fgets(comment, len, pImg1);
	}
	fscanf(pImg1, "%d %d", &x, &y);
	fscanf(pImg1, "%d", &ft);
	input_img = (char *) calloc (x*y*3, sizeof (char));
	if (input_img == NULL)
	{
		printf ("Memory not allocated");
		exit (EXIT_FAILURE);
	}
	read_ppm (pImg1, input_img, x, y);
	fclose(pImg1);

	//Queue Parent to Child
	qP2C = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
	if(qP2C == -1)
	{
		printf("Couldn't create Queue Child -> Parent\n");
		exit (EXIT_FAILURE);
	}

	//Queue Child to Parent
	qC2P = msgget(IPC_PRIVATE,  IPC_CREAT | 0666);
	if(qC2P == -1)
	{
		printf("Couldn't create Queue Child -> Parent\n");
		exit (EXIT_FAILURE);
	}


	free(input_img);
	return 0;
}

void print_help (void)
{
	printf ("\nPI_Filter: prog.exe [-p NUMBER_OF_PROCESSES] -k KERNEL -i INPUT_IMAGE -o OUTPUT_IMAGE [-h]\n");
	exit (EXIT_FAILURE);
}