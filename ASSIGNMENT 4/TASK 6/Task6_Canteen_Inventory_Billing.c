/* TASK 6 - College canteen inventory and billing using structures and a tagged union */
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_SALES 50

typedef struct { int day, month, year; } Date;
typedef struct { int hour, minute; } Time;

enum ItemType { PACKAGED, COOKED, COMBO };

typedef struct {
    Date expiry;
} PackagedInfo;

typedef struct {
    Time prepared;
} CookedInfo;

typedef struct {
    int componentIds[3];
    int componentCount;
} ComboInfo;

typedef struct {
    int id;
    char name[30];
    enum ItemType type;
    float price;
    int stock;
    union {
        PackagedInfo packaged;
        CookedInfo cooked;
        ComboInfo combo;
    } details;
} Item;

typedef struct {
    int itemId;
    int quantity;
    float revenue;
} Sale;

int find_item(Item items[], int n, int id) {
    for (int i = 0; i < n; i++) if (items[i].id == id) return i;
    return -1;
}

int record_sale(Item items[], int n, Sale sales[], int *saleCount,
                int id, int quantity) {
    int index = find_item(items, n, id);
    if (index < 0) {
        printf("Sale rejected: item %d not found.\n", id);
        return 0;
    }
    if (quantity <= 0 || quantity > items[index].stock) {
        printf("Sale rejected: insufficient stock for %s (available %d).\n",
               items[index].name, items[index].stock);
        return 0;
    }
    items[index].stock -= quantity;
    sales[*saleCount].itemId = id;
    sales[*saleCount].quantity = quantity;
    sales[*saleCount].revenue = quantity * items[index].price;
    (*saleCount)++;
    printf("Sale recorded: %s x%d = Rs. %.2f\n",
           items[index].name, quantity, quantity * items[index].price);
    return 1;
}

/* Simple date comparison for dates in the same month/year demonstration. */
int expires_within_two_days(Date expiry, Date today) {
    if (expiry.year != today.year || expiry.month != today.month) return 0;
    return expiry.day >= today.day && expiry.day <= today.day + 2;
}

void expiry_warning(const Item items[], int n, Date today) {
    puts("Expiry warnings:");
    for (int i = 0; i < n; i++) {
        if (items[i].type == PACKAGED &&
            expires_within_two_days(items[i].details.packaged.expiry, today)) {
            printf("%s expires on %02d/%02d/%04d\n", items[i].name,
                   items[i].details.packaged.expiry.day,
                   items[i].details.packaged.expiry.month,
                   items[i].details.packaged.expiry.year);
        }
    }
}

void print_revenue_summary(const Item items[], int n,
                           const Sale sales[], int saleCount) {
    float revenue[MAX_ITEMS] = {0};
    int order[MAX_ITEMS];
    for (int i = 0; i < n; i++) order[i] = i;
    for (int s = 0; s < saleCount; s++) {
        int index = find_item((Item *)items, n, sales[s].itemId);
        if (index >= 0) revenue[index] += sales[s].revenue;
    }
    for (int i = 0; i < n - 1; i++) {
        int best = i;
        for (int j = i + 1; j < n; j++)
            if (revenue[order[j]] > revenue[order[best]]) best = j;
        int temp = order[i]; order[i] = order[best]; order[best] = temp;
    }
    puts("Revenue summary (highest first):");
    for (int i = 0; i < n; i++)
        printf("%-15s Rs. %.2f\n", items[order[i]].name, revenue[order[i]]);
}

int main(void) {
    Item items[4] = {
        {1, "Milk Packet", PACKAGED, 30.0f, 10, {.packaged = {{15, 10, 2026}}}},
        {2, "Sandwich", COOKED, 50.0f, 8, {.cooked = {{10, 30}}}},
        {3, "Combo Meal", COMBO, 90.0f, 5, {.combo = {{1, 2}, 2}}},
        {4, "Juice", PACKAGED, 25.0f, 6, {.packaged = {{16, 10, 2026}}}}
    };
    Sale sales[MAX_SALES];
    int saleCount = 0;
    Date today = {13, 10, 2026};

    record_sale(items, 4, sales, &saleCount, 1, 2);  /* normal sale */
    record_sale(items, 4, sales, &saleCount, 2, 20); /* exceeds stock */
    record_sale(items, 4, sales, &saleCount, 3, 1);
    expiry_warning(items, 4, today);
    print_revenue_summary(items, 4, sales, saleCount);
    return 0;
}
