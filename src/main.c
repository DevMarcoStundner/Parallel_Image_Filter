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

struct msg {
  int id;
  struct pixel px[MSG];
};

struct DAT {
  long mtype;
  struct msg m;
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

	ppid = getpid();
	pid = 1;
	for (int j = 1; j <= atoi (argv[1]); j++) {
    if (pid > 0) {
      pid = fork();
      // -----------------------------------------------------------------------
      // ---------------------------------------------------------------- CHILDs
      // 
      if (pid == 0) {
        // receive data from PARENT
        struct DAT crcvDat;
        msgrcv (qP2C, &crcvDat, sizeof (struct DAT), j, 0); //takes msg from the queue

		/*
			Pixel einlesen und mit Filter mul
		*/


        msgsnd (qC2P, &c2pd, sizeof (struct DAT), 0);
      }
    }
  }
  // ---------------------------------------------------------------------------
  // -------------------------------------------------------------------- PARENT
  //
  if (getpid() == ppid) {
    struct DAT p2cd;
    struct pixel px[x*y]; 
	int m = 0;

	for(int i = 0; i <= x*y; i++)
	{
		px[i].r = input_img[m];
		m++;
		px[i].g = input_img[m];
		m++;
		px[i].b = input_img[m];
		m++;
	}






    for (int k = 1; k <= atoi (argv[1]); k++) {
      p2cd.mtype = k;
      p2cd.m.px[k-1].r = px[k-1].r;
      p2cd.m.px[k-1].g = px[k-1].g;
      p2cd.m.px[k-1].b = px[k-1].b;

      // send the msg
      msgsnd (qP2C, &p2cd, sizeof (struct DAT), 0);
    }

    printf ("Go\n");

    for (int k = 1; k <= atoi (argv[1]); k++) {
      // receive a reply
      struct DAT prcvDat;
      msgrcv (qC2P, &prcvDat, sizeof (struct DAT), k, 0);
      // output the received answer
#if 1
      printf ("Child %ld to Parent: %d %d %d\n", prcvDat.mtype, prcvDat.m.px[k].r,  prcvDat.m.px[k].g,  prcvDat.m.px[k].b);
#endif
    }
    // wait for child process to terminate
    if ( (waitpid (-1, NULL, 0)) < 0) {
      perror ("waitpid");
      exit (EXIT_FAILURE);
    }
    // remove the message queues
    msgctl (qP2C, IPC_RMID, NULL);
    msgctl (qC2P, IPC_RMID, NULL);
  }


	free(input_img);
	return 0;
}

void print_help (void)
{
	printf ("\nPI_Filter: prog.exe [-p NUMBER_OF_PROCESSES] -k KERNEL -i INPUT_IMAGE -o OUTPUT_IMAGE [-h]\n");
	exit (EXIT_FAILURE);
}