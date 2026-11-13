/* Task A1: Function decomposition and interfaces
   Demonstrates donor registration, eligibility, search, stock update,
   and returning two results using both pointer parameters and a structure. */
#include <stdio.h>
#include <string.h>

#define MAX_DONORS 100
typedef struct {
    int id, age, day, month, year;
    char name[50], group[4], phone[16];
} Donor;

typedef struct { int count, youngest_id; } SearchResult;

int register_donor(Donor *d, int id, const char *name, const char *group,
                  int age, const char *phone, int day, int month, int year);
int is_eligible(const Donor *d, int today_day, int today_month, int today_year);
int find_donors(const Donor donors[], int n, const char *group,
                int day, int month, int year, int *youngest_id);
SearchResult find_donors_result(const Donor donors[], int n, const char *group,
                                int day, int month, int year);
int update_stock(int stock[], int index, int change);

int register_donor(Donor *d, int id, const char *name, const char *group,
                  int age, const char *phone, int day, int month, int year) {
    if (!d || !name || !group || !phone || age < 18 || strlen(group) > 3) return 0;
    d->id = id; d->age = age;
    snprintf(d->name, sizeof d->name, "%s", name);
    snprintf(d->group, sizeof d->group, "%s", group);
    snprintf(d->phone, sizeof d->phone, "%s", phone);
    d->day = day; d->month = month; d->year = year;
    return 1;
}

/* Simplified eligibility demonstration: at least 90 days since last donation.
   Dates are compared using a simple day-count approximation. */
int is_eligible(const Donor *d, int td, int tm, int ty) {
    int today = ty * 365 + tm * 30 + td;
    int last = d->year * 365 + d->month * 30 + d->day;
    return d && today - last >= 90;
}

int find_donors(const Donor donors[], int n, const char *group,
                int day, int month, int year, int *youngest_id) {
    int count = 0, youngest_age = 1000;
    if (youngest_id) *youngest_id = -1;
    for (int i = 0; i < n; ++i) {
        if (strcmp(donors[i].group, group) == 0 &&
            is_eligible(&donors[i], day, month, year)) {
            count++;
            if (donors[i].age < youngest_age) {
                youngest_age = donors[i].age;
                if (youngest_id) *youngest_id = donors[i].id;
            }
        }
    }
    return count;
}

SearchResult find_donors_result(const Donor donors[], int n, const char *group,
                                int day, int month, int year) {
    SearchResult r;
    r.youngest_id = -1;
    r.count = find_donors(donors, n, group, day, month, year, &r.youngest_id);
    return r;
}

int update_stock(int stock[], int index, int change) {
    if (!stock || index < 0 || index >= 8 || stock[index] + change < 0) return 0;
    stock[index] += change;
    return 1;
}

int main(void) {
    Donor donors[3];
    int n = 0, youngest = -1;
    register_donor(&donors[n++], 1001, "Arun", "O+", 25, "9876543210", 1, 1, 2026);
    register_donor(&donors[n++], 1002, "Bala", "O+", 21, "9876543211", 1, 1, 2026);
    register_donor(&donors[n++], 1003, "Chitra", "A+", 30, "9876543212", 1, 8, 2026);
    int count = find_donors(donors, n, "O+", 1, 11, 2026, &youngest);
    printf("Pointer-output design: eligible=%d youngest ID=%d\n", count, youngest);
    SearchResult r = find_donors_result(donors, n, "O+", 1, 11, 2026);
    printf("Structure-return design: eligible=%d youngest ID=%d\n", r.count, r.youngest_id);
    return 0;
}
