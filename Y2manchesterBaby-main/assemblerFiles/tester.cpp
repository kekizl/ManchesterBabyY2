/**
 * @file tester.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-12-04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tester.h"

int main()
{

  // testSymbols();
  // testSymbolTable();
  // testInstruction();
  // testInstructionSet();
  // testOutputBuffer();
  testAssembler();

  return 0;
}

/**
 * @brief Tests the functions related to the Symbol Object
 *
 */
void testSymbols()
{

  cout << "---- SYMBOL TESTING ----" << endl
       << endl;
  cout << "TESTING BLANK CONSTRUCTOR: " << endl;
  Symbol a;
  cout << a;
  cout << "SHOULD EQUAL: " << endl
       << ":" << endl;

  cout << "TESTING NON-BLANK CONSTRUCTOR: " << endl;
  Symbol b("test", "1001");
  cout << b;
  cout << "SHOULD EQUAL: " << endl
       << "test"
       << ":"
       << "1001" << endl;

  cout << "TESTING GETTING LABEL" << endl;
  if (b.getLabel() == "test")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "LABEL:" << b.getLabel() << endl;
  }

  cout << "TESTING GETTING ADDRESS" << endl;
  if (b.getAddress() == "1001")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "ADDRESS:" << b.getAddress() << endl;
  }

  cout << "TESTING SETTING ADDRESS" << endl;
  b.setAddress("101");
  if (b.getAddress() == "101")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "ADDRESS:" << b.getAddress() << endl;
  }

  cout << "---- SYMBOL TESTING COMPLETE ----" << endl
       << endl;
}
/**
 * @brief Tests the functions related to the Symbol Table Object
 *
 */
void testSymbolTable()
{
  cout << "---- SYMBOL TABLE TESTING ----" << endl
       << endl;

  cout << "TESTING BLANK CONSTRUCTOR" << endl;
  SymbolTable a;
  cout << a;
  cout << "SHOULD EQUAL: " << endl;
  for (int i = 0; i < 10; i++)
  {
    cout << i << ":"
         << ":" << endl;
  }

  cout << "TESTING NON-BLANK CONSTRUCTOR" << endl;
  SymbolTable b(5);
  cout << b;
  cout << "SHOULD EQUAL: " << endl;
  for (int i = 0; i < 5; i++)
  {
    cout << i << ":"
         << ":" << endl;
  }

  cout << "TESTING HASH FUNCTION" << endl;
  cout << "CASE 1: " << endl;
  if (b.hashFunction("t") == 1)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "HASH POSITION:" << b.hashFunction("t") << endl;
  }

  cout << "CASE 2: " << endl;
  if (b.hashFunction("te") == 2)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "HASH POSITION:" << b.hashFunction("te") << endl;
  }

  cout << "CASE 3: " << endl;
  if (b.hashFunction("testing") == 1)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "HASH POSITION:" << b.hashFunction("testing") << endl;
  }

  cout << "TESTING INSERT FUNCTION" << endl;
  b.insert("testing", "1010");
  b.insert("te", "1001");
  b.insert("t", "1011");

  cout << b;
  cout << "SHOULD EQUAL: " << endl;
  cout << "0::" << endl;
  cout << "1:testing:1010" << endl;
  cout << "2:te:1001" << endl;
  cout << "3:t:1011" << endl;
  cout << "4::" << endl;

  cout << "TESTING REHASH FUNCTION" << endl;
  b.reHash();

  cout << b;
  cout << "SHOULD EQUAL: " << endl;
  cout << "0::" << endl;
  cout << "1::" << endl;
  cout << "2::" << endl;
  cout << "3::" << endl;
  cout << "4::" << endl;
  cout << "5::" << endl;
  cout << "6:testing:1010" << endl;
  cout << "7:te:1001" << endl;
  cout << "8:t:1011" << endl;
  cout << "9::" << endl;

  cout << "TESTING SEARCH FUNCTION" << endl;
  if (b.search("testing") == 6)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "SEARCH POSITION:" << b.search("testing") << endl;
  }

  cout << "TESTING LOOKUP FUNCTION" << endl;

  if (b.lookup("testing") == "1010")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "ADDRESS VALUE:" << b.lookup("testing") << endl;
  }
  cout << "TESTING UPDATE FUNCTION" << endl;
  b.update("testing", "0000");

  if (b.lookup("testing") == "0000")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "ADDRESS VALUE:" << b.lookup("testing") << endl;
  }
  cout << "---- SYMBOL TABLE TESTING COMPLETE ----" << endl
       << endl;
}

/**
 * @brief Tests the functions related to the Instruction Object
 *
 */
void testInstruction()
{
  cout << "---- INSTRUCTION TESTING ----" << endl
       << endl;
  cout << "TESTING BLANK CONSTRUCTOR: " << endl;

  Instruction a;
  cout << a;
  cout << "SHOULD EQUAL: " << endl
       << ":" << endl;

  cout << "TESTING NON-BLANK CONSTRUCTOR: " << endl;

  Instruction b("TEST", "101");
  cout << b;
  cout << "SHOULD EQUAL: " << endl
       << "TEST:101" << endl;

  cout << "TESTING GET NAME" << endl;
  if (b.getName() == "TEST")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "INSTRUCTION NAME: " << b.getName() << endl;
  }

  cout << "TESTING GET BINARY" << endl;
  if (b.getBinary() == "101")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "INSTRUCTION BINARY: " << b.getBinary() << endl;
  }

  cout << "TESTING SET BINARY" << endl;
  b.setBinary("000");
  if (b.getBinary() == "000")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "INSTRUCTION BINARY: " << b.getBinary() << endl;
  }
  cout << "---- INSTRUCTION TESTING COMPLETE ----" << endl
       << endl;
}

/**
 * @brief Tests the functions related to the Instruction Set
 *
 */
void testInstructionSet()
{
  cout << "---- INSTRUCTION SET TESTING ----" << endl
       << endl;

  cout << "TESTING BLANK CONSTRUCTOR: " << endl;

  InstructionSet a;
  cout << a;
  cout << "SHOULD EQUAL: " << endl;
  for (int i = 0; i < 8; i++)
  {
    cout << i << "::" << endl;
  }

  cout << "TESTING INSERT FUNCTION: " << endl;

  a.insert("TEST", "101");
  cout << a;
  cout << "SHOULD EQUAL: " << endl;
  cout << "0:TEST:101" << endl;
  for (int i = 1; i < 8; i++)
  {
    cout << i << "::" << endl;
  }

  a.insert("STOP", "001");
  a.insert("GOTO", "010");
  cout << "TESTING SEARCH FUNCTION: " << endl;
  if (a.search("STOP") == 1)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "SEARCH POSITION: " << a.search("STOP") << endl;
  }

  cout << "TESTING LOOKUP FUNCTION: " << endl;
  if (a.lookup("GOTO") == "010")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED" << endl;
    cout << "LOOKUP POSITION: " << a.lookup("GOTO") << endl;
  }

  cout << "---- INSTRUCTION SET TESTING COMPLETE ----" << endl
       << endl;
}

/**
 * @brief Tests the functions related to the output buffer
 *
 */
void testOutputBuffer()
{
  cout << "---- CODE BUFFER TESTING ----" << endl
       << endl;

  cout << "TESTING BLANK CONSTRUCTOR: " << endl;

  OutputBuffer a;
  cout << a;
  cout << "SHOULD EQUAL: " << endl;
  cout << "File: machineCode.txt" << endl;
  for (int i = 0; i < 32; i++)
  {
    cout << i << ":" << endl;
  }

  cout << "TESTING NON-BLANK CONSTRUCTOR: " << endl;
  OutputBuffer b("output.txt");
  cout << b;
  cout << "SHOULD EQUAL: " << endl;
  cout << "File: output.txt" << endl;
  for (int i = 0; i < 32; i++)
  {
    cout << i << ":" << endl;
  }

  cout << "TESTING SET BUFFER: " << endl;
  b.setBuffer(3, "10101010100100001001001");
  cout << b;
  cout << "SHOULD EQUAL: " << endl;
  cout << "File: output.txt" << endl;
  cout << "0:" << endl
       << "1:" << endl
       << "2:" << endl
       << "3:10101010100100001001001" << endl;
  for (int i = 4; i < 32; i++)
  {
    cout << i << ":" << endl;
  }

  cout << "TESTING GET BUFFER: " << endl;
  if (b.getBuffer(3) == "10101010100100001001001")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "BUFFER LINE: " << b.getBuffer(3) << endl;
  }

  cout << "TESTING GET FILE: " << endl;
  if (b.getFile() == "output.txt")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "OUTPUT FILE: " << b.getFile() << endl;
  }

  cout << "TESTING SET FILE: " << endl;
  b.setFile("test.txt");
  if (b.getFile() == "test.txt")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "OUTPUT FILE: " << b.getFile() << endl;
  }

  cout << "TESTING WRITING FILE: " << endl;
  b.writeBuffer();
  cout << "CHECK FILE" << endl;
  cout << "SHOULD EQUAL: " << endl;
  cout << "" << endl
       << "" << endl
       << "" << endl
       << "10101010100100001001001" << endl;
  for (int i = 4; i < 32; i++)
  {
    cout << endl;
  }
  cout << "---- CODE BUFFER TESTING COMPLETE ----" << endl
       << endl;
}

/**
 * @brief Tests the functions related to the assembler
 *
 */
void testAssembler()
{

  cout << "---- ASSEMBLER TESTING ----" << endl
       << endl;

  cout << "TESTING BLANK CONSTRUCTOR: " << endl;
  Assembler a;
  if (a.getInputFile() == "assembly.txt")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "FILE INPUT: " << a.getInputFile() << endl;
  }

  cout << "TESTING GET MEMORY LOCATION: " << endl;
  if (a.getMemoryLocation() == 0)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "MEMORY LOCATION: " << a.getMemoryLocation() << endl;
  }

  cout << "TESTING SET MEMORY LOCATION: " << endl;

  a.setMemoryLocation(5);
  if (a.getMemoryLocation() == 5)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "MEMORY LOCATION: " << a.getMemoryLocation() << endl;
  }

  cout << "TESTING GET INPUT FILE: " << endl;
  if (a.getInputFile() == "assembly.txt")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "INPUT FILE: " << a.getInputFile() << endl;
  }

  cout << "TESTING SET INPUT FILE: " << endl;

  a.setInputFile("test.txt");
  if (a.getInputFile() == "test.txt")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED:" << endl;
    cout << "INPUT FILE: " << a.getInputFile() << endl;
  }

  cout << "TESTING BINARY CONVERTER: " << endl;

  // TODO: Add more cases
  cout << "CASE 1: CONVERTING 1 TO BINARY" << endl;
  if (a.intToBinary(1) == "1")
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "CONVERTING 1 TO BINARY GIVES: " << a.intToBinary(1) << endl;
  }

  cout << "TESTING WORD CATEGORISATION: " << endl;

  cout << "CASE 1: COMMENT" << endl;
  if (a.categoriseWord(";comment") == -1)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "CATEGORY: " << a.categoriseWord("; This is a comment") << endl;
  }

  cout << "CASE 2: LABEL" << endl;
  if (a.categoriseWord("LABEL:") == 0)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "CATEGORY: " << a.categoriseWord("LABEL:") << endl;
  }

  cout << "CASE 3: INSTRUCTION" << endl;

  a.initialiseInstructionSet();

  if (a.categoriseWord("JMP") == 1)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "CATEGORY: " << a.categoriseWord("JMP") << endl;
  }

  cout << "CASE 3.1: VAR" << endl;
  if (a.categoriseWord("VAR") == 1)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "CATEGORY: " << a.categoriseWord("VAR") << endl;
  }

  cout << "CASE 3.1: OPERAND" << endl;
  if (a.categoriseWord("VARIABLE") == 2)
  {
    cout << "TEST PASSED" << endl;
  }
  else
  {
    cout << "TEST FAILED: " << endl;
    cout << "CATEGORY: " << a.categoriseWord("VARIABLE") << endl;
  }

  cout << "TESTING ASSEMBLER: " << endl;

  cout << "CASE 1: EXAMPLE CODE" << endl;
  Assembler b;
  b.setInputFile("BabyTest1-Assembler.txt");
  b.start();

  cout << "OUTPUT FILE SHOULD BE: " << endl;
  cout << "00000000000000000000000000000000" << endl;
  cout << "11100000000000100000000000000000" << endl;
  cout << "00010000000000010000000000000000" << endl;
  cout << "10010000000001100000000000000000" << endl;
  cout << "10010000000000100000000000000000" << endl;
  cout << "10010000000001100000000000000000" << endl;
  cout << "00000000000001110000000000000000" << endl;
  cout << "10000000001000000000000000000000" << endl;
  cout << "10110110010000000000000000000000" << endl;
  cout << "00000000000000000000000000000000" << endl;

  cout << "VERIFY OUTPUT" << endl;

  cout << "---- ASSEMBLER TESTING COMPLETE ----" << endl;
}
