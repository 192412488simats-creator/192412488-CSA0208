/* TASK 10 – Compare float accumulation with exact integer paise */
#include <stdio.h>
#include <limits.h>

int main(void)
{
    const int counts[] = {4000, 60000, 800000};
    const long bill_paise = 16250L; /* Rs 162.50 */
    const float bill_rupees = 162.50f;

    for (int k = 0; k < 3; k++) {
        int n = counts[k];
        long long exact_total_paise = (long long)n * bill_paise;
        float float_total_rupees = 0.0f;

        for (int i = 0; i < n; i++)
            float_total_rupees += bill_rupees;

        double exact_rupees = exact_total_paise / 100.0;
        double difference = (double)float_total_rupees - exact_rupees;

        printf("\nHouseholds: %d\n", n);
        printf("Integer paise total: %lld paise\n", exact_total_paise);
        printf("Exact total: Rs %.2f\n", exact_rupees);
        printf("Float accumulated total: Rs %.2f\n",
               (double)float_total_rupees);
        printf("Difference: Rs %.6f\n", difference);
    }

    printf("\nsizeof(int)=%zu, sizeof(long)=%zu, sizeof(long long)=%zu\n",
           sizeof(int), sizeof(long), sizeof(long long));
    printf("INT_MAX=%d, LONG_MAX=%ld, LLONG_MAX=%lld\n",
           INT_MAX, LONG_MAX, LLONG_MAX);
    return 0;
}
