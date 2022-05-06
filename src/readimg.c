#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readimg.h"


void write_ppm(char *p)
{

    char head[] = {
        'P','6','\n',
        '3',' ','3','\n',
        '2','5','5','\n'   
    };
    /* {
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
        
    }; */

    FILE *pImg = fopen("img2.ppm","wb");
    //size_t r2 = fwrite(head,sizeof(head[0]),sizeof(head),pImg);
    size_t r1 = fwrite(p,sizeof(p[0]),sizeof(p),pImg);
   // printf("\nwrote %zu elements",r1);
   // printf("\nwrote %zu elements of Head",r2);
    fclose(pImg);
}

void read_ppm(char *p)
{   
    
    char head[] = {
        'P','6','\n',
        '3',' ','3','\n',
        '2','5','5','\n'   
    };
    int end = 0;
    int count = 0;
    FILE *pImg = fopen("img1.ppm","r");
    FILE *pImg2 = fopen("img2.ppm","wb");
    //fwrite(head,sizeof(head[0]),sizeof(head),pImg2);
    //while (fgets(p,sizeof(p),pImg) != NULL)
    while(end == 0)
    {
        count = fread(p, sizeof(char), 38, pImg);
        if (count == 38)
        {
            end = 1;
        }   
    }
    for(int i = 0; i<=sizeof(p); i++)
    {
        printf("%x\n",p[i]);
    }
    size_t r1 = fwrite(p,sizeof(char),sizeof(p),pImg2);

    fclose(pImg);
    fclose(pImg2);

}