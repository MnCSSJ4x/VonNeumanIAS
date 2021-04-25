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

long long int MainMemory[MAX_SIZE];
int PC[SIZE_PC];
int MAR;
int IR;
int IBR;
instruction MBR;
int ACC;
int MQ;
int PC_index = 0;
int left_flag = 0; //If we have a single instruction _> by default its right instruction so 0
