/**
 * @file bufferLine.cpp
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief Logic of the BufferLine Class
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#include "bufferLine.h"

/**
 * @brief Construct a new Buffer Line object
 *
 */
BufferLine::BufferLine()
{
  operand = "00000";
  instructionBinary = "000";
  instructionName = "";
  value = 0;
}

/**
 * @brief Construct a new Buffer Line object
 *
 * @param op The operand of the buffer line
 * @param insBinary The instruction in binary of the buffer line
 * @param insName The instructions name of the buffer line
 */
BufferLine::BufferLine(string op, string insBinary, string insName)
{
  operand = op;
  instructionBinary = insBinary;
  instructionName = insName;
  value = 0;
}

/**
 * @brief Returns the Buffer Line's instruction binary
 *
 * @return string The instruction of the Buffer Line
 */
string BufferLine::getInstructionBinary() const
{
  return instructionBinary;
}

/**
 * @brief Returns the Buffer Line's operand
 *
 * @return string The operand of the Buffer Line
 */
string BufferLine::getOperand() const
{
  return operand;
}

/**
 * @brief Returns the Buffer Line's instruction name
 *
 * @return string The name of the buffer line instruction
 */

string BufferLine::getInstructionName() const
{
  return instructionName;
}

/**
 * @brief Returns the buffer lines instruction value
 *
 * @return int The value of the instruction
 */
int BufferLine::getInstructionValue() const
{
  return value;
}

/**
 * @brief Sets the Buffer Line's instruction binary
 *
 * @param ins The instruction binary of the buffer line
 * @return int Status of the function
 */
int BufferLine::setInstructionBinary(string ins)
{

  if (ins.length() != 3)
  {
    return INVALID_INSTRUCTION_BINARY;
  }
  instructionBinary = ins;

  return SUCCESS;
}

/**
 * @brief Sets the Buffer Line's operand
 *
 * @param op The operand of the buffer line
 * @return int Status of the function
 */
int BufferLine::setOperand(string op)
{

  if (op.length() != 5)
  {
    return INVALID_OPERAND_BINARY;
  }
  operand = op;

  return SUCCESS;
}

/**
 * @brief Sets the name of the Buffer Line's instruction
 *
 * @param name The name of the instruction
 * @return int Status of the function
 */
int BufferLine::setInstructionName(string name)
{

  if (name == "")
  {
    return INVALID_INSTRUCTION_NAME;
  }
  instructionName = name;
  return SUCCESS;
}

/**
 * @brief Sets the value of the Buffer Line's instruction
 *
 * @param val The avlue of the instruction
 * @return int Status of the function
 */
int BufferLine::setInstructionValue(int val)
{
  if (val < 0)
  {
    return INVALID_INSTRUCTION_VALUE;
  }
  value = val;
  return SUCCESS;
}

/**
 * @brief Returns the Buffer Line in the machine code format used in the ManchesterBaby
 *
 * @return string The machine code equivalent of the Buffer Line
 */
string BufferLine::asMachineCode() const
{
  if (instructionName != "VAR")
  {
    return operand + "00000000" + instructionBinary + "0000000000000000";
  }
  else
  {
    string machineCode = intToBinary(value);

    // Pad the machine code to 32 bits
    for (int i = machineCode.length(); i < 32; i++)
    {
      machineCode += "0";
    }

    return machineCode;
  }
}

/**
 * @brief Outputs the bufferline in a readable format
 *
 * @param output The output stream
 * @param bl The buffer line to output
 * @return ostream& The readable output stream
 */
ostream &
operator<<(ostream &output, const BufferLine &bl)
{

  output << bl.getInstructionBinary() << ":" << bl.getOperand() << endl;

  return output;
}