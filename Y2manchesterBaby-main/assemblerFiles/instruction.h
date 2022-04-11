/**
 * @file instruction.h
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief function and class declarations for the instructions in the instruction set
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

using namespace std;

/**
 * ### INCLUDES ###
 */

#include <string>
#include <iostream>

#include "utility.h"

/**
 * ### CLASS DEFINITIONS ###
 */

/**
 * @brief Stores a Instruction to be stored in the instruction table
 *
 */

class Instruction
{
private:
  /**
   * @brief The name of the instruction
   *
   */
  string name;

  /**
   * @brief The binary of the instruction
   *
   */
  string binary;

public:
  Instruction();
  Instruction(string n, string b);

  string getName() const;
  string getBinary() const;

  int setBinary(string b);

  friend ostream &operator<<(ostream &output, const Instruction &i);
};

#endif