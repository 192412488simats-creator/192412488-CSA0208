/* Q2 - Sorting the Examination Hall Seating Register
   Bubble sort with early exit, selection sort and insertion sort.
   Each algorithm reports key comparisons and swaps/shifts. */
#include <stdio.h>

void print_array(const int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\\n");
}
void copy_array(int dst[], const int src[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}
void bubble_sort(int a[], int n, long *cmp, long *moves) {
    *cmp = *moves = 0;
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            (*cmp)++;
            if (a[j] > a[j+1]) {
                int t = a[j]; a[j] = a[j+1]; a[j+1] = t;
                (*moves)++; swapped = 1;
            }
        }
        if (!swapped) break;
    }
}
void selection_sort(int a[], int n, long *cmp, long *moves) {
    *cmp = *moves = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*cmp)++;
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            int t = a[i]; a[i] = a[min]; a[min] = t;
            (*moves)++;
        }
    }
}
void insertion_sort(int a[], int n, long *cmp, long *moves) {
    *cmp = *moves = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            (*cmp)++;
            if (a[j] > key) {
                a[j+1] = a[j]; (*moves)++; j--;
            } else break;
        }
        a[j+1] = key;
    }
}
int main(void) {
    int original[] = {45, 12, 38, 7, 29, 18};
    int a[6]; long c, m;
    copy_array(a, original, 6); bubble_sort(a, 6, &c, &m);
    printf("Bubble sort:    "); print_array(a, 6); printf("Comparisons=%ld, swaps=%ld\\n", c, m);
    copy_array(a, original, 6); selection_sort(a, 6, &c, &m);
    printf("Selection sort: "); print_array(a, 6); printf("Comparisons=%ld, swaps=%ld\\n", c, m);
    copy_array(a, original, 6); insertion_sort(a, 6, &c, &m);
    printf("Insertion sort: "); print_array(a, 6); printf("Comparisons=%ld, shifts=%ld\\n", c, m);
    return 0;
}
