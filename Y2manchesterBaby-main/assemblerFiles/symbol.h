/**
 * @file symbol.h
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief function and class declarations for the symbols in the symbol table
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

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
 * @brief Stores a symbol to be stored in the symbol table
 *
 */

class Symbol
{
private:
  /**
   * @brief The label of the symbol
   *
   */
  string label;

  /**
   * @brief The address of the symbol
   *
   */
  string address;

public:
  Symbol();
  Symbol(string a, string l);

  string getLabel();
  string getAddress();

  int setAddress(string a);

  friend ostream &operator<<(ostream &output, Symbol &s);
};

#endif