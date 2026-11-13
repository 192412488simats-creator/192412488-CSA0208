/* TASK 2 - Courier parcel tracking with nested structures */
#include <stdio.h>

struct date { int day, month, year; };
struct address { char city[20]; int pincode; };
struct parcel {
    int id;
    float weight;
    struct address from, to;
    struct date booked;
    char service[12];
    float charge;
};

void print_parcel(const struct parcel *p) {
    printf("%d %.1f kg %s-%06d %02d/%02d/%04d\n",
           p->id, p->weight, p->to.city, p->to.pincode,
           p->booked.day, p->booked.month, p->booked.year);
}

/* Selection sort: ascending weight. */
void sort_by_weight(struct parcel p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int lightest = i;
        for (int j = i + 1; j < n; j++)
            if (p[j].weight < p[lightest].weight) lightest = j;
        if (lightest != i) {
            struct parcel temp = p[i];
            p[i] = p[lightest];
            p[lightest] = temp;
        }
    }
}

void list_by_receiver_city(const struct parcel p[], int n, const char city[]) {
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (p[i].to.city[j] && city[j] &&
               p[i].to.city[j] == city[j]) j++;
        if (p[i].to.city[j] == '\0' && city[j] == '\0') print_parcel(&p[i]);
    }
}

int main(void) {
    struct parcel list[3] = {
        {501, 4.5f, {"Salem", 636001}, {"Madurai", 625001}, {12,10,2026}, "Normal", 90.0f},
        {502, 1.2f, {"Chennai", 600001}, {"Chennai", 600077}, {12,10,2026}, "Express", 75.0f},
        {503, 2.8f, {"Erode", 638001}, {"Coimbatore", 641001}, {13,10,2026}, "Normal", 65.0f}
    };
    sort_by_weight(list, 3);
    puts("Parcels sorted by weight:");
    for (int i = 0; i < 3; i++) print_parcel(&list[i]);

    puts("Parcels for receiver city Chennai:");
    list_by_receiver_city(list, 3, "Chennai");

    /* Access third parcel receiver PIN: list[2].to.pincode
       Pointer form: struct parcel *ptr = list; ptr[2].to.pincode
       or (ptr + 2)->to.pincode */
    return 0;
}
