//
//    Thomas McMahon
// 
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
    static void InitErrorReporting( );

    // Records an error message.
    static void RecordError( string a_emsg );

    // Displays the collected error message.
    static void DisplayErrors( );

    //Checks for vector empty error
    static bool isEmptyError( );

private:

    static vector<string> m_ErrorMsgs;  
};
#endif