/* TASK 07 – Type conversion, integer division and rounding examples */
#include <stdio.h>

int main(void)
{
    int units = 225;
    int a = 5, b = 2;
    double exact_division = (double)a / b;
    long amount_paise = 16250L;
    double rupees = 162.50;

    printf("1) Integer division 5 / 2 = %d\n", a / b);
    printf("2) Floating division (double)5 / 2 = %.2f\n", exact_division);
    printf("3) Integer division 225 / 100 = %d\n", units / 100);
    printf("4) Correct bill display from paise = Rs %ld.%02ld\n",
           amount_paise / 100, amount_paise % 100);
    printf("5) double rupees example = Rs %.2f\n", rupees);

    /* Demonstrate rounding a fractional paise amount to nearest paise. */
    double calculated_paise = 1234.567;
    long rounded_paise = (long)(calculated_paise + 0.5);
    printf("6) 1234.567 paise rounded = %ld paise\n", rounded_paise);

    return 0;
}
