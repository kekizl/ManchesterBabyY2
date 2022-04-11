/**
 * @file memoryLocations.h
 * @author David Topping, Christian Zlatanov, Mathew Gallahcher, Connor Kelly, Stacy Onyango, Harry Inglis
 * @brief header file for the memoryLocations.cpp file. Holds class definitions etc.
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef MEMORY_LOCATIONS_H
#define MEMORY_LOCATIONS_H

/**
 * ### INCLUDES ###
 */
#include <iostream>

/**
 * ### CLASS DEFINITIONS ###
 */

/**
 * @brief holds an indivual register with 32 bits
 *
 */
class Register
{

private:
    bool location[32];

public:
    Register();
    bool getLocation(int x) const;
    void setLocation(int n, bool pos);
    void setRegister(bool inputRegister[]);
    bool getRegister();

    friend std::ostream &operator<<(std::ostream &output, const Register &Reg);
};

/**
 * @brief store (main memory) 32 individual registers stored in array
 *
 */
class Store
{
private:
    Register *storeRegister;
    int storeSize;

public:
    Store();
    Store(int size);
    Register getRegister(int i);
    bool setRegiserLocation(int reg, int regLocation, bool pos);
    bool getRegisterLocation(int reg, int loc) const;
    friend std::ostream &operator<<(std::ostream &outupt, const Store &St);
};
#endif // MEMORY_LOCATIONS_H