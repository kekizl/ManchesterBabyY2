/**
 * @file outputBuffer.cpp
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief Logic of the Output Buffer Class
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#include "outputBuffer.h"

/**
 * @brief Construct a new Code Buffer object
 *
 */
OutputBuffer::OutputBuffer()
{
  outputFile = "machineCode.txt";
  buffer = new BufferLine[32];
  currentSize = 0;
}
/**
 * @brief Construct a new Code Buffer object
 *
 * @param f The name of the output file
 */
OutputBuffer::OutputBuffer(string f)
{
  outputFile = f;
  buffer = new BufferLine[32];
  currentSize = 0;
}

/**
 * @brief Set the buffer at line l to the command and operand (optional)
 *
 * @param l The line to change in the buffer
 * @param ins The instruction to set the buffer line to in binary
 * @return int Status of the function
 */
int OutputBuffer::setBufferLine(int l, string ins)
{

  // Make sure that the line number is a positive number and not greater than 32
  if (l < 0 || l > 32)
  {
    return INVALID_MEMORY_LOCATION;
  }

  // Make sure that the instruction binary is 3 characters long
  if (ins.length() != 3)
  {
    return INVALID_INSTRUCTION_BINARY;
  }

  // Update the buffer size (if neccessary)
  int updateStatus = updateBufferSize(l);
  if (updateStatus != SUCCESS)
  {
    // If the buffer size has not updated succesfully return the error code
    return updateStatus;
  }

  int insBinStatus = buffer[l].setInstructionBinary(ins);
  if (insBinStatus != SUCCESS)
  {
    return insBinStatus;
  }

  return SUCCESS;
}

/**
 * @brief Set the buffer at line l to the command and operand (optional)
 *
 * @param l The line to change in the buffer
 * @param ins The instruction to set the buffer line to in binary
 * @param op The operand to set the buffer line to in binary (optional)
 * @return int Status of the function
 */

int OutputBuffer::setBufferLine(int l, string ins, string op)
{

  // Make sure that the line number is a positive number and not greater than 32
  if (l < 0 || l > 32)
  {
    return INVALID_MEMORY_LOCATION;
  }

  // Make sure that the instruction binary is 3 characters long
  if (ins.length() != 3)
  {
    return INVALID_INSTRUCTION_BINARY;
  }

  // Make sure that the operand binary is 5 characters long
  if (op.length() != 5)
  {
    return INVALID_OPERAND_BINARY;
  }

  // Update the buffer size (if neccessary)
  int updateStatus = updateBufferSize(l);
  if (updateStatus != SUCCESS)
  {
    // If the buffer size has not updated succesfully return the error code
    return updateStatus;
  }

  // Update the instruction
  int insBinStatus = buffer[l].setInstructionBinary(ins);
  if (insBinStatus != SUCCESS)
  {
    // If the instruction has not updated successfully return the error code
    return insBinStatus;
  }

  // Update the operand
  int opBinStatus = buffer[l].setOperand(op);
  if (opBinStatus != SUCCESS)
  {
    // If the operand has not updated succesfully return the error code
    return opBinStatus;
  }

  return SUCCESS;
}

/**
 * @brief Sets the buffer line l operand to the string provided
 *
 * @param l The line to change in the buffer
 * @param op The operand to set the buffer line to in binary
 * @return int Status of the function
 */
int OutputBuffer::setBufferLineOperand(int l, string op)
{

  // Make sure that the line number is a positive number and not greater than 32
  if (l < 0 || l > 32)
  {
    return INVALID_MEMORY_LOCATION;
  }

  // Make sure that the operand binary is 5 characters long
  if (op.length() != 5)
  {
    return INVALID_OPERAND_BINARY;
  }

  // Update the buffer size (if neccessary)
  int updateStatus = updateBufferSize(l);
  if (updateStatus != SUCCESS)
  {
    // If the buffer size has not updated succesfully return the error code
    return updateStatus;
  }

  // Update the operand
  int opBinStatus = buffer[l].setOperand(op);
  if (opBinStatus != SUCCESS)
  {
    // If the operand has not updated succesfully return the error code
    return opBinStatus;
  }

  return SUCCESS;
}

int OutputBuffer::setBufferLineValue(int l, int val)
{

  // Make sure that the line number is a positive number and not greater than 32
  if (l < 0 || l > 32)
  {
    return INVALID_MEMORY_LOCATION;
  }

  // Make sure that the instruction value is a positive number
  if (val < 0)
  {
    return INVALID_INSTRUCTION_VALUE;
  }

  // Update the buffer size (if neccessary)
  int updateStatus = updateBufferSize(l);
  if (updateStatus != SUCCESS)
  {
    // If the buffer size has not updated succesfully return the error code
    return updateStatus;
  }

  // Update the instruction value
  int insValStatus = buffer[l].setInstructionValue(val);
  if (insValStatus != SUCCESS)
  {
    // If the instruction value has not updated successfully return the error code
    return insValStatus;
  }

  return SUCCESS;
}

int OutputBuffer::setBufferLineName(int l, string name)
{

  // Make sure that the line number is a positive number and not greater than 32
  if (l < 0 || l > 32)
  {
    return INVALID_MEMORY_LOCATION;
  }
  // Update the buffer size (if neccessary)
  int updateStatus = updateBufferSize(l);
  if (updateStatus != SUCCESS)
  {
    // If the buffer size has not updated succesfully return the error code
    return updateStatus;
  }

  // Update the instruction name
  int insNameStatus = buffer[l].setInstructionName(name);
  if (insNameStatus != SUCCESS)
  {
    // If the instruction name has not updated successfully return the error code
    return insNameStatus;
  }

  return SUCCESS;
}
/**
 * @brief Gets the Buffer Line at line l
 *
 * @param l The line to get the machine code of
 * @return BufferLine The line of the Buffer at l
 */
BufferLine OutputBuffer::getBufferLine(int l) const
{

  return buffer[l];
}
/**
 * @brief Sets the output file of the code buffer
 *
 * @param f The path to the desired output file
 * @return int A status code relating to the function, -1 represents an error
 */
int OutputBuffer::setFile(string f)
{

  // Validate that f is a string that could lead to a file
  if (f == "")
  {
    return FILE_NOT_FOUND;
  }

  outputFile = f;
  return SUCCESS;
}
/**
 * @brief Gets the output file for the code buffer
 *
 * @return string The current output file for the code buffer
 */
string OutputBuffer::getFile() const
{
  return outputFile;
}

/**
 * @brief Writes the output buffer to the output file
 *
 * @return int Status of the function
 */
int OutputBuffer::writeBuffer()
{
  ofstream writer(outputFile);
  if (!writer)
  {
    return FILE_IO_ERROR;
  }

  for (int i = 0; i < currentSize + 1; i++)
  {
    writer << buffer[i].asMachineCode() << endl;
  }
  writer.close();

  return SUCCESS;
}

/**
 * @brief Tests to see if the buffer needs to be expanded
 *
 * @param l The current line number of the buffer to be updated
 * @return int Status of the function
 */
int OutputBuffer::updateBufferSize(int l)
{

  if (l < 0)
  {
    return INVALID_MEMORY_LOCATION;
  }

  // If the line is larger than the current buffer set the currentbuffer to that line
  if (l > currentSize)
  {
    currentSize = l;
  }

  return SUCCESS;
}

ostream &
operator<<(ostream &output, const OutputBuffer &ob)
{

  for (int i = 0; i < 32; i++)
  {
    BufferLine currentLine = ob.getBufferLine(i);
    string machineCode = currentLine.asMachineCode();
    output << i << ":" << machineCode << endl;
  }
  return output;
}
