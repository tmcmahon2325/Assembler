//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

    //Instructor Desctructor for the Instruction class
    Instruction() { };
    ~Instruction() { };

    //Enumeration for the InstructionType
    enum class InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,      // Assembler Language instruction.
        ST_Comment,             // Comment or blank line
        ST_End,                 // end instruction.
        ST_Error                // Statement has an error.
    };


    // Parse the Instruction.
    InstructionType ParseInstruction(string a_line);
    
    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);

    //String to return the instruction
    inline string& GetInstruction() { return m_instruction; }

    //Getter for the NumOpCode
    inline int GetNumericOperand()  { return m_NumOpCode; }

    // To access the label
    inline string& GetLabel() {

        return m_Label;
    };
    // To determine if a label is blank.
    inline bool isLabel() {

        return !m_Label.empty();
    };
    //Checking if Operand1 is numeric
    inline bool isNumericOperand1() {
        return m_IsNumericOperand1;
    }
    //Checking if Operand2 is numeric
    inline bool isNumericOperand2() {
        return m_IsNumericOperand2;
    }
    
    //Function to return the found instructionType
    InstructionType GetInstructionType(string a_OpCode);
    
    //Test to see if opCode is Assembly Code
    bool isAssemblyCode(string a_opCode);
    //Getters for the numeric values of Operands
    inline int& GetOperand1NumericValue() { return m_Operand1NumericValue; }
    inline int& GetOperand2NumericValue() { return m_Operand2NumericValue; }
    //Getters for the OpCode, Operand1 and Operand2
    inline string& GetOpCode() { return m_OpCode; }  
    inline string& GetOperand1() { return m_Operand1;  }
    inline string& GetOperand2() { return m_Operand2;  }

    
private:


    // The elemements of a instruction
    string m_Label;        // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand1;     // The first operand. 
    string m_Operand2;     // The second operand.


    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode = 0;     // The numerical value of the op code for machine language equivalents.

    InstructionType m_type = InstructionType::ST_Error; // The type of instruction.

    bool m_IsNumericOperand1 = false;// == true if the operand 1 is numeric.
    int m_Operand1NumericValue = 0;   // The value of the operand 1 if it is numeric.

    
    bool m_IsNumericOperand2 = false;// == true if the operand 2 is numeric.
    int m_Operand2NumericValue = 0;   // The value of the operand 2 if it is numeric.

    
    // Delete any comments from the statement.
    void DeleteComment(string& a_line)
    {
        size_t isemi1 = a_line.find(';');
        if (isemi1 != string::npos)
        {
            a_line.erase(isemi1);
        }
    }

    
   
    // Record the fields of the instructions.
    bool RecordFields(const string& a_line);

    // Get the fields that make up the statement.  This function returns false if there
    // are extra fields.
    bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
        string& a_Operand1, string& a_Operand2);

    // Check if a string contains a number. 
    bool isStrNumber(const string& a_str);

    
    //Map to store the MachineOpCode, <string, int>::<InstructionConstant, InstrustionNumber>
    map<string, int> m_MachineOpCode = { {"ADD", 1}, {"SUB", 2}, {"MULT", 3}, {"DIV",4}, {"LOAD",5}, {"STORE", 6}, {"ADDR", 7},
        {"SUBR", 8}, {"MULTR", 9}, {"DIVR", 10}, {"READ", 11}, {"WRITE", 12}, {"B", 13}, {"BM", 14}, {"BZ", 15}, {"BP", 16},
        {"HALT", 17} };

    //Vector to store AssemblyOpCode
    vector<string> m_AssemblyOpCode = { "DC", "DS", "ORG", "END" };
};




