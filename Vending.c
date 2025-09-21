#include <stdio.h>
#include "Vending.h"

void displayMenu(Item items[]) {
    printf("\n--- Vending Machine Menu ---\n");
    for (int i = 0; i < ITEMS; i++) {
        printf("%d. %s - %d UGX (%d in stock)\n", i + 1, items[i].name, items[i].price, items[i].stock);
    }
    printf("0. Exit\n");
}