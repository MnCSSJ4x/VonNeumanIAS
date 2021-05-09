#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 1000
#define SIZE_PC 10
#define BUFFER 500
//Instruction format

typedef struct instruction
{
  long long int lhs;
  long long int rhs;
  long long int data;
} instruction;

//Registers

unsigned long long int MainMemory[MAX_SIZE];
long long int PC[SIZE_PC];
long long int MAR;
long long int IR;
long long int IBR;
instruction MBR;
long long int ACC;
long long int MQ;
long long int PC_index = 0;
long long int left_flag = 0; //If we have a single instruction _> by default its right instruction so 0
void PrintStatus_Instruction();
void PrintStatus_Exectuion();
void fetch(int value_at_pc);
void decode_execute(int IR, int MAR);
long long int lhsinst,rhsinst,leftmem,rightmem;