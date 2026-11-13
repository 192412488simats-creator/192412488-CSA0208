/* Task A2: Recursive digital root and exponentiation by squaring */
#include <stdio.h>
#include <stdlib.h>

int digit_sum(int n) {
    if (n < 10) return n;
    return n % 10 + digit_sum(n / 10);
}
int digital_root(int n) {
    if (n < 10) return n;
    return digital_root(digit_sum(n));
}
long long power_fast(long long base, unsigned int exp) {
    if (exp == 0) return 1;
    long long half = power_fast(base, exp / 2);
    if (exp % 2 == 0) return half * half;
    return base * half * half;
}
long long power_linear(long long base, unsigned int exp) {
    if (exp == 0) return 1;
    return base * power_linear(base, exp - 1);
}
int main(void) {
    int n;
    unsigned int e;
    long long b;
    printf("Enter donor ID digits (positive integer): ");
    if (scanf("%d", &n) != 1 || n < 0) { puts("Invalid ID"); return 1; }
    printf("Digital root = %d\n", digital_root(n));
    printf("Enter base and non-negative exponent: ");
    if (scanf("%lld %u", &b, &e) != 2) { puts("Invalid input"); return 1; }
    printf("Linear power = %lld\n", power_linear(b, e));
    printf("Halving power = %lld\n", power_fast(b, e));
    return 0;
}
