/* Q1 - Searching a Library Catalogue
   Linear search (unsorted) and binary search (sorted), with comparison counts. */
#include <stdio.h>

int linear_search(const int a[], int n, int key, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (a[i] == key) return i;
    }
    return -1;
}

int binary_search(const int a[], int n, int key, int *comparisons) {
    int low = 0, high = n - 1;
    *comparisons = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparisons)++;
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main(void) {
    int sorted[] = {1021,1048,1103,1190,1222,1305,1377,1402,1460,1533};
    int unsorted[] = {1190,1021,1402,1103,1533,1222,1048,1460,1305,1377};
    int keys[] = {1021,1305,1533,1400};
    int n = (int)(sizeof sorted / sizeof sorted[0]);
    for (int k = 0; k < 4; k++) {
        int c1, c2;
        int p1 = linear_search(unsorted, n, keys[k], &c1);
        int p2 = binary_search(sorted, n, keys[k], &c2);
        printf("Book %d: linear index=%d, comparisons=%d | binary index=%d, comparisons=%d\\n",
               keys[k], p1, c1, p2, c2);
    }
    return 0;
}
