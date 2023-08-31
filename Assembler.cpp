#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"



// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler(int argc, char* argv[])
    : m_facc(argc, argv)
{
    // Nothing else to do here at this point.
} /* Assembler::Assembler(int argc, char* argv[])
    : m_facc(argc, argv) */


// Destructor currently does nothing.  You might need to add something as you develope this project.  If not, we can delete it.
Assembler::~Assembler()
{

} /* Assembler::~Assembler() */
// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.
void Assembler::PassI()
{
    int loc = 0;        // Tracks the location of the instructions to be generated.
    int label;

    // Successively process each line of source code.
    for (; ; ) {

        // Read the next line from the source file.
        string line;
        if (!m_facc.GetNextLine(line)) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if (st == Instruction::InstructionType::ST_End) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip comments.
        if (st == Instruction::InstructionType::ST_Comment)
        {
            continue;
        }
        // Handle the case where there is an error.
       
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if (m_inst.isLabel()) {
            if (m_symtab.LookupSymbol(m_inst.GetLabel(), label)) {
                string error = "END is not in the last statement";
                Errors::RecordError(error);
            }
            m_symtab.AddSymbol(m_inst.GetLabel(), loc);
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction(loc);
    } 

   
} /* void Assembler::PassI() */



/*
NAME

    PassII() - .

SYNOPSIS

    bool emulator::runProgram( );

DESCRIPTION

    This function generates the machine language equivalent of the assembler language.

*/
void Assembler::PassII()
{
    //Resets file to the beinning
    m_facc.rewind();
    int loc = 1;
    long long instructionContents;

    Errors::InitErrorReporting();
    //formats the output generated through passII
    cout << endl;
    cout << "Translation of the program:" << endl;
    cout << endl;
    cout << setw(10) << left << "Location" << left << setw(10) << "Contents" << left << setw(10) << "Original statement" << endl;

    //Goes line by line through the file
    for (; ; ) 
    {
        
        instructionContents = 0;
        // Read in next line
        string readLine;
        //If there is no more lines and no error statements record error
        if (!m_facc.GetNextLine(readLine)) 
        {
            string error_msg = "Error: 'End' statement is missing\n";
            Errors::RecordError(error_msg);
            break;
        }


        Instruction::InstructionType st = m_inst.ParseInstruction(readLine);
        //If statements to error check
        if (st == Instruction::InstructionType::ST_Error) 
        {
            string err = "There was an error while translating the statement";
            Errors::RecordError(err);
        }

        if (m_inst.GetLabel()[0] <= '9' && m_inst.GetLabel()[0] >= '0') 
        {
            string recordError = m_inst.GetLabel() + " is not valid. Needs to start with an alpha character.";
            Errors::RecordError(recordError);
        }
        else if (m_inst.GetLabel().length() > 10) 
        {
          string recordError = m_inst.GetLabel() + " is not valid. Label can only be between 1-10 characters.";
          Errors::RecordError(recordError);
        }

        if (st == Instruction::InstructionType::ST_Comment || readLine.empty()) 
        {
            cout << readLine << "\t" << endl;
            continue;
        }
                    
        if (st == Instruction::InstructionType::ST_End) 
        {
           cout << m_inst.GetInstruction() << endl;
           break;
        }
        //If it is not Machine or Assembly language, we call the instruction getter
        if (st != Instruction::InstructionType::ST_MachineLanguage && st != Instruction::InstructionType::ST_AssemblerInstr)
        {
           cout << "\t \t \t" << m_inst.GetInstruction() << endl;
           continue;
        }
        //Sets the instruction length
        instructionContents = m_inst.GetNumericOperand() * 10000000;
        //If statement to record errors for the assembler instruction
        if (st == Instruction::InstructionType::ST_AssemblerInstr) 
        {
           //If not end continue
           if (m_inst.GetOpCode() != "END")
           {
               //Error for an empty operand 1
               if (m_inst.GetOperand1().empty()) 
               {
                   Errors::RecordError("Empty equivalent for operand 1");
               }
               //Checking if input is not numeric
               else if (!m_inst.isNumericOperand1()) 
               {
                   Errors::RecordError(m_inst.GetOperand2() + "input is not valid, needs to be numeric.");
               }
               //Error for an empty operand 2
               if (m_inst.GetOperand2().empty()) 
               {
                   Errors::RecordError("Empty equivalent for operand 2");
               }
               //Checking if input is not numeric
               else if (!m_inst.isNumericOperand2()) 
               {
                   Errors::RecordError(m_inst.GetOperand2() + "Input is not valid, needs to be numeric.");
               }
               //If the opcode is not org and label is empty, need a different input
               if (m_inst.GetOpCode() != "ORG" && m_inst.GetLabel().empty()) 
               {
                   string toRecord = m_inst.GetOpCode();
                   Errors::RecordError("Invalide opcode, " + toRecord + " needed");
               }
           }
           //Adds the numeric Operand 1 if input is DC
           if (m_inst.GetOpCode() == "DC") 
           {
               instructionContents += m_inst.GetNumericOperand();
           }
        }       
           
           if (!m_inst.GetOperand1().empty() || m_inst.GetNumericOperand() != 17) 
           {
               string recordError = m_inst.GetOpCode() + " The Operand1 is missing.";
               Errors::RecordError(recordError);
           }

           else if (m_inst.isNumericOperand1() && !m_inst.GetOperand1().empty()) 
           {
               int symLoc = 0;

               if (m_symtab.LookupSymbol(m_inst.GetOperand1(), symLoc)) {
                   string toRecord = "Operand: " + m_inst.GetOperand1() + " is not found";
                   Errors::RecordError(toRecord);
                   //sets symbol location to the end of the constaint
                   symLoc = 999999;
               }
               //Adds the above constant to the instructionContents
               instructionContents += symLoc;
           }
       }
   //Formats output
   cout << setfill(' ') << loc << instructionContents << setw(7) << loc << "\t";
   //Inserts the location and memory into an emulator instance for emulation
   m_emul.insertMemory(loc, instructionContents);
   //Gets the instructions to output
   cout << " " << m_inst.GetInstruction() << endl;
   //Calls the location for getting the next instruction
   loc = m_inst.LocationNextInstruction(loc);
    
    //Formats and displays Errors
    cout << "________________________________________" << endl;
    Errors::DisplayErrors();
    cout << "_________________________________________" << endl;
} /* void Assembler::PassII() */



