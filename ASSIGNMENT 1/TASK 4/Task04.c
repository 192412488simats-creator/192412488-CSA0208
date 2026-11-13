/* TASK 04 – Safe macros and static inline alternatives */
#include <stdio.h>

#define RUPEES_TO_PAISE(x) ((long)(x) * 100L)
#define SQUARE(x) ((x) * (x))
#define MAX_VALUE(a, b) (((a) > (b)) ? (a) : (b))

static inline long square_fn(long x)
{
    return x * x;
}

static inline long max_fn(long a, long b)
{
    return a > b ? a : b;
}

int main(void)
{
    int a = 4, b = 9;
    int i = 3, j = 5;

    printf("SQUARE(a + 1) = %d\n", SQUARE(a + 1));
    printf("Maximum = %d\n", MAX_VALUE(a, b));
    printf("Rs 25 in paise = %ld\n", RUPEES_TO_PAISE(25));
    printf("Inline square = %ld\n", square_fn(5));
    printf("Inline maximum = %ld\n", max_fn(i, j));

    /* Do not use MAX_VALUE(i++, j): macro arguments may be evaluated twice. */
    printf("i before safe use = %d\n", i);
    printf("MAX using values = %d\n", MAX_VALUE(i, j));
    return 0;
}
