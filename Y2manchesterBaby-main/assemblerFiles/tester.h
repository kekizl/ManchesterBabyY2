/**
 * @file tester.h
 * @author Conor Kelly, Stacy Achieng Onyango, Harry Inglis
 * @brief Function declarations for the assembler tester
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef TESTER_H
#define TESTER_H

using namespace std;

/**
 * ### INCLUDES ###
 */

#include <string>
#include <iostream>
#include "instructionSet.h"
#include "instruction.h"
#include "assembler.h"
#include "symbol.h"
#include "symbolTable.h"
#include "outputBuffer.h"

void testSymbols();
void testSymbolTable();
void testInstruction();
void testInstructionSet();
void testOutputBuffer();
void testAssembler();

#endif