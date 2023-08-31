//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/**/
/*
FileAccess::FileAccess() FileAccess::FileAccess()

NAME

    FileAccess::FileAccess - Opens the assembly program file

SYNOPSIS

    FileAccess::FileAccess(int argc, char *argv[]);
    int argc -> the number of command lines input
    char *argv[] -> an array of file names

DESCRIPTION

    This constructor takes in a command line argument and opens
    the file to an assembly program.

RETURNS

    Nothing

AUTHOR

    Thomas McMahon

DATE

    8:52 PM 5/7/2022

*/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
} /* FileAccess::FileAccess( int argc, char *argv[] ) */

/*
NAME
   
    FileAccess::~FileAccess(); - closes the assembly program

SYNOPSIS
   
   void FileAccess::~FileAccess();

DESCRIPTION

    The destructor will close the assembly file once the program completes

*/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
} /* FileAccess::~FileAccess( ) */

/*

NAME

    bool FileAccess::GetNextLine - Retrieves the next line from the input file

SYNOPSIS

     bool FileAccess::GetNextLine (string &a_line)
        a_line -> this stores the next instruction

DESCRIPTION

    This function checks to see if the user is at the end of the file.
    If we are not the next line is passed into the parameter and the 
    function returns successfully.

RETURNS

    A boolean on whether or not there was another line.

*/
bool FileAccess::GetNextLine( string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
} /* bool FileAccess::GetNextLine( string &a_line ) */

/*
NAME
    
    FileAccess::rewind - restarts the program file

SYNOPSIS

    void FileAccess::rewind();

DESCRIPTION

    This function reinstates the original file

*/

void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
} /* void FileAccess::rewind( ) */
    
