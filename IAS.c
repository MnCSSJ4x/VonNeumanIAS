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

        // ARITHMATIC BASED

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

        //JUMP BASED
    }
}
void PrintStatus()
{
}
