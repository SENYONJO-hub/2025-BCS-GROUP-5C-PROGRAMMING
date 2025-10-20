#include <stdio.h>
#include "Vending.h"

int main() {
    Item items[ITEMS] = {
        {"Water", 1000, 200},
        {"Minutemaid", 2500, 300},
        {"Cakes", 5000, 150},
        {"Biscuits", 2000, 500},
        {"Pepsi", 100, 244},
        {"Bread", 5500, 250}
    };

    int denominations[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
    int numDenoms = sizeof(denominations) / sizeof(denominations[0]);

    while (1) {
        displayMenu(items);

        printf("Enter item number (0 to exit, multiple items separated by spaces, end with -1): ");
        int choice;
        char input[100];
        int selections[50], count = 0;
        while (scanf("%s", input) == 1) {
            if (sscanf(input, "%d", &choice) != 1){
                printf("Invalid input: %s. Please enter a anumber.\n", input);
                continue;
            }
            if (choice == -1) break;  // end of list
            if (choice == 0) {
                printf("\nThank you for using the vending machine. Goodbye!\n");
                return 0;
            }
            if (choice < 1 || choice > ITEMS) {
                printf("Invalid choice: %d. Skipping.\n", choice);
                continue;
            }
            selections[count++] = choice;
        }if (count == 0) {
            printf("No valid items selected.\n\n");
            continue;
        }

        int totalCost = 0;
        int quantities[50];

        // Collect quantities
        for (int i = 0; i < count; i++) {
            int idx = selections[i] - 1;
            printf("Enter quantity for %s: ", items[idx].name);
            scanf("%d", &quantities[i]);

            if (quantities[i] <= 0) {
                printf("Invalid quantity. Skipping %s.\n", items[idx].name);
                quantities[i] = 0;
                continue;
            }
            if (quantities[i] > items[idx].stock) {
                printf("Not enough stock for %s. Available: %d\n", items[idx].name, items[idx].stock);
                quantities[i] = 0;
                continue;
            }
            totalCost += items[idx].price * quantities[i];
        }

        if (totalCost == 0) {
            printf("No valid purchases made.\n\n");
            continue;
        }

        printf("\n--- Cart Summary ---\n");
        for (int i = 0; i < count; i++) {
            int idx = selections[i] - 1;
            if (quantities[i] > 0) {
                printf("%s x %d = %d UGX\n", items[idx].name, quantities[i], items[idx].price * quantities[i]);
            }
        }
        printf("Total = %d UGX\n", totalCost);

        int moneyInserted;
        printf("Enter amount of money you are inserting (UGX): ");
        scanf("%d", &moneyInserted);

        if (moneyInserted < totalCost) {
            printf("Insufficient funds. Transaction cancelled.\n\n");
            continue;
        }

        // Update stock
        for (int i = 0; i < count; i++) {
            int idx = selections[i] - 1;
            items[idx].stock -= quantities[i];
        }

        // Handle change
        int change = moneyInserted - totalCost;
        calculateChange(change, denominations, numDenoms);

        // Flush input buffer for next loop
        while (getchar() != '\n');
    }

    return 0;
}