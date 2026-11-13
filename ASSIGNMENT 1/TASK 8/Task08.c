/* TASK 08 – Source file for compilation-stage demonstration */
#include <stdio.h>

#define FIXED_CHARGE_PAISE 5000L

static long simple_bill(int units)
{
    long energy = 0;
    if (units > 100)
        energy += (long)(units - 100 < 100 ? units - 100 : 100) * 225L;
    if (units > 200)
        energy += (long)(units - 200) * 450L;
    return FIXED_CHARGE_PAISE + energy;
}

int main(void)
{
    int units = 150;
    long paise = simple_bill(units);
    printf("%d units -> Rs %ld.%02ld\n", units, paise / 100, paise % 100);
    return 0;
}

/*
Compilation stages (run in this folder):
gcc -E Task08.c -o Task08.i
gcc -S Task08.c -o Task08.s
gcc -c Task08.c -o Task08.o
gcc Task08.o -o Task08
gcc -Wall -Wextra Task08.c -o Task08
*/
