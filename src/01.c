#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char id[20];
    char name[50];
    int quantity;
    double price;
} Item;

Item items[MAX];
int item_count = 0;

int find_item(char *id) {
    for (int i = 0; i < item_count; i++) {
        if (strcmp(items[i].id, id) == 0) return i;
    }
    return -1;
}

int main() {
    char input[200];

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "---") == 0) break;

        char *cmd = strtok(input, "#");

        if (strcmp(cmd, "receive") == 0) {
            char *id = strtok(NULL, "#");
            char *name = strtok(NULL, "#");
            char *qty_str = strtok(NULL, "#");
            char *price_str = strtok(NULL, "#");

            if (!id || !name || !qty_str || !price_str) continue;

            int qty = atoi(qty_str);
            double price = atof(price_str);

            if (qty <= 0 || price < 0) continue;
            if (find_item(id) != -1) continue;

            strcpy(items[item_count].id, id);
            strcpy(items[item_count].name, name);
            items[item_count].quantity = qty;
            items[item_count].price = price;

            item_count++;
        }

        else if (strcmp(cmd, "report") == 0) {
            for (int i = 0; i < item_count; i++) {
                printf("%s|%s|%d|%.1f\n",
                       items[i].id,
                       items[i].name,
                       items[i].quantity,
                       items[i].price);
            }
        }
    }
    return 0;
}


/