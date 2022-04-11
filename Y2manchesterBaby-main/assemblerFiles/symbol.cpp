/**
 * @file symbol.cpp
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief contains the logic for the symbols in the symbol table
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "symbol.h"

/**
 * @brief Construct a new Symbol object
 *
 */
Symbol::Symbol()
{
  label = "";
  address = "";
}

/**
 * @brief Construct a new Symbol object
 *
 * @param l The label of the Symbol
 * @param a The address of the Symbol
 */
Symbol::Symbol(string l, string a)
{
  label = l;
  address = a;
}

/**
 * @brief Gets the label for the symbol
 *
 * @return string The label of the symbol
 */

string Symbol::getLabel()
{
  return label;
}

/**
 * @brief Gets the address of the symbol
 *
 * @return string The address of the symbol
 */

string Symbol::getAddress()
{
  return address;
}

/**
 * @brief Sets the address of the symbol
 *
 * @param a The new address of the symbol
 *
 * @return int The status of the function
 */

int Symbol::setAddress(string a)
{
  if (a.length() != 5)
  {
    return INVALID_ADDRESS_LENGTH;
  }

  address = a;
  return SUCCESS;
}

/**
 * @brief Overloads the output operator to show the symbol's label and address
 *
 * @param output The output stream
 * @param s The symbol object to be output
 * @return ostream& The formatted output
 */
ostream &operator<<(ostream &output, Symbol &s)
{
  output << s.getLabel() << ":" << s.getAddress() << endl;
  return output;
}