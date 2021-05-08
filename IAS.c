#include "IAS.h"

void fetch(int value_at_pc)
{
    MAR = value_at_pc;
    MBR.lhs = MainMemory[MAR] >> 20; //data_
    MBR.rhs = MainMemory[MAR] & 0b0000000000000000000011111111111111111111;

    if (left_flag == 0)
    {
        IR = (MBR.rhs) >> 12;
        MAR = ((MBR.rhs)) & 0b00000000111111111111;
        PrintStatus_Exectuion();
        decode_execute(IR, MAR);
        //decode on right
    }
    else
    {
        IBR = MBR.rhs;
        IR = (MBR.lhs) >> 12;
        MAR = ((MBR.lhs)) & 0b00000000111111111111;
        //decode left
        //decode right
    }
    PC_index++;
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
        MainMemory[MAR] = ACC;
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
        left_flag = 1;
        PC_index=MAR;
        break;
    case 0b00001110:
        printf("JUMP to RHS M(X)");
        left_flag = 0;
        PC_index=MAR;
        break;

    case 0b000011111:
        printf("JUMP TO LHS M(X) if AC is non-negative");
        if (ACC > 0)
        {
            left_flag = 1;
            PC[PC_index] = MainMemory[MAR];
        }
        break;
    case 0b00010000:
        printf("JUMP to RHS M(X) if AC is non-negative");
        if (ACC > 0)
        {
            left_flag = 0;
            PC[PC_index] = MainMemory[MAR];
        }
        break;

        //MODIFIED STOR

    case 0b00010010:
        printf("STOR AC value at M(X),[8:19]");
        lhsinst = MainMemory[MAR] >> 20;
        leftmem = lhsinst >> 12;
        rightmem = ACC & 00000000111111111111;
        lhsinst = (leftmem << 12) + rightmem;
        int rhsinst = MainMemory[MAR] & 0b0000000000000000000011111111111111111111;
        MainMemory[MAR] = (lhsinst << 20) + rhsinst;
        break;
    case 0b00010011:
        printf("STOR AC value at M(X),[28:39]");
        rhsinst = MainMemory[MAR] & 0b0000000000000000000011111111111111111111;
        leftmem = rhsinst >> 12;
        rightmem = ACC & 00000000111111111111;
        rhsinst = (leftmem << 12) + rightmem;
        lhsinst = MainMemory[MAR] >> 20;
        MainMemory[MAR] = (lhsinst << 20) + rhsinst;
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
    case 0b00001011:
        printf("Detected MUL M(x)\n");
        MBR.data = MainMemory[MAR];
        MQ=MQ*MBR.data;
        //MQ = (MQ * MBR.data) & 0b111111111111111111111111111111111111111111111111;
        //ACC = (ACC * MBR.data) >> 40;
        printf("Multiplication succesful\n");
        break;
    case 0b00001100:
        printf("Detected DIV M(X)\n");
        MBR.data = MainMemory[MAR];
        MQ = ACC / MBR.data;
        ACC = ACC % MBR.data;
        printf("Division successful \n");
        break;
    }
    PrintStatus_Instruction();
}
void PrintStatus_Instruction()
{
    printf("PC = %lld\nIR = %lld\nMAR = %lld\nIBR = %lld\nMBR = %lld\nLeft Instruction = %lld\nRight Instruction = %lld", PC_index, IR, MAR, IBR, MBR.data, MBR.lhs, MBR.rhs);
}
void PrintStatus_Exectuion()
{
    printf("ACC = %lld\n MQ= %lld\n Value obtained from memory = %lld \n MBR = %lld ", ACC, MQ, MainMemory[MAR], MBR.data);
}
void addandsub()
{
    MainMemory[0] = 0b00000001000000000100;
    MainMemory[4] = 5;
    MainMemory[5] = 15;
    if(MainMemory[4]==MainMemory[5])
        MainMemory[1] = 0b00000110000000000101;
    else
        MainMemory[1] = 0b00000101000000000101;
    MainMemory[2] = 0b00100001000000000110;
    PC[0] = 0;
    PC[1] = 1;
    PC[2] = 2;
    for (PC_index = 0; PC_index <= 2;)
        fetch(PC[PC_index]);
    printf("\n%lli", MainMemory[6]);
}
void factorial()
{
    MainMemory[100]=1;
    MainMemory[101]=5;
    MainMemory[0]=0b00001001000001100100;

    //MUL M(101)
    MainMemory[1]=0b00001011000001100101;

    MainMemory[2]=0b00000001000001100101;
    MainMemory[3]=0b00000110000001100100;
    MainMemory[4]=0b00100001000001100101;
    MainMemory[5]=0b00001110000000000010;
    MainMemory[6]=0b00001010000000000000;
    MainMemory[7]=0b00100001000001100110;
    //LOAD MQ M(100)
    //LOAD M(101) AC
    
    //Loop

    //LOAD M(101)
    //SUB M(100)
    //STOR M(101)
    //JUMP Loop
    PC[0]=0;
    PC[1]=2;

    PC[2]=1;
    PC[3]=2;
    PC[4]=3;
    PC[5]=4;
    PC[6]=5;
    for (PC_index = 0; PC_index <= 1;)
        fetch(PC[PC_index]);
    while(ACC>=1)
    {
        fetch(PC[PC_index]);
    }
    //LOAD MQ
    //STOR M(102)
        printf("\n%lli", MainMemory[102]);

}
int main()
{
    //addandsub();
    factorial();
}

//TO DO
//arithmetic involving addition, subtraction works

//MUL and DIV

// Sample 1  - Example given in qpaper
// Sample 2 - Factorial