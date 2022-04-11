/**
 * @file manchesterBaby.h
 * @author David Topping, Christian Zlatanov, Mathew Gallahcher
 * @brief file with function declarations for main.cpp
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 */
#ifndef MANCHESTER_BABY_H
#define MANCHESTER_BABY_H

/**
 * ### INCLUDES ###
 */
#include <iostream>
#include <bitset>
#include <bits/stdc++.h>
#include "memoryLocations.h"
using namespace std;

/**
 * @brief Runs the manchester baby simulator
 *
 * @param theStore
 */
void manchesterBabySimulator(Store *theStore);

/**
 * @brief Reads in the machine code text file and puts all instructions in the store
 *
 * @param machineCode
 */
void readInMachineCode(Store *theStore);

/**
 * @brief Increments a register by one
 *
 * @param CI
 */
void incrementRegister(Register *CI);

/**
 * @brief this method increments a bitset by one, credit is given for inspiration to this function
 *
 * @author https://stackoverflow.com/questions/16761472/how-can-i-increment-stdbitset
 * @tparam N
 * @param in
 * @return std::bitset<N>
 */
template <size_t N>
std::bitset<N> increment(bitset<N> in);

/**
 * @brief Fetches the PI from the store based on the PI
 *
 * @param CI
 * @param PI
 * @param theStore
 */
void fetch(Register *CI, Register *PI, Store *theStore);

/**
 * @brief wrapper function to decode the operand and the opcode
 *
 * @param CI
 */
void decode(Register *CI, string *opcode, int *operand);

/**
 * @brief decode the operand
 *
 * @param register
 * @return operand
 */
int decodeOperand(Register *PI);

/**
 * @brief decode the instruction
 *
 * @param register
 * @return instruction value
 */
string decodeOpcode(Register *PI);

/**
 * @brief Executing the PI
 *
 * @param opcode
 * @param operand
 * @param CI
 * @param PI
 * @param Accumulator
 */
void execute(string *opcode, int *operand, Register *CI, Register *PI, Register *Accumulator, Store *theStore);

/**
 * @brief Helper function prints all the memory locations
 *
 * @param CI
 * @param PI
 * @param Accumulator
 * @param theStore
 */
void printMemoryLocations(Register *CI, Register *PI, Register *Accumulator, Store *theStore);

#endif // MANCHESTER_BABY_H