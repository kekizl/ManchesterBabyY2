/**
 * @file instructionSet.cpp
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief contains the logic for the instruction set
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "instructionSet.h"

/**
 * @brief Construct a new Instruction Set object
 *
 */
InstructionSet::InstructionSet()
{
  tablesize = 8;
  currentSize = 0;
  table = new Instruction[8];
}

/**
 * @brief Destroy the Instruction Set object
 *
 */
InstructionSet::~InstructionSet()
{
  delete[] table;
}

/**
 * @brief Inserts an Instruction into the Instruction Set
 *
 * @param n The name of the Instruction
 * @param b The binary of the Instruction
 * @return int The status of the function
 */
int InstructionSet::insert(string n, string b)
{

  // Make sure that a name and binary value are provided
  if (n == "")
  {
    return INVALID_INSTRUCTION_NAME;
  }

  if (b.length() != 3)
  {
    return INVALID_INSTRUCTION_BINARY;
  }

  try
  {
    // Try to add the Instruction to the Instruction Set
    table[currentSize] = Instruction(n, b);
    currentSize++;
  }

  // if theres an error return false
  catch (const std::exception &e)
  {
    return CANNOT_INSERT_INSTRUCTION;
  }

  return SUCCESS;
}

/**
 * @brief Returns the position of a name in the Instruction Set.
 * @param n The name of the Instruction to search for
 * @return int The position of the name in the Instruction Set.
 */
int InstructionSet::search(string n) const
{
  // Make sure a valid name is passed in
  if (n == "")
  {
    return INVALID_INSTRUCTION_NAME;
  }

  int counter = 0;
  while (counter < currentSize)
  {
    if (table[counter].getName() == n)
    {
      return counter;
    }
    counter++;
  }

  return INSTRUCTION_NOT_FOUND;
}

/**
 * @brief Returns the binary of the Instruction with the given name
 *
 * @param n The name of the Instruction to get the binary of
 * @return string The binary of the Instruction
 */

string InstructionSet::lookup(string n) const
{
  // Make sure that the name is valid
  if (n == "")
  {
    return "";
  }

  const int result = search(n);
  if (result == -1)
  {
    return "";
  }
  return table[result].getBinary();
}
/**
 * @brief Returns the table of the instruction set
 *
 * @return Instruction* The table of instructions
 */
Instruction *InstructionSet::getTable() const
{
  return table;
}

/**
 * @brief Returns the max size of the instruction set table
 *
 * @return int The maximum size of the instruction set table
 */
int InstructionSet::getTableSize() const
{
  return tablesize;
}

/**
 * @brief Returns the current size of the instruction set table
 *
 * @return int The current size of the instruction set table
 */
int InstructionSet::getCurrentSize() const
{
  return currentSize;
}
/**
 * @brief Overloads the output operator to display the Instruction Set
 *
 * @param output The output stream
 * @param is The Instruction Set
 * @return ostream& The final output
 */
ostream &operator<<(ostream &output, const InstructionSet &is)
{
  for (int i = 0; i < is.getTableSize(); i++)
  {
    output << i << ":" << is.getTable()[i].getName() << ":" << is.getTable()[i].getBinary() << endl;
  }
  return output;
}