/**
 * @file main.cpp
 * @author David Topping, Christian Zlatanov, Mathew Gallahcher
 * @brief Contains all the functions for the manchester baby's fetch-execute cycle
 * @version 0.1
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
#include <cstdint>
#include "manchesterBaby.h"
#include "memoryLocations.h"
using namespace std;

/**
 * @brief Runs the manchester baby simulator
 *
 * @param theStore
 */
void manchesterBabySimulator(Store *theStore)
{
    // initialise local variables
    bool finished = false;
    int iteration = 1;

    // init opcode and operand
    int operand;
    string opcode;

    // declare memory locations
    Register CI;
    Register PI;
    Register Accumulator;

    // reading in the machine code
    readInMachineCode(theStore);

    // running the fetch execute cycle
    while (finished != true)
    {
        // Increment the CI REGISTER
        incrementRegister(&CI);

        // 2. Fetch
        fetch(&CI, &PI, theStore);

        // 3. Decode opcode and operand
        decode(&PI, &opcode, &operand);

        // 4. Execute.
        execute(&opcode, &operand, &CI, &PI, &Accumulator, theStore);

        // waiting for key pres to continue fetch execute cycle
        if (iteration != 1)
        {
            cout << "\nPress return to run to the next fetch-execute cycle\n"
                 << endl;
        }
        getchar();

        printMemoryLocations(&CI, &PI, &Accumulator, theStore);

        if (opcode == "STP")
        {
            finished = true;
        }

        iteration++;
    }
}

/**
 * @brief Reads in the machine code text file and stores it in a vector of registers
 *
 * @param machineCode
 */
void readInMachineCode(Store *theStore)
{

    string line;
    int storeReg = 0;

    // Read from the text file
    ifstream MyReadFile("manchesterBabyFiles/BabyTest1-MC.txt");

    // Read the file line by line and store in the store
    while (getline(MyReadFile, line))
    {
        for (int i = 0; i < 32; i++)
        {

            if (line[i] == '0')
            {
                theStore->setRegiserLocation(storeReg, i, 0);
            }
            else if (line[i] == '1')
            {
                theStore->setRegiserLocation(storeReg, i, 1);
            }
        }
        storeReg++;
    }

    MyReadFile.close();
}

/**
 * @brief Increments a register by one
 *
 * @param CI
 */
void incrementRegister(Register *CI)
{
    // init temp bitset
    bitset<32> ciBitset;

    // copying the CI register into the bitset
    for (int i = 0; i < 32; i++)
    {
        if (CI->getLocation(i) == 1)
        {
            ciBitset[i] = 1;
        }
        else
        {
            ciBitset[i] = 0;
        }
    }

    // helper function to increment the biset
    ciBitset = increment(ciBitset);

    // copying the bitset into the CI register
    string ciStr = ciBitset.to_string();
    for (int i = 0; i < 32; i++)
    {
        if (ciStr[31 - i] == '1')
        {
            CI->setLocation(i, 1);
        }
        else
        {
            CI->setLocation(i, 0);
        }
    }
}

/**
 * @brief this method increments a bitset by one, credit is given for inspiration to this function
 *
 * @author https://stackoverflow.com/questions/16761472/how-can-i-increment-stdbitset
 * @tparam N
 * @param in
 * @return std::bitset<N>
 */
template <size_t N>
std::bitset<N> increment(std::bitset<N> in)
{
    //  add 1 to each value, and if it was 1 already, carry the 1 to the next.
    for (size_t i = 0; i < N; ++i)
    {
        if (in[i] == 0)
        { // There will be no carry
            in[i] = 1;
            break;
        }
        in[i] = 0; // This entry was 1; set to zero and carry the 1
    }
    return in;
}

/**
 * @brief Fetches the PI from the store based on the PI
 *
 * @param CI
 * @param PI
 * @param theStore
 */
void fetch(Register *CI, Register *PI, Store *theStore)
{
    // convert the CI to an int
    int storeLocation = 0;

    for (int i = 0; i < 32; i++)
    {
        if (CI->getLocation(i) == 1)
        {
            storeLocation += pow(2, i);
        }
    }

    // get the array register from the store location based on the CI
    bool tempPi[32];

    for (int i = 0; i < 32; i++)
    {
        tempPi[i] = theStore->getRegisterLocation((storeLocation), i);
    }

    // put the instruction from the store into the PI
    for (int i = 0; i < 32; i++)
    {
        PI->setLocation(i, tempPi[i]);
    }
}

/**
 * @brief wrapper function to decode the operand and the opcode
 *
 * @param CI
 */
void decode(Register *CI, string *opcode, int *operand)
{
    // storing the opcode and operand in the pointers'variable
    *operand = decodeOperand(CI);
    *opcode = decodeOpcode(CI);
}

/**
 * @brief decode the operand
 *
 * @param register
 * @return operand
 */
int decodeOperand(Register *PI)
{
    int operand = 0;

    for (int j = 0; j < 5; j++)
    {
        // computes MyNum by iterating through the register
        operand += PI->getLocation(j) * pow(2, j);
    }

    return operand;
}

/**
 * @brief decode the instruction
 *
 * @param register
 * @return instruction value
 */
string decodeOpcode(Register *PI)
{
    // getting the opcode from the 13th,14th,15th position of the present instruction register
    bool a = PI->getLocation(13);
    bool b = PI->getLocation(14);
    bool c = PI->getLocation(15);

    // compares bool code and returns
    if (a == 0 && b == 0 && c == 0)
    {
        return "JMP";
    }
    if (a == 1 && b == 0 && c == 0)
    {
        return "JRP";
    }

    if (a == 0 && b == 1 && c == 0)
    {
        return "LDN";
    }

    if (a == 1 && b == 1 && c == 0)
    {
        return "STO";
    }

    if (a == 0 && b == 0 && c == 1)
    {
        return "SUB";
    }

    if (a == 1 && b == 0 && c == 1)
    {
        return "SUB";
    }
    if (a == 0 && b == 1 && c == 1)
    {
        return "CMP";
    }
    if (a == 1 && b == 1 && c == 1)
    {
        return "STP";
    }

    // error code if failure
    return "ERR";
}

/**
 * @brief Executing the PI
 *
 * @param opcode
 * @param operand
 * @param CI
 * @param PI
 * @param Accumulator
 */
void execute(string *opcode, int *operand, Register *CI, Register *PI, Register *Accumulator, Store *theStore)
{

    // indirect jump.
    if (*opcode == "JMP")
    {
        // integer holding the CI value
        int CIcount = 0;

        // Getting the decimal value of CI
        for (int i = 0; i < 32; i++)
        {
            if (CI->getLocation(i) == 1)
            {
                CIcount += pow(2, i);
            }
        }

        // creating a temp register that is a copy of the register that the operand points to.
        bool memory[32];

        // decimal value of the aformentioned array
        int memoryInt = 0;

        // copying the register to the temp register
        for (int i = 0; i < 32; i++)
        {
            memory[i] = theStore->getRegisterLocation((*operand), i);
        }

        // if the mamory value is negative
        if (memory[31] == true)
        {
            // flip the bits
            bool flip[32];
            for (int i = 0; i < 32; i++)
            {
                char a = memory[i];
                if (a == '0')
                {
                    flip[i] = 1;
                }
                else
                {
                    flip[i] = 0;
                }
            }
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (flip[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }
            // add one and negate
            memoryInt = -(memoryInt + 1);
        }

        // if the value is positive
        if (memory[32] == false)
        {
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (memory[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }
        }

        // Copying the new array to the CI
        bool NewCIArray[32];
        for (int i = 0; i < 32; i++)
        {
            int mask = 1u << (32 - 1 - i);
            NewCIArray[i] = (memoryInt & mask) ? true : false;
            CI->setLocation(i, NewCIArray[i]);
        }
    }

    // relative jump
    if (*opcode == "JRP")
    {
        // Integer variable holding the decimal value of the CI
        int CIcount = 0;

        // getting the decimal value of CI
        for (int i = 0; i < 32; i++)
        {
            if (CI->getLocation(i) == 1)
            {
                CIcount += pow(2, i);
            }
        }

        // temp variable holding a copy of the array that the operand points to
        bool memory[32];
        // temp variable holding the decimal value of the array
        int memoryInt = 0;

        // copying the register to the temp array
        for (int i = 0; i < 32; i++)
        {
            memory[i] = theStore->getRegisterLocation((*operand), i);
        }

        // if the value is negative
        if (memory[31] == true)
        {
            // flip the bits
            bool flip[32];
            for (int i = 0; i < 32; i++)
            {
                char a = memory[i];
                if (a == '0')
                {
                    flip[i] = 1;
                }
                else
                {
                    flip[i] = 0;
                }
            }
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (flip[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }
            // add one and negate
            memoryInt = -(memoryInt + 1);
        }

        // if the array is false
        if (memory[32] == false)
        {
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (memory[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }
        }
        // add the CI to the array value
        int NewCI = CIcount + memoryInt;
        // change the CI to the new value
        bool NewCIArray[32];
        for (int i = 0; i < 32; i++)
        {
            int mask = 1u << (32 - 1 - i);
            NewCIArray[i] = (NewCI & mask) ? 1 : 0;
            CI->setLocation(i, NewCIArray[i]);
        }
    }

    // Negative Load
    if (*opcode == "LDN")
    {
        // temp array holding the register that the operand points to
        bool load[32];

        // copying the register to the temp array
        for (int i = 0; i < 32; i++)
        {
            load[i] = theStore->getRegisterLocation((*operand), i);
        }

        // temp variable holding the flipped version of the load array
        bool flip[32];

        // if the number is negative
        if (load[31] == true)
        {
            // flip the bits
            for (int i = 0; i < 32; i++)
            {
                if (load[i] == false)
                {
                    flip[i] = true;
                }
                else
                {
                    flip[i] = false;
                }
            }
            // copy the flip array to the accumulator
            for (int i = 0; i < 32; i++)
            {
                Accumulator->setLocation(i, flip[i]);
            }
            // add one to the accumulator
            incrementRegister(Accumulator);
        }
        // if the value is positive
        if (load[31] == false)
        {
            // getting the decimal value of the array
            int storeLocation = 0;

            for (int i = 0; i < 32; i++)
            {
                if (load[i] == 1)
                {
                    storeLocation += pow(2, i);
                }
            }

            // negate the value
            storeLocation = -storeLocation;

            // converting the decimal back to binary
            for (int i = 32; i > -1; i--)
            {
                int mask = 1u << (32 - 1 - i);
                flip[i] = (storeLocation & mask) ? 1 : 0;
            }

            // reversing the array so that the smallest value is on the left
            int temp;
            int j = 31;
            for (int i = 0; i < j; i++, j--)
            {
                temp = flip[i];
                flip[i] = flip[j];
                flip[j] = temp;
            }
            // copying the reversed array to the accu,ulator
            for (int i = 0; i < 32; i++)
            {
                Accumulator->setLocation(i, flip[i]);
            }
        }
    }
    // store to memory
    if (*opcode == "STO")
    {
        // copys the accumulator to memory
        for (int i = 0; i < 32; i++)
        {
            theStore->setRegiserLocation((*operand), i, (Accumulator->getLocation(i)));
        }
    }

    // Subtract from accumulator
    if (*opcode == "SUB")
    {

        // temp array for both copys of accumulator and register
        bool memory[32];
        bool accumulatorArray[32];
        int memoryInt = 0;
        int accumulatorInt = 0;

        // copying the registers to the temp arrays
        for (int i = 0; i < 32; i++)
        {
            memory[i] = theStore->getRegisterLocation((*operand), i);
        }

        for (int i = 0; i < 32; i++)
        {
            accumulatorArray[i] = Accumulator->getLocation(i);
        }

        // if the memory array is negative
        if (memory[31] == true)
        {
            // flip the array
            bool flip[32];
            for (int i = 0; i < 32; i++)
            {
                char a = memory[i];
                if (a == '0')
                {
                    flip[i] = 1;
                }
                else
                {
                    flip[i] = 0;
                }
            }
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (flip[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }

            // add one and negate
            memoryInt = -(memoryInt + 1);
        }

        // if the array is positive
        if (memory[31] == false)
        {
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (memory[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }
        }

        // if the accumulator is negative
        if (accumulatorArray[31] == true)
        {
            // flip the bits
            bool flip[32];
            for (int i = 0; i < 32; i++)
            {
                int a = accumulatorArray[i];
                if (a == 0)
                {
                    flip[i] = 1;
                }
                else
                {
                    flip[i] = 0;
                }
            }

            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (flip[i] == 1)
                {
                    accumulatorInt += pow(2, i);
                }
            }

            // negate and add one
            accumulatorInt = -(accumulatorInt + 1);
        }
        // if the accumulator is positive
        if (accumulatorArray[31] == false)
        {
            // get the decimal value
            for (int i = 0; i < 32; i++)
            {
                if (accumulatorArray[i] == 1)
                {
                    memoryInt += pow(2, i);
                }
            }
        }

        // subtract the memory from the accumulator
        int newAccumulator = accumulatorInt - memoryInt;

        // get the binaray
        bool newAccumulatorArray[32];
        for (int i = 0; i < 32; i++)
        {
            int mask = 1u << (32 - 1 - i);
            newAccumulatorArray[i] = (newAccumulator & mask) ? 1 : 0;
        }

        // reverse the array
        int temp;
        int j = 31;
        for (int i = 0; i < j; i++, j--)
        {
            temp = newAccumulatorArray[i];
            newAccumulatorArray[i] = newAccumulatorArray[j];
            newAccumulatorArray[j] = temp;
        }

        // update the accumulator
        for (int i = 0; i < 32; i++)
        {
            Accumulator->setLocation(i, newAccumulatorArray[i]);
        }
    }

    // Skip next instuction if accumulator is negaive
    if (*opcode == "CMP")
    {
        // get the last value of the accumulator
        bool accumulator = Accumulator->getLocation(32);

        // if the accumulator is negative
        if (accumulator == true)
        {
            // increment the CI
            incrementRegister(CI);
        }
    }
}

/**
 * @brief Helper function prints all the memory locations
 *
 * @param CI
 * @param PI
 * @param Accumulator
 * @param theStore
 */
void printMemoryLocations(Register *CI, Register *PI, Register *Accumulator, Store *theStore)
{
    cout << "The CI:" << endl;
    cout << *CI << endl;

    cout << "The PI:" << endl;
    cout << *PI << endl;

    cout << "The Accumulator:" << endl;
    cout << *Accumulator << endl;

    cout << "The Store:" << endl;
    cout << *theStore << endl;
}