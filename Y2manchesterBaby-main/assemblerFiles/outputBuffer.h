/**
 * @file outputBuffer.h
 * @author Conor Kelly, Stacy Achieng Onyango
 * @brief file with function & class declarations for the Output Buffer class
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#ifndef OUTPUT_BUFFER_H
#define OUTPUT_BUFFER_H

using namespace std;
/**
 * ### INCLUDES ###
 */
#include <iostream>
#include <string>
#include <fstream>

#include "bufferLine.h"
#include "utility.h"
/**
 * ### CLASS DEFINITIONS ###
 */

/**
 * @brief Stores a Instruction to be stored in the instruction table
 *
 */

class OutputBuffer
{
private:
  string outputFile;
  BufferLine *buffer;
  int currentSize;

  int updateBufferSize(int l);

public:
  OutputBuffer();
  OutputBuffer(string f);

  int setBufferLine(int l, string cmd);
  int setBufferLine(int l, string cmd, string op);
  int setBufferLineOperand(int l, string op);
  int setBufferLineValue(int l, int val);
  int setBufferLineName(int l, string name);

  BufferLine getBufferLine(int l) const;
  int setFile(string f);
  string getFile() const;
  int writeBuffer();

  friend ostream &operator<<(ostream &output, const OutputBuffer &ob);
};
#endif