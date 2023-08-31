
// Thomas McMahon
// Implementation of the Errors class

#include "stdafx.h"

#include "Errors.h"

//Initializes the m_ErrorMsgs vector to store and record error messages
vector<string> Errors::m_ErrorMsgs;

/**/
/*
void Errors::InitErrorReporting()

NAME

	void Errors::InitErrorReporting() - clears the error message vector

SYNOPSIS

	void Errors::InitErrorReporting()

DESCRIPTION

	This function removes all errors that were previously stored in the vector

RETURNS

	Void

AUTHOR

	Thomas McMahon

DATE

	8:52 PM 5/7/2022

*/
/**/
void Errors::InitErrorReporting() 
{
	//Clears error messages to start with nothing stored
	Errors::m_ErrorMsgs.clear();
} /* void Errors::InitErrorReporting() */


/**/
/*
void Errors::RecordError(string a_emsg)

NAME

	void Errors::RecordError(string a_emsg) - Stores the error messages in a vector

SYNOPSIS

	void Errors::RecordError(string a_emsg)
	a_emsg --> string error that is stored during the program

DESCRIPTION

	This function displays the errors that were stored in the first pass

RETURNS

	Void

AUTHOR

	Thomas McMahon

DATE

	8:52 PM 5/7/2022

*/
/**/
void Errors::RecordError(string a_emsg)
{
	Errors::m_ErrorMsgs.push_back(a_emsg);
} /* void Errors::RecordError(string a_emsg) */

/**/
/*
void Errors::DisplayErrors()

NAME

	void Errors::DisplayErrors() - Displays the errors stored during runtime

SYNOPSIS

	void Errors::DisplayErrors()

DESCRIPTION

	This function displays the errors that were stored during runtime

RETURNS

	Void

AUTHOR

	Thomas McMahon

DATE

	8:52 PM 5/7/2022

*/
/**/
void Errors::DisplayErrors() 
{
	// Iterates through the error message 
	// vector to display any errors held
	for (int msgNumber = 0; msgNumber < m_ErrorMsgs.size(); msgNumber++)
	{
		// Displays the stored error messages
		cout << m_ErrorMsgs[msgNumber] << endl;
	}
	// Clears the error vector
	m_ErrorMsgs.clear();
} /* void Errors::DisplayErrors() */

/**/
/*
bool Errors::isEmptyError()

NAME

	bool Errors::isEmptyError

SYNOPSIS

	bool Errors::isEmptyError()

DESCRIPTION

	This function displays the errors that were stored in the first pass

RETURNS

	Returns true if there are no errors present, otherwise returns false

AUTHOR

	Thomas McMahon

DATE

	8:52 PM 5/7/2022

*/
/**/
bool Errors::isEmptyError()
{
	// Returns a boolean of whether or not the vector is empty
	return m_ErrorMsgs.empty();
} /* bool Errors::isEmptyError() */