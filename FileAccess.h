//  Thomas McMahon
//	File access to source file.

// This is the way that multiple inclusions are defended against often used in UNIX
#ifndef _FILEACCESS_H  
// We use pragmas in Visual Studio and g++.  See other include files
#define _FILEACCESS_H  

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:

    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

    // Get the next line from the source file.  Returns true if there was one.
    bool GetNextLine( string &a_line );

    // Put the file pointer back to the beginning of the file.
    void rewind( );

private:

    // Source file object.
    ifstream m_sfile;		
};
#endif

