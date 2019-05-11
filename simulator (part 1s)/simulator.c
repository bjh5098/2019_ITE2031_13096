#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8       /* number of machine registers */
#define MAXLINELENGTH 1000

typedef struct stateStruct
{
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;
//bjh
int convertNum(int num);
void disassemble(int mc, int *opcode, int *regA, int *regB, int *Offset);
void printState(stateType *);

int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    if (argc != 2)
    {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL)
    {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }
    
    /* read in the entire machine-code file into memory */
    state.pc = 0;
    for (int i = 0; i < NUMREGS; i++)
    {
        state.reg[i] = 0;
    }
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++)
    {
        if (sscanf(line, "%d", state.mem + state.numMemory) != 1)
        {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    int opcode;
    int regA;
    int regB;
    int Offset;
    int counter = 0;

    printf("\n");
    while (1) // keep simulate
    {
        printState(&state); // print before executing the instruction
        disassemble(state.mem[state.pc], &opcode, &regA, &regB, &Offset);
        if (opcode == 0)//add
        {
            state.reg[Offset] = state.reg[regA] + state.reg[regB];
        }
        else if (opcode == 1)//nor
        {
            state.reg[Offset] = ~(state.reg[regA] | state.reg[regB]);
        }
        else if (opcode == 2)//lw
        {
            state.reg[regB] = state.mem[state.reg[regA] + Offset];
        }
        else if (opcode == 3)//sw
        {
            state.mem[state.reg[regA] + Offset] = state.reg[regB];
        }
        else if (opcode == 4)//beq
        {
            if (state.reg[regA] == state.reg[regB])
            {
                state.pc += Offset;
            }
        }
        else if (opcode == 5)//jalr
        {
            state.reg[regB] = state.pc + 1;
            state.pc = state.reg[regA] - 1;
        }
        else if (opcode == 6)//halt
        {
            printf("machine halted\ntotal of %d instructions "
                   "executed\nfinal state of machine:\n", counter + 1);
            state.pc++;
            printState(&state);
            break;
        }
        else if (opcode == 7)//noop
        {
            //do nothing
        }
        else
        {
            printf("error: unrecognized opcode\n");
            exit(1);
        }
        

        state.pc++;
        counter++;
    }

    return (0);
}

void disassemble(int mc, int *opcode, int *regA, int *regB, int *Offset)
{
    *opcode = (mc >> 22) & 7;
    *regA = (mc >> 19) & 7;
    *regB = (mc >> 16) & 7;
    *Offset = convertNum(mc & 65535);
}

void printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");

    for (i = 0; i < statePtr->numMemory; i++)
    {
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n");

    for (i = 0; i < NUMREGS; i++)
    {
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }
    printf("end state\n");
}

int convertNum(int num)
{
    /* convert a 16-bit number into a 32-bit Linux integer */
    if (num & (1 << 15))
    {
        num -= (1 << 16);
    }
    return (num);
}