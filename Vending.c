#include <stdio.h>
#include "Vending.h"

// Displays the vending machine menu with item details
void displayMenu(Item items[]) {
    // Print menu header
    printf("\n--- Vending Machine Menu ---\n");
    // Loop through all items to display their number, name, price, and stock
    for (int i = 0; i < ITEMS; i++) {
        printf("%d. %s - %d UGX (%d in stock)\n", i + 1, items[i].name, items[i].price, items[i].stock);
    }
    // Print exit option
    printf("0. Exit\n");
}
