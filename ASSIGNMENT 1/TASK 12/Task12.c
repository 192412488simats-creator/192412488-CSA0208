/* TASK 12 – Smart meter billing: watt-hours, 15-minute intervals,
   configurable tariff file, and 6 PM–10 PM peak rate (+20%).

   tariff.txt format (all money values in paise):
   fixed_charge_paise 5000
   normal_rate_paise 225
   peak_percent 120

   Compile: gcc -std=c11 -Wall -Wextra Task12.c -o Task12
   Run:     ./Task12
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTERVALS_PER_DAY 96
#define INTERVAL_MINUTES 15
#define PEAK_START_MINUTE (18 * 60)
#define PEAK_END_MINUTE (22 * 60)

typedef struct {
    long long fixed_charge_paise;
    long long normal_rate_paise;
    int peak_percent;
} Tariff;

static int load_tariff(const char *filename, Tariff *t)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    int ok = fscanf(fp, "fixed_charge_paise %lld\n"
                        "normal_rate_paise %lld\n"
                        "peak_percent %d",
                    &t->fixed_charge_paise,
                    &t->normal_rate_paise,
                    &t->peak_percent) == 3;
    fclose(fp);

    return ok && t->fixed_charge_paise >= 0 &&
           t->normal_rate_paise >= 0 && t->peak_percent >= 100;
}

/* Each reading is cumulative watt-hours. Calculate interval energy in Wh.
   For this example, each interval's tariff is based on its starting time. */
static long long calculate_energy_charge(
    const long long wh[], int count, const Tariff *tariff)
{
    long long total_paise = 0;

    for (int i = 1; i < count; i++) {
        long long interval_wh = wh[i] - wh[i - 1];
        if (interval_wh < 0) {
            fprintf(stderr, "Error: cumulative meter reading decreased.\n");
            return -1;
        }

        int minute_of_day = ((i - 1) % INTERVALS_PER_DAY) * INTERVAL_MINUTES;
        long long rate = tariff->normal_rate_paise;

        if (minute_of_day >= PEAK_START_MINUTE &&
            minute_of_day < PEAK_END_MINUTE) {
            /* Round peak rate to nearest paisa. */
            rate = (tariff->normal_rate_paise * tariff->peak_percent + 50) / 100;
        }

        /* Wh * paise/kWh / 1000 = paise; round to nearest paisa per interval. */
        total_paise += (interval_wh * rate + 500) / 1000;
    }
    return total_paise;
}

int main(void)
{
    Tariff tariff;
    if (!load_tariff("tariff.txt", &tariff)) {
        puts("Could not read valid tariff.txt.");
        puts("Create tariff.txt using the format shown in the source comments.");
        return 1;
    }

    /* Demonstration readings: 97 cumulative readings cover one day + start. */
    long long readings[INTERVALS_PER_DAY + 1];
    readings[0] = 0;

    for (int i = 1; i <= INTERVALS_PER_DAY; i++) {
        /* Example: 100 Wh consumed in every 15-minute interval. */
        readings[i] = readings[i - 1] + 100;
    }

    long long energy = calculate_energy_charge(
        readings, INTERVALS_PER_DAY + 1, &tariff);

    if (energy < 0) return 1;

    long long total = tariff.fixed_charge_paise + energy;
    printf("Intervals processed: %d\n", INTERVALS_PER_DAY);
    printf("Energy charge: Rs %lld.%02lld\n", energy / 100, energy % 100);
    printf("Fixed charge: Rs %lld.%02lld\n",
           tariff.fixed_charge_paise / 100,
           tariff.fixed_charge_paise % 100);
    printf("Total bill: Rs %lld.%02lld\n", total / 100, total % 100);
    return 0;
}
