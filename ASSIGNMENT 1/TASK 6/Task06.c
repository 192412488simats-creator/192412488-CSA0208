/* TASK 06 – Correct scanf/printf formats and input validation */
#include <stdio.h>

int main(void)
{
    int household_id, units;
    long bill_paise;

    printf("Enter household ID and units consumed: ");
    if (scanf("%d %d", &household_id, &units) != 2) {
        printf("Invalid input: enter two whole numbers.\n");
        return 1;
    }

    if (household_id <= 0 || units < 0) {
        printf("Invalid household ID or units.\n");
        return 1;
    }

    bill_paise = 5000L;
    if (units > 100)
        bill_paise += (long)(units - 100 < 100 ? units - 100 : 100) * 225L;
    if (units > 200)
        bill_paise += (long)(units - 200) * 450L;

    printf("Household ID: %d\n", household_id);
    printf("Units consumed: %d\n", units);
    printf("Total bill: Rs %ld.%02ld\n",
           bill_paise / 100, bill_paise % 100);
    return 0;
}
