//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const string &a_symbol, int a_loc );
    	a_symbol	-> The name of the symbol to be added to the symbol table.
    	a_loc		-> the location to be associated with the symbol.

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/
void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st -> second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
} /* void SymbolTable::AddSymbol( const string &a_symbol, int a_loc ) */

/*
NAME

    DisplaySymbolTable - Prints out the symbol table for the user to view.

SYNOPSIS

    void DisplaySymbolTable( );
       
DESCRIPTION

    This function will display the symbol table.

*/
void SymbolTable::DisplaySymbolTable()
{
    map<string, int>::iterator it;
    int count = 0;

    cout << "Symbol Table:" << endl;
    cout << "Symbol# \t Symbol    Location" << endl;

    for (it = m_symbolTable.begin(); it != m_symbolTable.end(); it++)
    {
       cout << left << setw(10) << count << right << setw(10) << it->first
            << right << setw(10) << it->second << endl;       
        count++;
    }
} /* void SymbolTable::DisplaySymbolTable() */

/*
NAME

    LookupSymbol - This checks to see if the symbol.

SYNOPSIS

    bool LookupSymbol( const string &a_symbol, int a_loc );
        a_symbol	-> The name of the symbol that the function will look for.
        a_loc		-> If the symbol is found the location will be updated.

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.

RETURNS

    True if the symbol exists, false otherwise.
*/
bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc)
{
    // Iterates through the symbol table to check for a match
    if (m_symbolTable.find(a_symbol) == m_symbolTable.end())
    {

        return false;
    }
    a_loc = m_symbolTable[a_symbol];
    return true;
   
} /* bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) */
