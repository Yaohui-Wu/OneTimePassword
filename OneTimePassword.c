// Usage: (Windows) OneTimePassword password or (Linux, *BSD, MacOS) ./OneTimePassword password
// Windows is compiled by DevCPP on X86_32/X86_64 platforms.
// Linux, BSD, MacOS is compiled by gcc on X86_32/X86_64 platforms.
// Talk is SO EASY, show you my GOD.
// Simple is beautiful.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AMOUNT 64

int main(int argc, char *argv[])
{
// 95+1 printable characters pad
    unsigned char aucKeysTable[96];

// this character is arbitrary
    aucKeysTable[95] = 36;

// initialize random number seed
    srand((unsigned int)time(NULL));

// the pad is initialized with a pseudo-random number algorithm
    for(unsigned long long i = 0; i < 95; ++i)
    {
LOOP:
        aucKeysTable[i] = 32 + rand() % 95;

        for(unsigned long long j = 0; j < i; ++j)
        {
            if(aucKeysTable[j] == aucKeysTable[i]) goto LOOP;
        }
    }

    unsigned long long ulPasswordLength = -1;

// Passwords are of any length, from one to infinity.
    while(argv[1][++ulPasswordLength]);

    for(unsigned long long i = 1; i <= AMOUNT; ++i)
    {
// generate password
        for(unsigned long long j = 0; argv[1][j]; ++j) argv[1][j] = aucKeysTable[argv[1][j] % 96];

        printf("One Time Password(%llu)\t%s\n", i, argv[1]);

// Pseudo "JunTai" random number algorithm, this is the core of the algorithm.
        for(unsigned long long k = 0; k < 12; ++k)
        {
            unsigned long long ulKeyIndex, ulKeyTemp, *pulKeySwap1 = (unsigned long long*)aucKeysTable, *pulKeySwap2 = (unsigned long long*)aucKeysTable;

            if(i & 1) ulKeyIndex = argv[1][k % ulPasswordLength] % 12;

            else ulKeyIndex = rand() % 12;

            ulKeyTemp = pulKeySwap1[k];

            pulKeySwap1[k] = pulKeySwap2[ulKeyIndex];

            pulKeySwap2[ulKeyIndex] = ulKeyTemp;
        }
    }

    return 0;
}