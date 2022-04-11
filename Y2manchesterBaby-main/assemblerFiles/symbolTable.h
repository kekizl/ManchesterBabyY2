/**
 * @file symbolTable.h
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief function and class declarations for the symbol table
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

using namespace std;
/**
 * ### INCLUDES ###
 */
#include <string>
#include <math.h>
#include <iostream>

#include "symbol.h"
#include "utility.h"
/**
 * ### CLASS DEFINITIONS ###
 */

/**
 * @brief A class representing the symbol table. It represents the symbols in a linear probing hash table
 *
 */
class SymbolTable
{
private:
  /**
   * @brief The max size of the symbol table
   *
   */
  int tablesize;

  /**
   * @brief The current size of the symbol table
   *
   */

  int currentSize;
  /**
   * @brief The table of symbols
   *
   */
  Symbol *table;

public:
  SymbolTable();
  SymbolTable(int size);
  ~SymbolTable();

  int reHash();
  int hashFunction(string l) const;
  int insert(string l, string a);
  int search(string l) const;
  int update(string l, string a);
  string lookup(string l) const;

  Symbol *getTable() const;
  int getTableSize() const;
  int getCurrentSize() const;

  friend ostream &operator<<(ostream &output, const SymbolTable &st);
};

#endif