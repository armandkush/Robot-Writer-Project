#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
#include "rs232.h"
#include "serial.h"
#include "CustomFunctions.h"

#define bdrate 115200               /* 115200 baud */
#define MAX_ARRAY_SIZE 1028
#define Scale 0.278

void SendCommands (char *buffer );

int main()
{

    //char mode[]= {'8','N','1',0};
    char buffer[100];

    // If we cannot open the port then give up immediately
    if ( CanRS232PortBeOpened() == -1 )
    {
        printf ("\nUnable to open the COM port (specified in serial.h) ");
        exit (0);
    }

    // Time to wake up the robot
    printf ("\nAbout to wake up the robot\n");

    // We do this by sending a new-line
    sprintf (buffer, "\n");
     // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    Sleep(100);

    // This is a special case - we wait  until we see a dollar ($)
    WaitForDollar();

    printf ("\nThe robot is now ready to draw\n");

        //These commands get the robot into 'ready to draw mode' and need to be sent before any writing commands
    sprintf (buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    char *fileNameFont = "SingleStrokeFont.txt";
    StoreFontData(fileNameFont); //Function to read and store font data into structure array B.
    int i,S,F,AValue;
    float XPostScale, YPostScale;

    FILE *fileToBeRead;
    int ASCII;

    // opening file.
    fileToBeRead = fopen("SampleLines.txt", "r");

    // error checking.
    if (fileToBeRead == NULL)
/*1(1)*/       {
/*ex, layer(n)*/ printf("File is not available \n");
               } /*1*/
    else
/*1(2)*/{
    //4 Decision between newline, return carriage, or starting print
    int xmulti = 0; // counter for offset per letter when printing
    int ymulti = 0;
    while ((ASCII = fgetc(fileToBeRead)) != EOF)  //read text file until eof
/*2(1)*/   {
        //printf("%c", ASCII); for diagnostic purpose (checking correct ASCII file is chosen)
        AValue = ASCII;
        if (AValue == 10)//newline
/*3(1)*/  {
            xmulti=0;//reset x offset for subsequent letters to 0 (here for redundancies sake)
            ymulti++;
           }/*3(1)*/
       else if (AValue == 13)//return carriage
  /*3(2)*/     {
        fontData[i].num1 = 0;
        xmulti=0; //reset x offset for subsequent letters to 0
       }/*3(2)*/
       else if ( LocateASCIIinFont ( fontData, AValue, &S, &F ) == 0 )//find location of font data to print
/*3(3)*/ {
        //printf ("Data starts on line %d and ends on line %d", S, F);
        //printf ("\n");
        int i, Pvalue, PenCheck;
        float XToPrint, YToPrint;
        for ( i  = S ; i < F ; i++)//iterating through font data to print out.
/*4(1)*/  {
        //printf ("Line:%d   a:%d  b:%d  c:%d\n", i, fontData[i].num1, fontData[i].num2, fontData[i].num3 );
        //printf ("\n");
        Pvalue = fontData[i].num3;
        PenCheck = fontData[i-1].num3;
        //Offset process
        XToPrint = fontData[i].num1+(18*xmulti);
        YToPrint = fontData[i].num2-(28*ymulti);
        //Offset completed.
        XPostScale = ScaleB4Print(XToPrint); //Scaling to 5/18 or 0.278 for printing.
        YPostScale = ScaleB4Print(YToPrint);

        //printf ("G0 X%.2f Y%.2f\n",XPostScale, YPostScale); //for diagnostic purpose (checking if scale and offset work)
        //printf ("\n");
           if (Pvalue == 0 && PenCheck != 0 )
 /*5(1)*/        {
               //printf ("S0\n"); for diagnostic purposes
               //printf ("G0 X%.2f Y%.2f\n",XPostScale, YPostScale);
               sprintf (buffer, "S0\n");
               sprintf (buffer, "G0 X%.2f Y%.2f\n",XPostScale,YPostScale);
               SendCommands(buffer);
                 } /*5(1)*/
               else if(Pvalue == 0 && PenCheck == 0)
 /*5(2)*/          {
              //printf ("G0 X%.2f Y%.2f\n",XPostScale, YPostScale);for diagnostic purposes
                sprintf (buffer, "G0 X%.2f Y%.2f\n",XPostScale,YPostScale);
                SendCommands(buffer);
                } /*5(2)*/

              else if (Pvalue != 0 && PenCheck == 0)
/*5(3)*/        {
              //printf ("S1000\n");
              //printf ("G1 X%.2f Y%.2f\n",XPostScale, YPostScale);for diagnostic purposes
                sprintf (buffer, "S1000\n");
                sprintf (buffer, "G0 X%.2f Y%.2f\n",XPostScale,YPostScale);
                SendCommands(buffer);
                }/*5(3)*/
           else
/*5(4)*/          {
                //printf ("G1 X%.2f Y%.2f\n",XPostScale, YPostScale);for diagnostic purposes
                sprintf (buffer, "G1 X%.2f Y%.2f\n",XPostScale,YPostScale);
                SendCommands(buffer);
               }/*5(4)*/
              }/*4(1)*/

        xmulti++;  //count up after printing one letter
      } /*3(3)*/

    else //error checking for non valid ASCII values.
    {
        printf ("\nThe character could not be found");
    }

        }/*2(1)*/
    //5
    fclose(fileToBeRead);

    return 0;

}

    // Before we exit the program we need to close the COM port
    CloseRS232Port();
    printf("Com port now closed\n");

    return (0);
}

// Send the data to the robot - note in 'PC' mode you need to hit space twice
// as the dummy 'WaitForReply' has a getch() within the function.
void SendCommands (char *buffer )
{
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    WaitForReply();
    //WaitForReply();
    Sleep(100); // Can omit this when using the writing robot but has minimal effect
    // getch(); // Omit this once basic testing with emulator has taken place
}

