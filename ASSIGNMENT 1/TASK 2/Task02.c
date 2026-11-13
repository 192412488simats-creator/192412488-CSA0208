/* TASK 02 – Data types, sizeof, limits and 16-bit meter rollover */
#include <stdio.h>
#include <limits.h>

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    /* Conversion back to meter_t applies modulo 65536 for a 16-bit meter. */
    return (meter_t)(current - previous);
}

int main(void)
{
    printf("sizeof(meter_t) = %zu bytes, maximum reading = %u\n",
           sizeof(meter_t), (unsigned)USHRT_MAX);

    printf("Consumption: %u units\n", consumption(1200, 1530));
    printf("Consumption: %u units\n", consumption(65400, 120));

    printf("\nOther type sizes on this system:\n");
    printf("sizeof(char)       = %zu\n", sizeof(char));
    printf("sizeof(short)      = %zu\n", sizeof(short));
    printf("sizeof(int)        = %zu\n", sizeof(int));
    printf("sizeof(long)       = %zu\n", sizeof(long));
    printf("sizeof(long long)  = %zu\n", sizeof(long long));
    printf("sizeof(float)      = %zu\n", sizeof(float));
    printf("sizeof(double)     = %zu\n", sizeof(double));

    printf("\nInteger ranges:\n");
    printf("INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
    printf("LONG_MIN = %ld, LONG_MAX = %ld\n", LONG_MIN, LONG_MAX);
    printf("LLONG_MIN = %lld, LLONG_MAX = %lld\n", LLONG_MIN, LLONG_MAX);
    printf("USHRT_MAX = %u\n", (unsigned)USHRT_MAX);
    return 0;
}
