/**
 * @file utility.h
 * @author Conor Kelly, Stacy Achieng Onyango
 * @brief file with function declarations for utilities
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */

#ifndef UTILITY_H
#define UTILITY_H

using namespace std;
/**
 * ### INCLUDES ###
 */
#include <iostream>
#include <string>
#include "utility.h"

string intToBinary(int n);

/**
 * ### ERROR CODES ###
 */

/**
 * ### 100 - 199 ###
 * ### GENERAL ERRORS ###
 */

#define SUCCESS 100                 // Value returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER 101 // Value returned if an input parameter is invalid
#define MEMORY_ALLOCATION_ERROR 102 // Value returned if a memory allocation error occurs
#define INVALID_MENU_OPTION 103     // Value returned if the user selects an invalid menu option
#define FILE_IO_ERROR 104           // Value returned if a file IO operation failed
#define FILE_NOT_FOUND 105          // Value returned if a file cannot be found at that location

/**
 * ### 200-299 ###
 * ## ASSEMBLER ERRORS ###
 */

#define COMMENT 200     // Value returned if the word is a comment
#define LABEL 201       // Value returned if the word is a label
#define INSTRUCTION 202 // Value returned if the word is an instruction
#define OPERAND 203     // Value returned if the word is an operand

#define INPUT_FILE_NOT_FOUND 210  // Value returned if the input file is not found
#define OUTPUT_FILE_NOT_FOUND 211 // Value returned if the output file is not found

#define MULTIPLE_LABELS_FOUND 220       // Value returned if there are multiple labels on a line
#define MULTIPLE_INSTRUCTIONS_FOUND 221 // Value returned if there are multiple instructions on a line
#define MULTIPLE_OPERANDS_FOUND 222     // Value returned if there are multiple operands found on a line

#define NO_OPERAND_FOUND 230 // Value returned if there is no operand found and an operand is required

/**
 * ### 300-399 ###
 * ## SYMBOL TABLE ERRORS ###
 */

#define LABEL_ALREADY_EXISTS 300 // Value returned if there is already a label in the symbol table
#define LABEL_NOT_FOUND 301      // Value returned if there is no label in the symbol table

#define FAILED_TO_REHASH 310 // Value returned if the symbol table cannot be rehashed
#define FAILED_TO_INSERT 311 // Value returned if the symbol table cannot insert that label

#define HASH_NEGATIVE 320 // Value returned if the hash function returns a negative number

/**
 * ### 400-499 ###
 * ## BUFFER LINE ERRORS ###
 */

#define INVALID_INSTRUCTION_BINARY 400 // Value returned if the instruction binary is invalid
#define INVALID_OPERAND_BINARY 401     // Value returned if the operand binary is invalid
#define INVALID_INSTRUCTION_NAME 402   // Value returned if the instruction name is invalid
#define INVALID_INSTRUCTION_VALUE 403  // Value returned if the instruction value is invalid

/**
 * ### 500-599 ###
 * ## INSTRUCTION ERRORS ###
 */

/**
 * ### 600-699 ###
 * ## INSTRUCTION SET ERRORS ###
 */

#define CANNOT_INSERT_INSTRUCTION 600 // Value returned if the instruction cannot be inserted into the instruction set
#define INSTRUCTION_NOT_FOUND 601     // Value returned if the instruction cannot be found in the instruction set


/**
 * ### 700-799 ###
 * ## OUTPUT BUFFER ERRORS ###
 */

#define INVALID_MEMORY_LOCATION 701 // Value returned if the line number is invalid

/**
 * ### 800-899 ###
 * ## SMYBOL ERRORS ###
 */

#define INVALID_ADDRESS_LENGTH 801 // Value returned if the address length is invalid

#endif
