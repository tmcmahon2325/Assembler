//
//   Thomas McMahon
//
#include "stdafx.h"
#include "Errors.h"
#include "Instruction.h"
#include "SymTab.h"

/*
 NAME

    Instruction::InstructionType Instruction::ParseInstruction(string a_line)

 SYNOPSIS

   Instruction::InstructionType Instruction::ParseInstruction(string a_line)
        string a_Line -> Stores the string to test for instruction

 SYNOPSIS

    This function returns what type of instruction

 RETURN

    An instructionType on what was found
 */
Instruction::InstructionType Instruction::ParseInstruction(string a_line)
{
       
    // Record the original statement.  This will be needed in the sceond pass.
    m_instruction = a_line;

    // Delete any comment from the line.
    DeleteComment( a_line );

    // Record label, opcode, and operands.  Up to you to deal with formatting errors.
    bool isFormatError = RecordFields( a_line );
    
    if (m_Operand1.empty()) {
        m_IsNumericOperand1 = false;
    }

    //Use a range-based for loop (thanks C++ 11!) to check each character of operand 1
    //and if isdigit() returns false for any of them, then we set the bool to false.
    for (char const& ch : m_Operand1) {
        if (isdigit(ch) == 0) {
            m_IsNumericOperand1 = false;
        }
    }   
    
    // Return the instruction type.  This has to be handled in the code.
    return GetInstructionType(m_OpCode);
} /* Instruction::InstructionType Instruction::ParseInstruction(string a_line) */


  
  
  
/*
NAME

    Instruction::RecordFields - records the fields of the instruction

SYNOPSIS

    bool Instruction::RecordFields(const string &a_line);
        a_line -> a line passed in to retreive information.

DESCRIPTION

    This function records the fields passed in and calls the parse method
    to store the individual values

RETURN

    A boolean on whether or not it was successful
*/
bool Instruction::RecordFields( const string &a_line )
{
    // Get the fields that make up the instruction.
    bool isFormatError = ! ParseLineIntoFields( a_line, m_Label, m_OpCode, m_Operand1, m_Operand2);

    // if code was a comment, there is nothing to do.
    if (m_OpCode.empty() && m_Label.empty()) return isFormatError;

    // Record whether the operands are numeric and their value if they are.
    m_IsNumericOperand1 = isStrNumber(m_Operand1);
    if (m_IsNumericOperand1) m_Operand1NumericValue = stoi(m_Operand1);

    m_IsNumericOperand2 = isStrNumber(m_Operand2);
    if (m_IsNumericOperand2) m_Operand2NumericValue = stoi(m_Operand2);

    // For the sake of comparing, convert the op code to upper case.
    for (char& c : m_OpCode)
    {
        c = toupper(c);
    }
    

    return true;
} /* bool Instruction::RecordFields( const string &a_line ) */

/*
NAME

    bool Instruction::isAssemblyCode - checks if the param is an assembly instruction

SYNOPSIS

    bool Instruction::isAssemblyCode(string a_OpCode);
        a_OpCode -> This reads in the opCode and compares it to determine its type
*/
bool Instruction::isAssemblyCode(string a_OpCode) {
    for (string OpCode : m_AssemblyOpCode) {
        if (OpCode == a_OpCode) {
            return true;
        }
    }
    return false;
} /* bool Instruction::isAssemblyCode(string a_OpCode); */


/*
Name 

    Instruction::InstructionType Instruction::GetInstructionType(string a_OpCode)

SYNOPSIS

    Instruction::InstructionType Instruction::GetInstructionType(string a_OpCode);\
        a_OpCode -> This stores the opCode for comparison

DESCRIPTION

    Uses the OpCode to compare to the enum instruction types to find out what instruction
    type it is

RETURNS

    The instruction type of the parameter

*/
Instruction::InstructionType Instruction::GetInstructionType(string a_OpCode) {
    
    if (m_OpCode == "DS" || m_OpCode == "DC" || m_OpCode == "ORG") {
       return InstructionType::ST_AssemblerInstr;
    }
    
    else if (m_OpCode == "END") {
        return InstructionType::ST_End;
    }

    else if (m_OpCode == " " && m_Label == " ") {
        return InstructionType::ST_Comment;
    }
    else {
        m_type = InstructionType::ST_Error;
    }
    return m_type;
} /* Instruction::InstructionType Instruction::GetInstructionType(string a_OpCode); */

/*
NAME

    int Instruction::LocationNextInstruction(int a_loc);

SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc)
        int a_loc -> the current location

DESCRIPTION

    This function reads in the current location to find the next location

RETURN

    The new location
*/
 int Instruction::LocationNextInstruction(int a_loc) 
 {   //If it is a comment or instruction, we return the current location
     if (m_type == InstructionType::ST_Comment || m_type == InstructionType::ST_End) 
     {
         return a_loc;
     }
     //If it is ORG or DS instructions, we add by Operand1's numeric value
     if (m_OpCode == "ORG" || m_OpCode == "DS") 
     {
         return stoi(m_Operand1);
     }
     //If it is a MachineLanguage Instruction and org called, return location + Operand1
     else if (m_type == InstructionType::ST_MachineLanguage && m_OpCode == "org") 
     {
         return a_loc + stoi(m_Operand1);
     }
     return a_loc++;

 } /* int Instruction:LocationNextInstruction(in a_loc); */

 /*
 NAME

    int InstructionOpCode(string& a_loc)

 SYNOPSIS

    int InstructOpCode(string& a_loc)
        string& a_loc -> The current location

 Description

    This defines a map for the AssemblyOpCode

 RETURN
 
    The integer equivelant from the map off of the string input
 */
 int InstructionOpCode(string& a_loc) {
     map<string, int> m_AssemblyOpCode = { {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV",4}, {"LOAD",5}, {"STORE", 6}, {"ADDR", 7},
        {"SUBR", 8}, {"MULTR", 9}, {"DIVR", 10}, {"READ", 11}, {"WRITE", 12}, {"B", 13}, {"BM", 14}, {"BZ", 15}, {"BP", 16},
        {"HALT", 17} };

     if (m_AssemblyOpCode[a_loc] <= 17 && m_AssemblyOpCode[a_loc] >= 1) {
         return m_AssemblyOpCode[a_loc];
     }
     else {
         return -1;
     }
 } /*int InstructionOpCode(string& a_loc); */
 
/*
 NAME

    bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
                                          string& a_Operand1, string& a_Operand2)

 SYNOPSIS

    bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
                                          string& a_Operand1, string& a_Operand2)
        string a_line      -> the current line
        string& a_label    -> this points to the label location
        string& a_OpCode   -> this point to the OpCode location
        String& a_Operand1 -> this points to Operand1 location
        String& a_Operand2 -> this points to Operand2 location

 Description
 
    This parses the input line and adds the fields read in to individual varaiables

 RETURN

    A boolean on whether or not it was successful
 */
bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
    string& a_Operand1, string& a_Operand2)
{
    // Get rid of any commas from the line.
    replace(a_line.begin(), a_line.end(), ',', ' ');

    // Get the elements of the line.  That is the label, op code, operand1, and operand2.
    string endStr;
    a_label = a_OpCode = a_Operand1 = a_Operand2 = "";
    istringstream ins(a_line);
    if (a_line[0] == ' ' || a_line[0] == '\t')
    {
        a_label = "";
        ins >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
    }
    else
    {
        ins >> a_label >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
    }
    // If there is extra data, return false.
    return endStr.empty() ? true : false;
} /* bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
    string& a_Operand1, string& a_Operand2) */

/*
 NAME

    bool Instruction::isStrNumber(const string& a_str);

 SYNOPSIS

    bool Instruction::isStrNumber(const string& a_str)
        a_str -> The string we are testing for a numbe

 Description
 
    This function checks to see if a string is an integer

 RETURN

    A boolean on whether or not the string input is an integer
 */
bool Instruction::isStrNumber(const string& a_str)
{
    if (a_str.empty()) return false;

    // If there is a - or a plus, make sure there are more characters.
    int ichar = 0;
    if (a_str[0] == '-' || a_str[0] == '+')
    {
        ichar++;
        if (a_str.length() < 2) return false;
    }
    // Make sure that the remaining characters are all digits
    for (; ichar < a_str.length(); ichar++)
    {
        if (!isdigit(a_str[ichar])) return false;
    }
    return true;
} /* bool Instruction::isStrNumber(const string& a_str) */
