/* TASK 09 – Complete rural electricity billing program with validation */
#include <stdio.h>
#include <limits.h>

typedef unsigned short meter_t;

static unsigned int units_consumed(meter_t previous, meter_t current)
{
    return (meter_t)(current - previous);
}

static long compute_bill(unsigned int units)
{
    long paise = 5000L; /* fixed charge Rs 50 */

    if (units > 200U)
        paise += (long)(units - 200U) * 450L;
    if (units > 100U) {
        unsigned int middle = units < 200U ? units - 100U : 100U;
        paise += (long)middle * 225L;
    }
    return paise; /* first 100 units are free */
}

int main(void)
{
    long previous_input, current_input;
    int household_id;

    printf("Enter household ID: ");
    if (scanf("%d", &household_id) != 1 || household_id <= 0) {
        printf("Invalid household ID.\n");
        return 1;
    }

    printf("Enter previous and current meter readings (0 to %u): ",
           (unsigned)USHRT_MAX);
    if (scanf("%ld %ld", &previous_input, &current_input) != 2) {
        printf("Invalid reading: enter numeric values.\n");
        return 1;
    }

    if (previous_input < 0 || previous_input > USHRT_MAX ||
        current_input < 0 || current_input > USHRT_MAX) {
        printf("Invalid reading: values must be between 0 and %u.\n",
               (unsigned)USHRT_MAX);
        return 1;
    }

    meter_t previous = (meter_t)previous_input;
    meter_t current = (meter_t)current_input;

    /* A lower current value is treated as one register rollover. */
    unsigned int units = units_consumed(previous, current);
    long bill = compute_bill(units);

    printf("\nHousehold ID: %d\n", household_id);
    printf("Units consumed: %u\n", units);
    printf("Energy + fixed charge: Rs %ld.%02ld\n", bill / 100, bill % 100);
    return 0;
}
