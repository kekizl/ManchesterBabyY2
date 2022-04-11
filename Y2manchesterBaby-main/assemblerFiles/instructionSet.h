/**
 * @file instructionSet.h
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief function and class declarations for the Instruction Set
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

using namespace std;
/**
 * ### INCLUDES ###
 */
#include <string>
#include <math.h>
#include <iostream>

#include "instruction.h"
/**
 * ### CLASS DEFINITIONS ###
 */

/**
 * @brief A class representing the instruction. It represents the instructions in a linear probing hash table
 *
 */
class InstructionSet
{
private:
  /**
   * @brief The size of the instruction set
   *
   */
  int tablesize;

  /**
   * @brief The current size of the instruction set
   *
   */
  int currentSize;

  /**
   * @brief The table of instructions
   *
   */
  Instruction *table;

public:
  InstructionSet();
  ~InstructionSet();

  int insert(string n, string b);
  int search(string n) const;
  string lookup(string n) const;

  Instruction *getTable() const;
  int getTableSize() const;
  int getCurrentSize() const;

  friend ostream &operator<<(ostream &output, const InstructionSet &is);
};
#endif