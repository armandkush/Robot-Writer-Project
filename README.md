# Robot-Writer-Project
## Software Project: Developing software for a writing robot

Description:

The goal of the project is to design a software that can communicate with the writing robot and print
out text from a text file of any length with a letter height of 5mm on a sheet of paper. The program
is written in C using the CodeBlocks IDE. It will use a virtual rs232 serial port to connect to the
robot/Arduino.
The software is designed to first create a buffer. It will then open the virtual rs232 port using
functions from the serial.c and rs232.c file and will wake up the robot by sending specific commands
to it and waiting for a $ sign from the robot as a signal its ready.
It will then store font data from “SingleStrokeFont.txt” text file into a structure array (struct
StorageArray fontData[]). It will then read the “SampleLines.txt” text file or any file you input into
the code by character and sequentially store into variables called int ASCII and int AValue. As a value
of ASCII is stored, a custom function called LocateASCIIinFont() will iterate through the structure
array to look for the starting point and end point of the specific ASCII character. It will then
sequentially offset the coordinates of the font data, scale down the font data by 0.278 of 5/18 to
make it 5 units and then convert the coordinates into g-codes to be sent through the RS232 port to
the robot using SendCommand(). This code will repeat until all characters in the text file has
successfully been converted and sent to robot to be printed and then the file will close. The RS232
virtual port should then close, and the program will end.


List of technologies used:
    - C (rs232 library)

Installation instructions:

1) Install C programming module
2) Install IDE (ex: Codeblocks)
3) Clone the repo



Usage instructions:

1) Replace “SingleStrokeFont.txt” with the name of the font data file you would like to use at
line 50 in main.c
2) Replace “SampleLines.txt” with the name of the text data file you would like to use at line 59 in main.c
3) Replace value of #define scale if you would like to change the size of the final print data in main.c
4) Make sure #define Serial_Mode in serial.c is uncommented.
5) Check the COM Port of robot that is connected to the computer.
6) Change #define cport_nr to the COM Port of robot connected to computer but minus 1 in main.c
7) Compile and run the code.



File structure of the project:


    ├── ...
    └── Robot-Writer-Project    # Main folder
        ├── main   # Folder containing files for debugging
        │   ├── bin 
        │   │   └── debug
        │   │       └── RobotWriter.exe # Executable to run program without IDE
        │   ├── obj
        │   │   └── debug
        │   │       ├── CustomFunctions.o # File containing objects for custom functions
        │   │       ├── main.o  # File containing objects for main
        │   │       ├── rs232.o # File containing objects for rs232
        │   │       └── serial.o # File containing objects for serial
        │   ├── CustomFunctions.c     # C file containing all custom functions and structure array to be used in the main file.
        │   ├── CustomFunctions.h     # Header file for CustomFunctions.c
        │   ├── main.c    # C file containing the main code that needs to be run.
        │   ├── RobotWriter.cbp       # Codeblocks project file
        │   ├── RobotWriter.depend      # File containing dependencies fo RobotWriter.cbp
        │   ├── RobotWriter.layout       # File containing layout file for RobotWriter.cbp
        │   ├── rs232.c       # C file containing RS232 library files
        │   ├── rs232.h       # Header file for RS232 library
        │   ├── serial.c      # C file containing code for communication between C file and robot
        │   ├── serial.h      # Header file for serial.c
        │   ├── SingleStrokeFont.txt # Text file containing font data
        │   └── test.txt       # Text file for testing functionality of program
        ├── System_Flowchart.pdf      # PDF file containing a flowchart of the program systems
        ├── System_Manual.pdf     # PDF file containing an overview of the project and the usage instructions.
        ├── LICENSE                  # File containing license information  
        └── README.md                # File containing essential information and instructions


License information:
Copyright 2021 Armand Kushairi.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
