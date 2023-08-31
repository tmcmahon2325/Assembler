/*
 * Thomas McMahon
 * Assembler main program.
 */
#include "stdafx.h"      
#include <stdio.h>

#include "Assembler.h"

int main( int argc, char *argv[] )
{   //Calls the command line arguments
    Assembler assem( argc, argv );

    // Establish the location of the labels:
    assem.PassI( );

    // Display the symbol table.
    assem.DisplaySymbolTable();

    // Output the translation.
    assem.PassII( );
    
    // Run the emulator on the translation of the assembler language program that was generated in Pass II.
    assem.RunProgramInEmulator();
   
    // Terminate indicating all is well.  If there is an unrecoverable error, the 
    // program will terminate at the point that it occurred with an exit(1) call.
    return 0;
} 