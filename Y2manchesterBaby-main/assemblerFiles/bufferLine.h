/**
 * @file bufferLine.h
 * @author Conor Kelly, Stacy Achieng Onyango
 * @brief file with function & class declarations for the BufferLine
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#ifndef BUFFER_LINE_H
#define BUFFER_LINE_H

using namespace std;
/**
 * ### INCLUDES ###
 */
#include <iostream>
#include <string>

#include "utility.h"

/**
 * ### CLASS DEFINITIONS ###
 */

/**
 * @brief Stores one line of the OUtput Buffer
 *
 */

class BufferLine
{
private:
  string operand;
  string instructionBinary;
  string instructionName;
  int name;
  int value;

public:
  BufferLine();
  BufferLine(string op, string insBinary, string insName);

  string getOperand() const;
  string getInstructionBinary() const;
  string getInstructionName() const;
  int getInstructionValue() const;

  int setOperand(string op);
  int setInstructionBinary(string ins);
  int setInstructionName(string name);
  int setInstructionValue(int val);

  string asMachineCode() const;

  friend ostream &operator<<(ostream &output, const BufferLine &bl);
};

#endif