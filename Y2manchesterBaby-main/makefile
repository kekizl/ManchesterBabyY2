CC = g++
CFLAGS = -std=c++17 -Wall -Werror -pedantic -g


# The complete command with all files
complete:
	g++ -std=c++17 -Wall -Werror -pedantic -g -o main menu.cpp assemblerFiles/assembler.cpp assemblerFiles/bufferLine.cpp assemblerFiles/instruction.cpp assemblerFiles/instructionSet.cpp assemblerFiles/outputBuffer.cpp assemblerFiles/symbol.cpp assemblerFiles/symbolTable.cpp assemblerFiles/utility.cpp manchesterBabyFiles/manchesterBaby.cpp manchesterBabyFiles/memoryLocations.cpp

# Compiles both the assembler and the simulator

all: menu.o manchesterBaby.o memoryLocations.o assembler.o symbol.o symbolTable.o instruction.o instructionSet.o outputBuffer.o bufferLine.o utility.o
	$(CC) $(CFLAGS) -o main menu.o manchesterBaby.o memoryLocations.o  assembler.o symbol.o symbolTable.o instruction.o instructionSet.o outputBuffer.o bufferLine.o utility.o


# Compiles just the simulator
simulator: manchesterBaby.o memoryLocations.o
	$(CC) $(CFLAGS) -o simulator manchesterBaby.o memoryLocations.o

# Compiles just the assembler
assembler: assembler.o symbol.o symbolTable.o instruction.o instructionSet.o outputBuffer.o bufferLine.o utility.o
	$(CC) $(CFLAGS) -o assembler assembler.o symbol.o symbolTable.o instruction.o instructionSet.o outputBuffer.o bufferLine.o utility.o

#Cleans the directory
clean:
	rm *.o main assembler simulator assemblerTest
	
# Compiles the Assembler with tests

assembler_test: assembler.o symbol.o symbolTable.o instruction.o instructionSet.o tester.o outputBuffer.o bufferLine.o utility.o
	$(CC) $(CFLAGS) -o assemblerTest assembler.o symbol.o symbolTable.o instruction.o instructionSet.o tester.o outputBuffer.o bufferLine.o utility.o

##### assembler files #####

tester.o: assemblerFiles/tester.cpp assemblerFiles/tester.h
	$(CC) -c -g assemblerFiles/tester.cpp

assembler.o: assemblerFiles/assembler.cpp assemblerFiles/assembler.h assemblerFiles/instructionSet.h assemblerFiles/symbolTable.h assemblerFiles/outputBuffer.h
	$(CC) -c -g assemblerFiles/assembler.cpp

symbol.o: assemblerFiles/symbol.cpp assemblerFiles/symbol.h
	$(CC) -c -g assemblerFiles/symbol.cpp

symbolTable.o: assemblerFiles/symbolTable.cpp assemblerFiles/symbolTable.h symbol.o
	$(CC) -c -g assemblerFiles/symbolTable.cpp

instruction.o: assemblerFiles/instruction.cpp assemblerFiles/instruction.h
	$(CC) -c -g assemblerFiles/instruction.cpp

instructionSet.o: assemblerFiles/instructionSet.cpp assemblerFiles/instructionSet.h
	$(CC) -c -g assemblerFiles/instructionSet.cpp

outputBuffer.o: assemblerFiles/outputBuffer.cpp assemblerFiles/outputBuffer.h
	$(CC) -c -g assemblerFiles/outputBuffer.cpp

bufferLine.o: assemblerFiles/bufferLine.cpp assemblerFiles/bufferLine.h
	$(CC) -c -g assemblerFiles/bufferLine.cpp

utility.o: assemblerFiles/utility.cpp assemblerFiles/utility.cpp
	$(CC) -c -g assemblerFiles/utility.cpp



##### simulator files #####

manchesterBaby.o: manchesterBabyFiles/manchesterBaby.cpp manchesterBabyFiles/manchesterBaby.h manchesterBabyFiles/memoryLocations.h
	$(CC) -c -g manchesterBabyFiles/manchesterBaby.cpp

memoryLocations.o: manchesterBabyFiles/memoryLocations.cpp manchesterBabyFiles/memoryLocations.h
	$(CC) -c -g manchesterBabyFiles/memoryLocations.cpp 

menu.o: menu.cpp manchesterBabyFiles/manchesterBaby.h manchesterBabyFiles/memoryLocations.h
	$(CC) -c -g menu.cpp


