/* Task A4: Growable donor array using realloc with safe failure handling */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int id, age; char name[50], group[4]; } Donor;
typedef struct { Donor *data; size_t size, capacity; } DonorList;

int add_donor(DonorList *list, Donor d) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 2 : list->capacity * 2;
        Donor *p = realloc(list->data, new_capacity * sizeof *p);
        if (p == NULL) return 0; /* old allocation remains valid */
        list->data = p;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = d;
    return 1;
}
int main(void) {
    DonorList list = {NULL, 0, 0};
    for (int i = 0; i < 5; ++i) {
        Donor d = {7001+i, 20+i, "Sample Donor", "O+"};
        if (!add_donor(&list, d)) {
            perror("realloc"); free(list.data); return 1;
        }
        printf("Added %d: size=%zu capacity=%zu\n",
               list.data[list.size-1].id, list.size, list.capacity);
    }
    free(list.data);
    list.data = NULL; list.size = list.capacity = 0;
    return 0;
}
