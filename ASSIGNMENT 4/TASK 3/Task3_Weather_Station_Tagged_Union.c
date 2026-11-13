/* TASK 3 - Weather station packets using a tagged union */
#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading {
    enum kind type;
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

void show(const struct reading *r) {
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->value.celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->value.percent);
            break;
        case STATUS:
            printf("Status %s\n", r->value.status);
            break;
        default:
            printf("Unknown packet type\n");
    }
}

int main(void) {
    struct reading log[3] = {
        {TEMPERATURE, {.celsius = 31.5f}},
        {HUMIDITY, {.percent = 68}},
        {STATUS, {.status = "OK"}}
    };
    printf("sizeof union = %zu, sizeof struct reading = %zu\n",
           sizeof log[0].value, sizeof log[0]);
    for (int i = 0; i < 3; i++) show(&log[i]);

    /* Misuse experiment: the active member is celsius, not percent.
       Reading value.percent here is not a meaningful humidity reading;
       its result is implementation-dependent/unspecified by the intended data model. */
    struct reading wrong = {TEMPERATURE, {.celsius = 31.5f}};
    printf("Misuse experiment (reading inactive member): %d\n", wrong.value.percent);
    return 0;
}
