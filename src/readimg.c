#include <stdio.h>
#include "readimg.h"


void write_ppm(void)
{
    char data[] = 
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

    int size = sizeof(data)/sizeof(data[0]);

    FILE *pImg = fopen("img1.ppm","wb");
    fwrite(data,1,size,pImg);
    fclose(pImg);
}