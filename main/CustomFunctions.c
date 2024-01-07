#include <stdio.h>
#include <stdlib.h>

#include "CustomFunctions.h"



StorageArray fontData[MAX_ARRAY_SIZE];

float ScaleB4Print(float RawXY)
{
 float NewXY = (RawXY*Scale);
 return NewXY;
}

int LocateASCIIinFont(StorageArray fontData[], int ASCII, int *Start, int *Finish )
{
    int j;
    for ( j  = 0 ; j < MAX_ARRAY_SIZE ; j++)
    {
        if ( ( fontData[j].num1 == 999 ) && ( fontData[j].num2 == ASCII) )
        {
            *Start = j+1;
            *Finish = *Start + fontData[j].num3;
            return (0);

        }
    }
    // If we got here, we did not find the letter
    *Start = -1;
    *Finish = -1;
    return (-1);
}

void StoreFontData (char *fileName)
{
    FILE *filePtr = NULL;
    int  i = 0;

    if ((filePtr = fopen(fileName, "r")) == NULL)
    {
        printf("Error : Unable to open %s for reading\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(filePtr, "%d%d%d", &fontData[i].num1, &fontData[i].num2, &fontData[i].num3) != EOF)
    {
        i++;
    }

    fclose(filePtr);
return 0;
}


