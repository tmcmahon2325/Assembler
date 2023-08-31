// Thomas McMahon
// Implementation of the emulator class

#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"


/*
NAME

	bool emulator::InsertMemory

Synopsis

	bool emulator::InsertMemory() 

DESCRIPTION

	This function inserts the memory to the emulator
*/
bool emulator::insertMemory(int a_location, long long a_contents)
{
	if (a_location >= 0 && a_location < MEMSZ)
	{
		m_memory[a_location] = a_contents;
		return true;
	}
	else
	{
		Errors::RecordError("Location is not valid");
		return false;
	}
} /* bool emulator::insertMemory(int a_location, long long a_contents)*/

/*
NAME

	runProgram() - Runs the emulator program.

SYNOPSIS

	bool emulator::runProgram( );

DESCRIPTION

	This function emulates over the program to translate results.

RETURNS

	A boolean on whether or not the program executed

*/
bool emulator::runProgram()
{
	int loc = 100;
	string opCode = "";
	string memloc = "";
	cout << "Results from emulation: " << endl;
		
	while (true) 
	{
		//Local variables to determine locations of input
		int contents = m_memory[loc];
		int opCode = contents / 10000000;
		int reg = contents / 1000000 % 10;
		int reg1 = contents / 100000 % 10;
		int addr = contents % 1000000;

		// Switch statement for the opcode
		switch (opCode) {
		// ADD instruction case
		case 1:
			m_reg[reg] += m_memory[addr];
			loc += 1;
			break;
		// SUB instruction case
		case 2:
			m_reg[reg] -= m_memory[addr];
			loc += 1;
			break;
		// MULT instruction case
		case 3:
			m_reg[reg] *= m_memory[addr];
			loc += 1;
			break;
		// DIV instruction case
		case 4:
			m_reg[reg] /= m_memory[addr];
			loc += 1;
			break;
		// LOAD instruction case
		case 5:
			m_reg[reg] = m_memory[addr];
			loc += 1;
			break;
		// STORE instruction case
		case 6:
			m_memory[addr] = m_reg[reg];
			loc += 1;
			break;
		// ADD REG instruction case
		case 7:
			m_reg[reg] += m_reg[reg1];
			loc += 1;
			break;
		// SUB REG instruction case
		case 8:
			m_reg[reg] -= m_reg[reg1];
			loc += 1;
			break;
		// MULT REG instruction case
		case 9:
			m_reg[reg] *= m_reg[reg1];
			loc += 1;
			break;
		// DIV REG instruction case
		case 10:
			m_reg[reg] /= m_reg[reg1];
			loc += 1;
			break;
		// READ instruction case
		case 11:
			int input;
			cout << "? ";
			cin >> input;
			m_memory[addr] = input;
			loc += 1;
			break;
		// WRITE instruction case
		case 12:
			cout << m_memory[addr] << endl;
			loc += 1;
			break;
		// BRANCH instruction case
		case 13:
			loc = addr;
			break;
		// BRANCH MINUS instruction case
		case 14:
			if (m_reg[reg] < 0)
			{
				loc = addr;
			}
			else
			{
				loc += 1;
			}
			break;
		// BRANCH ZERO instruction case
		case 15:
			if (m_reg[reg] == 0)
			{
				loc = addr;
			}
			else
			{
				loc += 1;
			}
			break;
		// BRANCH POSITIVE instruction case
		case 16:
			if (m_reg[reg] > 0)
			{
				loc = addr;
			}
			else
			{
				loc += 1;
			}
			break;
		// HALT instruction case
		case 17: 
			cout << "End of emulation." << endl;
			exit(1);
		
		default:
			cerr << "Invalid opcode" << endl;
			exit(0);
		}
		//If statement to end the statement
		if (isEnd) {
			return true;
		}
	}
	return false;
} /* bool emulator::runProgram() */
	
