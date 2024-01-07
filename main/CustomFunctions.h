#include <stdio.h>
#include <string.h>


#ifndef CUSTOMFUNCTIONS_H_INCLUDED
#define CUSTOMFUNCTIONS_H_INCLUDED

#define MAX_ARRAY_SIZE 1028
#define Scale 0.278

typedef struct
{
    int num1;
    int num2;
    int num3;
}StorageArray;   //structure to contain 3 data


StorageArray fontData[MAX_ARRAY_SIZE]; //structure array to store font data


void StoreFontData (char *fileName);  //function to store font data into structure array
float ScaleB4Print(float RawXY); //function to scale g code by 5/18 or 0.278 before printing.
int LocateASCIIinFont(StorageArray fontData[], int ASCII, int *Start, int *Finish ); //function to locate start and end point of specific ASCII characters in structure array containing font data.

#endif // CUSTOMFUNCTIONS_H_INCLUDED
