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
#include <malloc.h>
#include "readimg.h"


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

int main(int argc, char **argv) 
{
    int opt;
	char *input_img = (char *) calloc(38,sizeof(char));
	if(input_img == NULL)
	{
		printf("Memory not allocated");
		exit(EXIT_FAILURE);
	}
	/* printf("input_img: %zu\n",sizeof(input_img));
	printf("char: %zu\n",sizeof(char)); */

	/* const char *iarg = NULL;
	const char *oarg = NULL;
    const char *karg = NULL;
	const char *parg = NULL; */

	/* if (argc == 1) {
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
			/* char ppmdata[] =
			{
				'P','6','\n',
				'3',' ','3','\n',
				'2','5','5','\n',
				255,0,0,     //rot
				255,128,0,   //orange
				255,255,0,   //gelb
				128,255,0,   //gruen
				0,255,255,   //tuerkis
				0,0,255,     //blau 
				255,0,0,     //rot
				255,128,0,   //orange
				255,255,0,   //gelb
  			};
			int size = sizeof(ppmdata)/sizeof(ppmdata[0]);
			FILE *pImg = fopen("img1.ppm","wb");
			size_t r1 = fwrite(ppmdata,1,size,pImg);
			//printf("\nwrote %zu elements",r1);
			fclose(pImg); */

			/*
				Bei Vortschritt mal auf git hochladen

			*/

			read_ppm(input_img);
			/* if(strcmp(ppmdata,input_img) != 0)
			{
				printf("Strings are not same size\n");
			} 
			write_ppm(input_img); 
			
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
	} */
	


	free(input_img);
	return 0;
}

void print_help (void)
{
	printf ("\nPI_Filter: prog.exe [-p NUMBER_OF_PROCESSES] -k KERNEL -i INPUT_IMAGE -o OUTPUT_IMAGE [-h]\n");
	exit (EXIT_FAILURE);
}