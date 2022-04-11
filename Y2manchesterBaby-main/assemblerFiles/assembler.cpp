/**
 * @file assembler.cpp
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief Logic of the Assembler Class
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#include "assembler.h"

/**
 * @brief Construct a new Assembler Object
 *
 */
Assembler::Assembler()
{
  memoryLocation = 0;
  inputFile = "BabyTest1-Assembler.txt";
}

/**
 * @brief Construct a new Assembler Object
 * @param inF The filepath of the assembly code
 * @param outF the filepath of the output file
 */
Assembler::Assembler(string inF, string outF)
{
  memoryLocation = 0;
  inputFile = inF;
  outputBuffer.setFile(outF);
}
/**
 * @brief Destroy the Assembler object
 *
 */
Assembler::~Assembler()
{
}
/**
 * @brief Gets the memory location of the assembler
 *
 * @return int The memory location
 */
int Assembler::getMemoryLocation() const
{

  return memoryLocation;
}

/**
 * @brief Set the memory location
 *
 * @param m The value for the new memory location
 * @return int The status of the function
 */
int Assembler::setMemoryLocation(int m)
{

  if (m < 0 || m > 31)
  {
    return INVALID_INPUT_PARAMETER;
  }

  memoryLocation = m;

  return SUCCESS;
}

/**
 * @brief Returns the input file of the assembler
 *
 * @return string The path of the input file
 */
string Assembler::getInputFile() const
{

  return inputFile;
}

/**
 * @brief Sets the input file for the assembler
 *
 * @param f The path to the input file for the assembler
 * @return int The status of the function
 */
int Assembler::setInputFile(string f)
{

  // Create an file stream to validate the new file path
  ifstream reader(f);
  if (!reader)
  {
    cout << "ERROR: Could not open: " << f << endl;
    return FILE_NOT_FOUND;
  }

  inputFile = f;
  return SUCCESS;
}

/**
 * @brief Sets the output file for the program
 *
 * @param f The path to the output file
 * @return int The status of the function
 */

int Assembler::setOutputFile(string f)
{

  if (f == "")
  {
    return FILE_IO_ERROR;
  }

  outputBuffer.setFile(f);
  return SUCCESS;
}

/**
 * @brief Categorises words depending on their meaning in the assembler
 *
 * @param word The word to be categorised
 * @return int The category of the word
 */
int Assembler::categoriseWord(string word) const
{

  // if the current word is a comment skip to the next line
  if (word.find(";") != string::npos)
  {
    return COMMENT;
  }

  // If the final character is a : then it is a label
  if (word.find(":") == word.length() - 1)
  {
    return LABEL;
  }

  // If the word is in the instruction set or is the word 'VAR'
  if ((instructionSet.search(word) != INVALID_INSTRUCTION_NAME && instructionSet.search(word) != INSTRUCTION_NOT_FOUND) || word == "VAR")
  {
    return INSTRUCTION;
  }

  return OPERAND;
}

/**
 * @brief Starts the assembler process
 *
 * @return int The status of the assembler
 */
int Assembler::start()
{

  initialiseInstructionSet();

  cout << "TRYING TO OPEN: " << inputFile << endl;
  // Create an file stream and validate it
  ifstream reader(inputFile);
  if (!reader)
  {
    cout << "UNABLE TO OPEN FILE: " << inputFile << endl;
    return INPUT_FILE_NOT_FOUND;
  }

  // Variable to store the line number currently being parsed.
  int lineNumber = 1;

  // Variable to store the status of various functions
  int status;
  // Create a variable to store the current line in the file
  string line;

  cout << endl
       << "--- FIRST PASS ---" << endl
       << endl;
  while (getline(reader, line))
  {

    status = 0;
    // Create a place to store all of the words on this line
    vector<string> words = {};

    // convert the line from a string to char[] for using in strtok()
    char *charLine = new char[line.length()];

    // Copy the contents of line to charLine
    strcpy(charLine, line.c_str());

    // Create a substring until the first delimiter
    char *token = strtok(charLine, " ");

    // Loop while there are still substrings to be made
    while (token != NULL)
    {
      // Add this substring to the list of words
      words.push_back(token);
      // Look for the next token
      token = strtok(NULL, " ");
    }

    // Variables for storing information about the current line
    string label = "";
    string instruction = "";
    string operand = "";

    // Tracks if there has been activity in the program on this line in the file
    bool activity = false;

    for (int i = 0; i < (int)words.size(); i++)
    {
      string currentWord = words.at(i);
      cout << lineNumber << ": Attempting to identify: " << currentWord << endl;
      int category = categoriseWord(currentWord);

      // If it is a comment move on to the next line
      if (category == COMMENT)
      {
        cout << lineNumber << ": Comment Identified" << endl;
        break;
      }

      // If it is a label
      if (category == LABEL)
      {
        cout << lineNumber << ": Label Identified" << endl;
        if (label != "")
        {
          cout << lineNumber << ": !ERROR! MULTIPLE LABELS FOUND" << endl;
          return MULTIPLE_LABELS_FOUND;
        }
        label = currentWord.substr(0, currentWord.length() - 1);
        continue;
      }

      // If it is an instruction
      if (category == INSTRUCTION)
      {
        cout << lineNumber << ": Instruction Identified" << endl;
        if (instruction != "")
        {
          cout << lineNumber << ": !ERROR! MULTIPLE INSTRUCTIONS FOUND" << endl;
          return MULTIPLE_INSTRUCTIONS_FOUND;
        }
        instruction = currentWord;
        continue;
      }

      cout << lineNumber << ": Operand Identified" << endl;
      if (operand != "")
      {
        cout << lineNumber << ": !ERROR! MULTIPLE OPERANDS FOUND" << endl;
        return MULTIPLE_OPERANDS_FOUND;
      }
      // Otherwise it is an operand
      operand = currentWord;
    }

    // If there is  label add it to the symbol table
    if (label != "")
    {

      cout << lineNumber << ": Generating Memory Location" << endl;
      string memoryLocationBinary = intToBinary(memoryLocation);
      cout << lineNumber << ": Memory Location: " << memoryLocationBinary << endl;
      // Pad the operand to 5 bits
      for (int i = memoryLocationBinary.length(); i < 5; i++)
      {
        memoryLocationBinary += "0";
      }
      status = symbolTable.insert(label, memoryLocationBinary);
      if (status != SUCCESS)
      {
        cout << lineNumber << ": !! ERROR !!" << endl;

        if (status == LABEL_ALREADY_EXISTS)
        {
          cout << lineNumber << ": Error: Label with Name: " << label << " already exists" << endl;
        }
        else if (status == FAILED_TO_INSERT)
        {
          cout << lineNumber << ": Error: Failed to insert symbol in to symbol table" << endl;
        }

        return status;
      }
      activity = true;
    }

    // If there is an instruction decode the instruction and add it to the outputBuffer
    if (instruction != "")
    {
      activity = true;

      if (instruction == "VAR")
      {
        status = outputBuffer.setBufferLineName(memoryLocation, "VAR");
        if (status != SUCCESS)
        {

          cout << lineNumber << ": !!ERROR !!" << endl;

          if (status == INVALID_MEMORY_LOCATION)
          {
            cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
          }
          else if (status == INVALID_INSTRUCTION_NAME)
          {
            cout << lineNumber << ": Error: Invalid Instruction Name" << endl;
          }

          return status;
        }
        if (operand != "")
        {
          int intValue = stoi(operand);
          status = outputBuffer.setBufferLineValue(memoryLocation, intValue);
          if (status != SUCCESS)
          {
            cout << lineNumber << ": !! ERROR !!" << endl;
            if (status == INVALID_MEMORY_LOCATION)
            {
              cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
            }
            return status;
          }
        }
        else
        {
          cout << lineNumber << ": !!ERROR !!" << endl;
          cout << lineNumber << ": Error: No Operand Found " << memoryLocation << endl;
          return NO_OPERAND_FOUND;
        }
      }

      if (instruction == "JMP")
      {

        if (operand != "")
        {
          int symbolLocation = symbolTable.search(operand);

          // If the symbol location is an invalid operand
          if (symbolLocation == INVALID_INPUT_PARAMETER)
          {
            cout << lineNumber << ": !! ERROR !! " << endl;

            cout << lineNumber << ": Error: Invalid Label" << endl;
          }
          // If the operand is not in the symbol table
          if (symbolLocation == -1)
          {
            string instructionBinary = instructionSet.lookup("JMP");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
            }
            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !! ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction Binary" << endl;
              }

              return status;
            }
          }
          else
          {
            string instructionBinary = instructionSet.lookup("JMP");

            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }

            string operandBinary = symbolTable.lookup(operand);

            if (operandBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find operand" << endl;
              return LABEL_NOT_FOUND;
            }

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary, operandBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
              else if (status == INVALID_OPERAND_BINARY)
              {
                cout << lineNumber << ": Error: Invalid operand binary" << endl;
              }

              return status;
            }
          }
        }
        else
        {
          cout << lineNumber << ": !!ERROR !!" << endl;
          cout << lineNumber << ": Error: No Operand Found " << memoryLocation << endl;
          return NO_OPERAND_FOUND;
        }
      }

      if (instruction == "JRP")
      {

        if (operand != "")
        {
          int symbolLocation = symbolTable.search(operand);

          // If the symbol location is an invalid operand
          if (symbolLocation == INVALID_INPUT_PARAMETER)
          {
            cout << lineNumber << ": !! ERROR !! " << endl;
            cout << lineNumber << ": Error: Invalid Label" << endl;
          }

          // If the operand is not in the symbol table
          if (symbolLocation == -1)
          {
            string instructionBinary = instructionSet.lookup("JRP");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }

              return status;
            }
          }
          else
          {
            string instructionBinary = instructionSet.lookup("JRP");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }

            string operandBinary = symbolTable.lookup(operand);

            if (operandBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find operand" << endl;
              return LABEL_NOT_FOUND;
            }

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary, operandBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
              else if (status == INVALID_OPERAND_BINARY)
              {
                cout << lineNumber << ": Error: Invalid operand binary" << endl;
              }

              return status;
            }
          }
        }
        else
        {
          cout << lineNumber << ": !!ERROR !!" << endl;
          cout << lineNumber << ": Error: No Operand Found " << memoryLocation << endl;
          return NO_OPERAND_FOUND;
        }
      }

      if (instruction == "LDN")
      {

        if (operand != "")
        {
          int symbolLocation = symbolTable.search(operand);
          // If the symbol location is an invalid operand
          if (symbolLocation == INVALID_INPUT_PARAMETER)
          {
            cout << lineNumber << ": !! ERROR !! " << endl;
            cout << lineNumber << ": Error: Invalid Label" << endl;
            return INVALID_INPUT_PARAMETER;
          }

          // If the operand is not in the symbol table
          if (symbolLocation == -1)
          {
            string instructionBinary = instructionSet.lookup("LDN");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
              return status;
            }
          }
          else
          {
            string instructionBinary = instructionSet.lookup("LDN");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }
            string operandBinary = symbolTable.lookup(operand);
            if (operandBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find operand" << endl;
              return LABEL_NOT_FOUND;
            }

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary, operandBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
              else if (status == INVALID_OPERAND_BINARY)
              {
                cout << lineNumber << ": Error: Invalid operand binary" << endl;
              }
              return status;
            }
          }
        }
        else
        {
          cout << lineNumber << ": !!ERROR !!" << endl;
          cout << lineNumber << ": Error: No Operand Found " << memoryLocation << endl;
          return NO_OPERAND_FOUND;
        }
      }

      if (instruction == "STO")
      {

        if (operand != "")
        {
          int symbolLocation = symbolTable.search(operand);
          // If the symbol location is an invalid operand
          if (symbolLocation == INVALID_INPUT_PARAMETER)
          {
            cout << lineNumber << ": !! ERROR !! " << endl;
            cout << lineNumber << ": Error: Invalid Label" << endl;
            return INVALID_INPUT_PARAMETER;
          }

          // If the operand is not in the symbol table
          if (symbolLocation == -1)
          {
            string instructionBinary = instructionSet.lookup("STO");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
            }
          }
          else
          {
            string instructionBinary = instructionSet.lookup("STO");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }
            string operandBinary = symbolTable.lookup(operand);
            if (operandBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find operand" << endl;
              return LABEL_NOT_FOUND;
            }
            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary, operandBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
              else if (status == INVALID_OPERAND_BINARY)
              {
                cout << lineNumber << ": Error: Invalid operand binary" << endl;
              }
            }
          }
        }
        else
        {
          cout << lineNumber << ": !!ERROR !!" << endl;
          cout << lineNumber << ": Error: No Operand Found " << memoryLocation << endl;
          return NO_OPERAND_FOUND;
        }
      }

      if (instruction == "SUB")
      {

        if (operand != "")
        {
          int symbolLocation = symbolTable.search(operand);
          if (symbolLocation == INVALID_INPUT_PARAMETER)
          {
            cout << lineNumber << ": !! ERROR !! " << endl;
            cout << lineNumber << ": Error: Invalid Label" << endl;
            return INVALID_INPUT_PARAMETER;
          }

          // If the operand is not in the symbol table
          if (symbolLocation == -1)
          {
            string instructionBinary = instructionSet.lookup("SUB");

            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
            }
          }
          else
          {
            string instructionBinary = instructionSet.lookup("SUB");
            if (instructionBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find instruction" << endl;
              return INSTRUCTION_NOT_FOUND;
            }
            string operandBinary = symbolTable.lookup(operand);
            if (operandBinary == "")
            {
              cout << lineNumber << ": !! ERROR !! " << endl;
              cout << lineNumber << ": Error: Cannot find operand" << endl;
              return LABEL_NOT_FOUND;
            }
            status = outputBuffer.setBufferLine(memoryLocation, instructionBinary, operandBinary);
            if (status != SUCCESS)
            {

              cout << lineNumber << ": !!ERROR !!" << endl;
              if (status == INVALID_MEMORY_LOCATION)
              {
                cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
              }
              else if (status == INVALID_INSTRUCTION_BINARY)
              {
                cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
              }
              else if (status == INVALID_OPERAND_BINARY)
              {
                cout << lineNumber << ": Error: Invalid operand binary" << endl;
              }
            }
          }
        }
        else
        {
          cout << lineNumber << ": !!ERROR !!" << endl;
          cout << lineNumber << ": Error: No Operand Found " << memoryLocation << endl;
          return NO_OPERAND_FOUND;
        }
      }

      if (instruction == "CMP")
      {

        string instructionBinary = instructionSet.lookup("CMP");
        if (instructionBinary == "")
        {
          cout << lineNumber << ": !! ERROR !! " << endl;
          cout << lineNumber << ": Error: Cannot find instruction" << endl;
          return INSTRUCTION_NOT_FOUND;
        }
        status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
        if (status != SUCCESS)
        {

          cout << lineNumber << ": !!ERROR !!" << endl;
          if (status == INVALID_MEMORY_LOCATION)
          {
            cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
          }
          else if (status == INVALID_INSTRUCTION_BINARY)
          {
            cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
          }
        }
      }

      if (instruction == "STP")
      {

        string instructionBinary = instructionSet.lookup("STP");
        if (instructionBinary == "")
        {
          cout << lineNumber << ": !! ERROR !! " << endl;
          cout << lineNumber << ": Error: Cannot find instruction" << endl;
          return INSTRUCTION_NOT_FOUND;
        }

        status = outputBuffer.setBufferLine(memoryLocation, instructionBinary);
        if (status != SUCCESS)
        {

          cout << lineNumber << ": !!ERROR !!" << endl;
          if (status == INVALID_MEMORY_LOCATION)
          {
            cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
          }
          else if (status == INVALID_INSTRUCTION_BINARY)
          {
            cout << lineNumber << ": Error: Invalid Instruction binary" << endl;
          }
        }
      }
    }
    if (activity)
    {
      memoryLocation++;
    }

    lineNumber++;
  }

  // Reset the memory location back to the start
  memoryLocation = 0;

  // Create an new file stream and validate it
  ifstream reader2(inputFile);
  if (!reader2)
  {
    cout << "ERROR: Could not open: " << inputFile;
    return INPUT_FILE_NOT_FOUND;
  }

  cout << endl
       << "--- SECOND PASS ---" << endl
       << endl;

  // Reset the line number
  lineNumber = 0;

  // Reset the function status
  status = 0;

  while (getline(reader2, line))
  {

    // Create a place to store all of the words on this line
    vector<string> words = {};

    // convert the line from a string to char[] for using in strtok()
    char *charLine = new char[line.length()];
    // char charLine[line.length()];

    // Copy the contents of line to charLine
    strcpy(charLine, line.c_str());

    // Create a substring until the first delimiter
    char *token = strtok(charLine, " ");
    // Loop while there are still substrings to be made
    while (token != NULL)
    {
      // Add this substring to the list of words
      words.push_back(token);
      // Look for the next token
      token = strtok(NULL, " ");
    }

    // Variables for storing information about the current line
    string label = "";
    string instruction = "";
    string operand = "";

    // Tracks if there has been activity in the program on this line in the file
    bool activity = false;

    for (int i = 0; i < (int)words.size(); i++)
    {
      string currentWord = words.at(i);
      cout << lineNumber << ": Attempting to identify: " << currentWord << endl;
      int category = categoriseWord(currentWord);

      // If it is a comment move on to the next line
      if (category == COMMENT)
      {
        cout << lineNumber << ": Comment Identified" << endl;
        break;
      }

      // If it is a label move to the next word
      if (category == LABEL)
      {
        cout << lineNumber << ": Label Identified" << endl;
        activity = true;
        continue;
      }

      // If it is an instruction move to the next word
      if (category == INSTRUCTION)
      {
        cout << lineNumber << ": Instruction Identified" << endl;
        instruction = currentWord;
        activity = true;
        continue;
      }

      cout << lineNumber << ": Operand Identified" << endl;
      // Otherwise it is an operand
      operand = currentWord;
    }

    if (operand != "" && instruction != "VAR")
    {

      string operandBinary = symbolTable.lookup(operand);
      if (operandBinary == "")
      {
        cout << lineNumber << ": !! ERROR !!" << endl;
        cout << lineNumber << ": Operand not declared" << endl;
        return INVALID_OPERAND_BINARY;
      }

      status = outputBuffer.setBufferLineOperand(memoryLocation, operandBinary);
      if (status != SUCCESS)
      {

        cout << lineNumber << ": !!ERROR !!" << endl;

        if (status == INVALID_MEMORY_LOCATION)
        {
          cout << lineNumber << ": Error: Invalid Memory Location " << memoryLocation << endl;
        }
        else if (status == INVALID_INSTRUCTION_NAME)
        {
          cout << lineNumber << ": Error: Invalid Instruction Name" << endl;
        }

        return status;
      }
      activity = true;
    }
    if (activity)
    {
      memoryLocation++;
    }

    lineNumber++;
  }

  status = outputBuffer.writeBuffer();
  if (status != SUCCESS)
  {
    if (status == FILE_IO_ERROR)
    {
      cout << "!! ERROR !!" << endl;
      cout << "Error: Could not open file" << endl;
    }

    return status;
  }

  cout << endl
       << "--- SUCCESSFULLY ASSEMBLED ---" << endl
       << endl;
  return SUCCESS;
}
/**
 * @brief A function to initialse the assemblers instruction set.
 *
 * @return int A status code of the function
 */
int Assembler::initialiseInstructionSet()
{

  // Insert all the machine code commands
  instructionSet.insert("JMP", "000");
  instructionSet.insert("JRP", "100");
  instructionSet.insert("LDN", "010");
  instructionSet.insert("STO", "110");
  instructionSet.insert("SUB", "001");
  instructionSet.insert("SUB", "101");
  instructionSet.insert("CMP", "011");
  instructionSet.insert("STP", "111");

  return 0;
}