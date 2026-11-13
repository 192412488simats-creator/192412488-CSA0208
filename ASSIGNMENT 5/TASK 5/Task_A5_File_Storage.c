/* Task A5: Donors stored as text; stock stored as fixed-size binary records.
   Files are created in the current working directory. */
#include <stdio.h>
#include <string.h>

typedef struct { int group_code; int units; } Stock;
typedef struct { int id, age; char name[40], group[4]; } Donor;

int update_units(FILE *fp, int index, int units) {
    Stock s;
    if (!fp || index < 0 || units < 0) return 0;
    if (fseek(fp, (long)index * (long)sizeof(Stock), SEEK_SET) != 0) return 0;
    if (fread(&s, sizeof s, 1, fp) != 1) return 0;
    s.units = units;
    if (fseek(fp, -(long)sizeof(Stock), SEEK_CUR) != 0) return 0;
    return fwrite(&s, sizeof s, 1, fp) == 1;
}
int main(void) {
    Donor donors[] = {{1001,25,"Arun","O+"},{1002,22,"Bala","A+"}};
    FILE *tf = fopen("donors.txt", "w");
    if (!tf) { perror("donors.txt"); return 1; }
    for (size_t i=0; i<sizeof donors/sizeof donors[0]; ++i)
        fprintf(tf, "%d|%s|%s|%d\n", donors[i].id, donors[i].name,
                donors[i].group, donors[i].age);
    fclose(tf);

    Stock initial[5] = {{1,40},{2,25},{3,12},{4,8},{5,30}};
    FILE *bf = fopen("stock.dat", "w+b");
    if (!bf) { perror("stock.dat"); return 1; }
    if (fwrite(initial, sizeof(Stock), 5, bf) != 5) {
        perror("fwrite"); fclose(bf); return 1;
    }
    printf("Update stock record 3: %s\n", update_units(bf, 3, 20) ? "success" : "failed");
    rewind(bf);
    Stock s;
    while (fread(&s, sizeof s, 1, bf) == 1)
        printf("Group code %d: %d units\n", s.group_code, s.units);
    fclose(bf);
    return 0;
}
