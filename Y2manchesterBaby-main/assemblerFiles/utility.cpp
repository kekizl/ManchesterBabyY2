/**
 * @file utility.cpp
 * @author Conor Kelly, Stacy Achieng Onyango
 * @brief file with function for utilitys
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#include "utility.h"

/**
 * @brief Converts an integer into a big-endian binary number
 *
 * @param n The integer to be converted
 * @return string The big-endian binary representation, "ERROR" means an error occured
 */
string intToBinary(int n)
{
  // Make sure that n can be converted to an integer
  if (n < 0)
  {
    return "ERROR";
  }

  // Handle 0 edge-case
  if (n == 0)
  {
    return "0";
  }
  string result = "";
  while (n > 0)
  {
    result += to_string(n % 2);
    n = n / 2;
  }

  return result;
}