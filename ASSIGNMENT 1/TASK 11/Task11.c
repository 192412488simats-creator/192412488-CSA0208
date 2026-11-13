/* TASK 11 – Recommended final design using integer paise and wide totals */
#include <stdio.h>
#include <limits.h>

#define METER_MAX 65535U
#define SLAB1_UNITS 100U
#define SLAB2_UNITS 200U
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL
#define FIXED_PAISE 5000LL

static unsigned int get_units(unsigned int previous, unsigned int current)
{
    return (current - previous) & METER_MAX;
}

static long long bill_paise(unsigned int units)
{
    long long amount = FIXED_PAISE;
    if (units > SLAB1_UNITS) {
        unsigned int middle = units < SLAB2_UNITS
                            ? units - SLAB1_UNITS
                            : SLAB2_UNITS - SLAB1_UNITS;
        amount += (long long)middle * RATE2_PAISE;
    }
    if (units > SLAB2_UNITS)
        amount += (long long)(units - SLAB2_UNITS) * RATE3_PAISE;
    return amount;
}

int main(void)
{
    unsigned int previous, current;
    int household_id;

    printf("Enter household ID: ");
    if (scanf("%d", &household_id) != 1 || household_id <= 0) {
        puts("Invalid household ID.");
        return 1;
    }

    printf("Enter previous and current readings (0 to %u): ", METER_MAX);
    if (scanf("%u %u", &previous, &current) != 2 ||
        previous > METER_MAX || current > METER_MAX) {
        puts("Invalid meter readings.");
        return 1;
    }

    unsigned int units = get_units(previous, current);
    long long amount = bill_paise(units);

    printf("Household: %d\nUnits: %u\n", household_id, units);
    printf("Bill: Rs %lld.%02lld\n", amount / 100, amount % 100);
    return 0;
}
