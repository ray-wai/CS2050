//Headerfiles

//3 files, 2 header files, one main program
//for lab 14 we will submit the 2 headerfiles

//lab14.h -> header file
//lab14.c -> header file
//main.c -> testing program (will not be submitted)

//in one program, copy everything above the main program; includes, typedef, declarations (lab14.h) 
	//this is used to compile
//in another program, copy everything below the main program; function implementations (lab14.c)
	//this is used during runtime

//***********************************************************************************************************************************
//There is 1 tricky thing, the compiler doesn't know lab14.h and lab14.c are there (it doesn't know where to find the implementation)
//At the very beginning of your .c files, include your .h file
	//#include "lab14.h"
	
//BOTH IN THE FUNCTIONS FILE AND IN THE MAIN PROGRAM INCLUDE THIS HEADER FILE
//***********************************************************************************************************************************

//the <> signals the default library 
//for your own header file, put "" (it tells the compiler is it not a built in default library, so go to that location to find it)

//only include the standard libraries <stdio.h> <stdlib.h>.... in the .h file, then any file that uses the header will also have those libraries included





//how to compile it
	//gcc main.c lab14.c -Wall -Werror
//dont link .c files within other .c files; it creates lots of compiler headaches

