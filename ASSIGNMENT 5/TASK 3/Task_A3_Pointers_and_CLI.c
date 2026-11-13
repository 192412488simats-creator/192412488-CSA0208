/* Task A3: Pointer operations, lowest-stock pointer, and command-line interface.
   Usage: ./bloodbank find O+ | ./bloodbank issue A- 2 | ./bloodbank lowest */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *groups[8] = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};

int group_index(const char *g) {
    for (int i = 0; i < 8; ++i) if (strcmp(groups[i], g) == 0) return i;
    return -1;
}
int *lowest_stock(int stock[], int n) {
    if (!stock || n <= 0) return NULL;
    int *p = &stock[0];
    for (int i = 1; i < n; ++i) if (stock[i] < *p) p = &stock[i];
    return p; /* points into caller-owned array, not a local variable */
}
int main(int argc, char *argv[]) {
    int stock[8] = {15, 8, 12, 6, 9, 4, 20, 7};
    int *p = stock;
    printf("Pointer demo: p+3=%p, *(p+3)=%d, p[3]=%d, *p++=%d\n",
           (void *)(p+3), *(p+3), p[3], *p++);
    if (argc == 2 && strcmp(argv[1], "lowest") == 0) {
        int *low = lowest_stock(stock, 8);
        printf("Lowest stock: %d units\n", *low);
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "find") == 0) {
        int i = group_index(argv[2]);
        if (i < 0) { fprintf(stderr, "Invalid blood group\n"); return 2; }
        printf("%s stock = %d units\n", groups[i], stock[i]);
        return 0;
    }
    if (argc == 4 && strcmp(argv[1], "issue") == 0) {
        int i = group_index(argv[2]), units = atoi(argv[3]);
        if (i < 0 || units <= 0) { fprintf(stderr, "Invalid group or units\n"); return 2; }
        if (stock[i] < units) { fprintf(stderr, "Insufficient stock\n"); return 3; }
        stock[i] -= units;
        printf("Issued %d units of %s; balance=%d\n", units, groups[i], stock[i]);
        return 0;
    }
    fprintf(stderr, "Usage: %s find GROUP | issue GROUP UNITS | lowest\n", argv[0]);
    return 1;
}
