/* Q6 - Sort and search a hostel resident directory.
   Names are stored in a 2-D character array. */
#include <stdio.h>
#include <string.h>

#define MAX_NAMES 20
#define NAME_LEN 30

void remove_newline(char s[]) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\\n') s[n - 1] = '\\0';
}
void sort_names(char names[][NAME_LEN], int n) {
    char temp[NAME_LEN];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
            }
        }
    }
}
int binary_search(char names[][NAME_LEN], int n, const char key[]) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int result = strcmp(names[mid], key);
        if (result == 0) return mid;
        if (result < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int main(void) {
    char names[MAX_NAMES][NAME_LEN] = {
        "Ravi", "Anu", "Kiran", "Meena", "Anu", "Zoya"
    };
    int n = 6;
    sort_names(names, n);
    printf("Sorted resident names:\\n");
    for (int i = 0; i < n; i++) printf("%s\\n", names[i]);
    printf("Search Anu: index %d\\n", binary_search(names, n, "Anu"));
    printf("Duplicate names:\\n");
    for (int i = 1; i < n; i++)
        if (strcmp(names[i], names[i - 1]) == 0) printf("%s\\n", names[i]);
    return 0;
}
