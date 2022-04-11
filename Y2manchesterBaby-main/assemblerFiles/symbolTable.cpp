/**
 * @file symbolTable.cpp
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief contains the logic for the symbol table
 * @version 0.1
 * @date 2021-11-22
 *z
 * @copyright Copyright (c) 2021
 *
 */

#include "symbolTable.h"
#include "symbol.h"

/**
 * @brief Construct a new Symbol Table object
 *
 */
SymbolTable::SymbolTable()
{
  tablesize = 10;
  currentSize = 0;
  table = new Symbol[10];
}
/**
 * @brief Construct a new Symbol Table object
 *
 * @param size The size of the Symbol Table
 */
SymbolTable::SymbolTable(int size)
{
  tablesize = size;
  currentSize = 0;
  table = new Symbol[size];
}

/**
 * @brief Destroy the Symbol Table object
 *
 */
SymbolTable::~SymbolTable()
{
  delete[] table;
}

/**
 * @brief Rehashes the table and updates the stored symbol table
 *
 * @return int The status of the function
 */
int SymbolTable::reHash()
{

  Symbol *tmp = new Symbol[2 * tablesize];
  tablesize *= 2;
  for (int i = 0; i < tablesize / 2; i++)
  {

    try
    {
      // Get the preferred location for this label
      string currentLabel = table[i].getLabel();
      // If there is nothing in this position skip this position
      if (currentLabel == "")
      {
        continue;
      }
      int targetPos = hashFunction(table[i].getLabel());

      // Loop up to the entire table size
      for (int j = 0; j < tablesize; j++)
      {
        // If there is a valid space (empty slot or deleted slot) insert a new Symbol at that location
        if (tmp[(targetPos + j) % tablesize].getLabel() == "D" || tmp[(targetPos + j) % tablesize].getLabel() == "")
        {
          tmp[(targetPos + j) % tablesize] = Symbol(table[i].getLabel(), table[i].getAddress());
          break;
        }
      }
    }

    catch (const std::exception &e)
    {
      return FAILED_TO_REHASH;
    }
  }
  delete[] table;
  table = tmp;
  return SUCCESS;
}

/**
 * @brief Hashes the label and returns the position in the Symbol Table.
 *
 * @param l
 * @return int The position in the Symbol Table or an error code
 */
int SymbolTable::hashFunction(string l) const
{

  // Check if a label is passed in
  if (l == "")
  {
    return INVALID_INPUT_PARAMETER;
  }

  // Initialise the numbers to be used for the hash function
  const int p = 31;
  const int T = tablesize;

  // Inititalise a variable to be used to store the total of the hash function
  unsigned long int total = 0;

  // Store the length of the label passed into the function
  const int N = l.length();

  for (int i = 0; i <= N; i++)
  {
    /*
        Add to the total with the function of:
        Character @ (Length - i) * p ^ (i)
    */
    total += int(l[N - i]) * pow(p, i);
  }

  if (total <= 0)
  {
    return HASH_NEGATIVE;
  }

  // When all of the characters have been added together divide it by T and the result of the hash function is that remainder
  return total % T;
}

/**
 * @brief Inserts a Symbol to the Symbol table
 *
 * @param l The label of the Symbol
 * @param a The address of the Symbol
 * @return int The status of the function
 */
int SymbolTable::insert(string l, string a)
{

  if (l == "" || a == "")
  {
    return INVALID_INPUT_PARAMETER;
  }

  // If the symbol table is too occupied rehash the table

  if (currentSize / tablesize > 0.5)
  {
    int reHashStatus = reHash();
    if (reHashStatus == FAILED_TO_REHASH)
    {
      return FAILED_TO_REHASH;
    }
  }
  try
  {
    // Get the preferred location for this label
    int targetPos = hashFunction(l);
    // Loop up to the entire table size
    for (int i = 0; i < tablesize; i++)
    {
      // If there is already a node with this label return false
      if (table[(targetPos + i) % tablesize].getLabel() == l)
      {
        return LABEL_ALREADY_EXISTS;
      }
      // If there is a valid space (empty slot or deleted slot) insert a new Symbol at that location
      if (table[(targetPos + i) % tablesize].getLabel() == "D" || table[(targetPos + i) % tablesize].getLabel() == "")
      {
        table[(targetPos + i) % tablesize] = Symbol(l, a);
        currentSize++;
        return SUCCESS;
      }
    }
  }

  catch (const std::exception &e)
  {
    return FAILED_TO_INSERT;
  }

  return SUCCESS;
}

/**
 * @brief Returns the position of a label in the SymbolTable.
 *
 * @param l The label of the Symbol to search for
 * @return int The position of the label in the SymbolTable.
 */
int SymbolTable::search(string l) const
{
  // Make sure a valid label is passed in
  if (l == "")
  {
    return INVALID_INPUT_PARAMETER;
  }

  try
  {
    // Get the preferred location for this label
    int targetPos = hashFunction(l);
    // Loop up to the entire table size
    for (int i = 0; i < tablesize; i++)
    {
      // If the current slot is the key return true
      if (table[(targetPos + i) % tablesize].getLabel() == l)
      {
        return (targetPos + i) % tablesize;
      }

      // If you reach an empty slot the key is not in the table
      if (table[(targetPos + i) % tablesize].getLabel() == "")
      {
        return -1;
      }
    }
  }
  catch (const std::exception &e)
  {
    return false;
  }

  return -1;
}

/**
 * @brief Updates the address of the label. Returns false if label does not exist or another error occurs
 *
 * @param l The label of the Symbol to update
 * @param a The new address for the Symbol
 * @return int The status of the function
 */
int SymbolTable::update(string l, string a)
{
  // Make sure the label and address are valid
  if (l == "" || a == "")
  {
    return INVALID_INPUT_PARAMETER;
  }

  const int result = search(l);
  if (result == LABEL_NOT_FOUND)
  {
    return LABEL_NOT_FOUND;
  }
  table[result].setAddress(a);
  return SUCCESS;
}

/**
 * @brief Returns the address of the Symbol with the given label
 *
 * @param l The label of the Symbol to get the address of
 * @return string The address of the Symbol
 */

string SymbolTable::lookup(string l) const
{
  // Make sure that the label is valid
  if (l == "")
  {
    return "";
  }

  const int result = search(l);
  if (result == -1)
  {
    return "";
  }
  return table[result].getAddress();
}

/**
 * @brief Returns the table of symbols of the object
 *
 * @return Symbol* A pointer to the Symbol Table table
 */
Symbol *SymbolTable::getTable() const
{
  return table;
}

/**
 * @brief Returns the max table size of the symbol table
 *
 * @return int The max table size of the symbol table
 */
int SymbolTable::getTableSize() const
{
  return tablesize;
}

/**
 * @brief Returns the current size of the symbol table
 *
 * @return int The current size of the symbol table
 */
int SymbolTable::getCurrentSize() const
{
  return currentSize;
}
/**
 * @brief Overloads the output operator to display the Symbol Table for debugging
 *
 * @param output The output stream
 * @param st The symbol table
 * @return ostream& The final output
 */
ostream &operator<<(ostream &output, const SymbolTable &st)
{
  for (int i = 0; i < st.getTableSize(); i++)
  {
    output << i << ":" << st.getTable()[i].getLabel() << ":" << st.getTable()[i].getAddress() << endl;
  }
  return output;
}