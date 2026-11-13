/* TASK 05 – Header file and conditional DEBUG compilation */
#include <stdio.h>
#include "billing.h"

long compute_bill(int units)
{
    long energy = 0;

    if (units > SLAB2_UNITS)
        energy += (long)(units - SLAB2_UNITS) * RATE3_PAISE;

    if (units > SLAB1_UNITS) {
        int middle = units < SLAB2_UNITS
                   ? units - SLAB1_UNITS
                   : SLAB2_UNITS - SLAB1_UNITS;
        energy += (long)middle * RATE2_PAISE;
    }

#ifdef DEBUG
    printf("[DEBUG] units=%d, energy_charge_paise=%ld\n", units, energy);
#endif

    return FIXED_CHARGE_PAISE + energy;
}

int main(void)
{
    int units;
    printf("Enter units consumed: ");
    if (scanf("%d", &units) != 1 || units < 0) {
        printf("Invalid units.\n");
        return 1;
    }

    long bill = compute_bill(units);
    printf("Total bill = Rs %ld.%02ld\n", bill / 100, bill % 100);
    return 0;
}
