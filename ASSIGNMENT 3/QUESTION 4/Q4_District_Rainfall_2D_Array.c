/* Q4 - District rainfall records using a two-dimensional array.
   Demonstrates annual totals, monthly averages, maximum rainfall and deficiency. */
#include <stdio.h>

#define DISTRICTS 3
#define MONTHS 4

void row_totals(const double rain[DISTRICTS][MONTHS], double totals[]) {
    for (int i = 0; i < DISTRICTS; i++) {
        totals[i] = 0;
        for (int j = 0; j < MONTHS; j++) totals[i] += rain[i][j];
    }
}
void column_averages(const double rain[DISTRICTS][MONTHS], double averages[]) {
    for (int j = 0; j < MONTHS; j++) {
        double sum = 0;
        for (int i = 0; i < DISTRICTS; i++) sum += rain[i][j];
        averages[j] = sum / DISTRICTS;
    }
}
void find_maximum(const double rain[DISTRICTS][MONTHS], double *maximum,
                  int *district, int *month) {
    *maximum = rain[0][0]; *district = 0; *month = 0;
    for (int i = 0; i < DISTRICTS; i++)
        for (int j = 0; j < MONTHS; j++)
            if (rain[i][j] > *maximum) {
                *maximum = rain[i][j]; *district = i; *month = j;
            }
}
int main(void) {
    /* Small 3 x 4 sample for hand verification; replace with 38 x 12 for full data. */
    double rain[DISTRICTS][MONTHS] = {
        {80, 65, 40, 90},
        {55, 70, 35, 60},
        {100, 85, 75, 95}
    };
    double totals[DISTRICTS], averages[MONTHS], max;
    int maxD, maxM;
    row_totals(rain, totals);
    column_averages(rain, averages);
    find_maximum(rain, &max, &maxD, &maxM);

    for (int i = 0; i < DISTRICTS; i++)
        printf("District %d annual total = %.1f mm\\n", i + 1, totals[i]);
    for (int j = 0; j < MONTHS; j++)
        printf("Month %d state average = %.1f mm\\n", j + 1, averages[j]);
    printf("Wettest district-month: District %d, Month %d = %.1f mm\\n",
           maxD + 1, maxM + 1, max);
    printf("Districts below 60%% of overall state average: ");
    double grand = 0;
    for (int i = 0; i < DISTRICTS; i++) grand += totals[i];
    double stateAverage = grand / (DISTRICTS * MONTHS);
    for (int i = 0; i < DISTRICTS; i++)
        if (totals[i] / MONTHS < 0.60 * stateAverage) printf("%d ", i + 1);
    printf("\\n");
    return 0;
}
