/* Task B1: Instrumented recursive power functions and digital root */
#include <stdio.h>
#include <stdlib.h>

long long calls_linear, calls_fast;
long long power_linear(long long base, int exp) {
    calls_linear++;
    if (exp == 0) return 1;
    return base * power_linear(base, exp-1);
}
long long power_fast(long long base, int exp) {
    calls_fast++;
    if (exp == 0) return 1;
    long long half = power_fast(base, exp/2); /* compute only once */
    return (exp % 2 == 0) ? half*half : base*half*half;
}
int digit_sum(int n) { return n < 10 ? n : n%10 + digit_sum(n/10); }
int digital_root(int n) { return n < 10 ? n : digital_root(digit_sum(n)); }
long long power_iterative(long long base, unsigned int exp) {
    long long result = 1;
    while (exp) {
        if (exp & 1U) result *= base;
        base *= base;
        exp >>= 1U;
    }
    return result;
}
int main(void) {
    int tests[] = {10,100,1000,10000};
    for (int i=0; i<4; ++i) {
        calls_linear=0; calls_fast=0;
        /* Use base 1 so the demonstration avoids integer overflow. */
        power_linear(1, tests[i]); power_fast(1, tests[i]);
        printf("n=%d linear calls=%lld fast calls=%lld\n",
               tests[i], calls_linear, calls_fast);
    }
    printf("digital_root(98765)=%d\n", digital_root(98765));
    calls_linear=0; calls_fast=0;
    printf("linear 2^30=%lld calls=%lld\n", power_linear(2,30), calls_linear);
    printf("fast 2^30=%lld calls=%lld\n", power_fast(2,30), calls_fast);
    printf("iterative 2^30=%lld\n", power_iterative(2,30));
    return 0;
}
