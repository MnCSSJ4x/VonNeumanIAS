#include "IAS.h"

void fetch(int value_at_pc)
{
    MAR = value_at_pc;
    MBR.lhs = MainMemory[MAR] >> 20; //data_
    MBR.rhs = MainMemory[MAR] & 0b0000000000000000000011111111111111111111;
    IBR = MBR.rhs;
    IR = (MBR.lhs) >> 12;
    MAR = ((MBR.lhs)) & 0b00000000111111111111;
    PC_index++;

    if (left_flag == 0)
    {
        decode_execute(IR, MAR);
        //decode on right
    }
    else
    {
        //decode left
        //decode right
    }
}

void decode_execute(int IR, int MAR)
{
    switch (IR) //Takes opcode
    {
        //MEMORY BASED
    case 0b00001010:
        printf("Detected LoadMQ\n");
        ACC = MQ;
        printf("Transfer of MQ to ACC Done.\n"); //Load MQ
        break;
    case 0b00001001:
        MBR.data = MainMemory[MAR];
        MQ = MBR.data;
        //load MQ M(X)
        break;
    case 0b00100001: //Stor M(X)
        printf("Detected STOR M(X)");
        ACC = MBR.data;
        MainMemory[MAR] = MBR.data;
        printf("Stored Succesfully");
        break;
    case 0b00000001: //Load M(X)
        printf("Detected LOAD M(X)");
        MBR.data = MainMemory[MAR];
        ACC = MBR.data;
        printf("Load successful\n");
        break;

    case 0b00000010:
        printf("Detected -LOAD M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC = -MBR.data;
        printf("Load successful\n");
        break;
    case 0b00000100:
        printf("Detected LOAD -| M(X)|\n");
        MBR.data = -(long long int)fabs(MainMemory[MAR]);
        ACC = MBR.data;
        printf("Load successful\n");
        break;
    case 0b00000011:
        printf("Detected LOAD| M(X) |");
        MBR.data = MainMemory[MAR];
        ACC = (long long int)fabs(MBR.data);
        printf("Load successful\n");
        break;

    //JUMP BASED
    
    case 0b00001101:
        printf("JUMP to LHS M(X)");
        left_flag=1;
        PC[PC_index]=MainMemory[MAR];
        break;
    case 0b00001110:
        printf("JUMP to RHS M(X)");
        left_flag=0;
        PC[PC_index]=MainMemory[MAR];
        break;
    
    case 0b000011111:
        printf("JUMP TO LHS M(X) if AC is non-negative");
        if(ACC>0)
        {
            left_flag=1;
            PC[PC_index]=MainMemory[MAR];
        }
        break;
    case 0b00010000:
        printf("JUMP to RHS M(X) if AC is non-negative");
        if(ACC>0)
        {
            left_flag=0;
            PC[PC_index]=MainMemory[MAR];
        }
        break;

    //MODIFIED STOR

    case 0b00010010:
        printf("STOR AC value at M(X),[8:19]");
        int lhsinst=MainMemory[MAR]>>20;
        int leftmem=lhsinst>>12;
        int rightmem=ACC & 00000000111111111111;
        lhsinst=(leftmem<<12)+rightmem;
        int rhsinst=MainMemory[MAR] & 0b0000000000000000000011111111111111111111;
        MainMemory[MAR]=(lhsinst<<20)+rhsinst;
        break;
    case 0b00010011:
        printf("STOR AC value at M(X),[28:39]");
        int rhsinst=MainMemory[MAR] & 0b0000000000000000000011111111111111111111;
        int leftmem=rhsinst>>12;
        int rightmem=ACC & 00000000111111111111;
        rhsinst=(leftmem<<12)+rightmem;
        int lhsinst=MainMemory[MAR]>>20;
        MainMemory[MAR]=(lhsinst<<20)+rhsinst;
        break;


    // ARITHMETIC BASED

    case 0b00000101:
        printf("Detected add M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC += MBR.data;
        printf("Added to AC succesfully\n");
        break;
    case 0b00000111:
        printf("Detected add |M(X)|\n");
        MBR.data = (long long int)fabs(MainMemory[MAR]);
        ACC += MBR.data;
        printf("Added to AC succesfully\n");
        break;
    case 0b00000110:
        printf("Detected sub M(X)\n");
        MBR.data = MainMemory[MAR];
        ACC -= MBR.data;
        printf("Subtracted from AC succesfully\n");
        break;
    case 0b00001000:
        printf("Detected sub |M(X)|\n");
        MBR.data = (long long int)fabs(MainMemory[MAR]);
        ACC -= MBR.data;
        printf("Subtracted from AC succesfully\n");
        break;
    case 0b00010100:
        printf("Detected Left Shift\n");
        ACC = ACC << 1;
        printf("Left shift successful\n");
        break;
    case 0b00010101:
        printf("Detected Right Shift\n");
        ACC = ACC >> 1;
        printf("Right shift successful\n");
        break;

    }
}
void PrintStatus()
{
}