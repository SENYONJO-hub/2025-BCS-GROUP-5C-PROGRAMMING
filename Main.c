#include <stdio.h>
#include "Vending.h"
// Headers
#include <stdlib.h>  // For standard library functions
#include <string.h>  // For string manipulation (printf)

// Logs transactions and errors to vending_log.txt for auditing
void logTransaction(const char *message) {
    FILE *logFile = fopen("vending_log.txt", "a");
    if (logFile) {
        fprintf(logFile, "[%s %s] %s\n", __DATE__, __TIME__, message);
        fclose(logFile);
    }
}

// Main function to run the vending machine program
int main() {
    // Tracks invalid inputs to prevent infinite loops
    int invalidInputCount = 0;
    // Maximum allowed invalid inputs before exiting
    const int MAX_INVALID_ATTEMPTS = 5;

    // Initialize array of items with name, price, and stock
    Item items[ITEMS] = {
        {"Water", 1000, 200},
        {"Minutemaid", 2500, 300},
        {"Cakes", 5000, 150},
        {"Biscuits", 2000, 500},
        {"Pepsi", 100, 244},
        {"Bread", 5500, 250}
    };

    // Define available denominations for change calculation
    int denominations[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
    // Calculate number of denominations
    int numDenoms = sizeof(denominations) / sizeof(denominations[0]);

    // Main loop to keep the vending machine running
    while (1) {
        // Check if ITEMS is valid
        if (ITEMS <= 0) {
            printf("Error: Invalid number of items. Exiting.\n");
            logTransaction("Invalid number of items in menu");
            return 1;
        }
        // Check for valid item data (non-empty names)
        for (int i = 0; i < ITEMS; i++) {
            if (items[i].name[0] == '\0') {
                printf("Error: Invalid item data. Exiting.\n");
                logTransaction("Invalid item data in menu");
                return 1;
            }
        }
        // Display the menu of available items
        displayMenu(items);

        // Provide clear instructions for user input
        printf("Instructions: Enter item numbers (1-%d) separated by spaces, end with -1, or 0 to exit.\n", ITEMS);
        // Clear input buffer to prevent stray input issues
        while (getchar() != '\n' && getchar() != EOF);
        // Prompt for item selections
        printf("Enter item number (0 to exit, multiple items separated by spaces, end with -1): ");
        int choice;
        // Array to store selected item numbers
        int selections[50], count = 0;

        // Read item selections until -1 or invalid input
        while (scanf("%d", &choice)) {
            // Check if input is a valid integer
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n' && getchar() != EOF);
                invalidInputCount++;
                // Exit if too many invalid inputs
                if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                    printf("Too many invalid attempts. Exiting.\n");
                    logTransaction("Program exited due to excessive invalid inputs");
                    return 1;
                }
                continue;
            }
            // End selection list if -1 is entered
            if (choice == -1) break;
            // Exit program if 0 is entered
            if (choice == 0) {
                printf("\nThank you for using the vending machine. Goodbye!\n");
                return 0;
            }
            // Check if item number is valid
            if (choice < 1 || choice > ITEMS) {
                printf("Invalid choice: %d. Skipping.\n", choice);
                logTransaction("Invalid item choice entered");
                invalidInputCount++;
                if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                    printf("Too many invalid attempts. Exiting.\n");
                    logTransaction("Program exited due to excessive invalid inputs");
                    return 1;
                }
                continue;
            }
            // Check if selected item is in stock
            if (items[choice - 1].stock == 0) {
                printf("Item %s is out of stock. Skipping.\n", items[choice - 1].name);
                logTransaction("Attempted to select out-of-stock item");
                invalidInputCount++;
                if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                    printf("Too many invalid attempts. Exiting.\n");
                    logTransaction("Program exited due to excessive invalid inputs");
                    return 1;
                }
                continue;
            }
            // Store valid selection
            selections[count++] = choice;
        }

        // Check if any valid items were selected
        if (count == 0) {
            printf("No valid items selected.\n\n");
            continue;
        }

        // Variables for total cost and quantities
        int totalCost = 0;
        int quantities[50];

        // Collect quantities for selected items
        for (int i = 0; i < count; i++) {
            int idx = selections[i] - 1;
            // Clear input buffer before reading quantity
            while (getchar() != '\n' && getchar() != EOF);
            // Prompt for quantity of selected item
            printf("Enter quantity for %s: ", items[idx].name);
            scanf("%d", &quantities[i]);
            // Check if quantity input is a valid integer
            if (scanf("%d", &quantities[i]) != 1) {
                printf("Invalid quantity for %s. Skipping.\n", items[idx].name);
                while (getchar() != '\n' && getchar() != EOF);
                quantities[i] = 0;
                logTransaction("Invalid quantity entered");
                invalidInputCount++;
                if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                    printf("Too many invalid attempts. Exiting.\n");
                    logTransaction("Program exited due to excessive invalid inputs");
                    return 1;
                }
                continue;
            }

            // Check if quantity is positive
            if (quantities[i] <= 0) {
                printf("Invalid quantity. Skipping %s.\n", items[idx].name);
                quantities[i] = 0;
                logTransaction("Invalid quantity entered");
                invalidInputCount++;
                if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                    printf("Too many invalid attempts. Exiting.\n");
                    logTransaction("Program exited due to excessive invalid inputs");
                    return 1;
                }
                continue;
            }
            // Check if enough stock is available
            if (quantities[i] > items[idx].stock) {
                printf("Not enough stock for %s. Available: %d\n", items[idx].name, items[idx].stock);
                quantities[i] = 0;
                logTransaction("Attempted to select excess stock");
                invalidInputCount++;
                if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                    printf("Too many invalid attempts. Exiting.\n");
                    logTransaction("Program exited due to excessive invalid inputs");
                    return 1;
                }
                continue;
            }
            // Calculate cost for this item
            totalCost += items[idx].price * quantities[i];
        }

        // Check if any valid purchases were made
        if (totalCost == 0) {
            printf("No valid purchases made.\n\n");
            continue;
        }

        // Display cart summary
        printf("\n--- Cart Summary ---\n");
        for (int i = 0; i < count; i++) {
            int idx = selections[i] - 1;
            if (quantities[i] > 0) {
                // Print item details and cost
                printf("%s x %d = %d UGX\n", items[idx].name, quantities[i], items[idx].price * quantities[i]);
            }
        }
        // Print total cost
        printf("Total = %d UGX\n", totalCost);

        // Clear input buffer before reading money
        while (getchar() != '\n' && getchar() != EOF);
        // Prompt for money inserted
        printf("Enter amount of money you are inserting (UGX): ");
        int moneyInserted;
        scanf("%d", &moneyInserted);
        // Check if money input is valid and non-negative
        if (scanf("%d", &moneyInserted) != 1 || moneyInserted < 0) {
            printf("Invalid amount entered. Transaction cancelled.\n");
            while (getchar() != '\n' && getchar() != EOF);
            logTransaction("Invalid money amount entered");
            invalidInputCount++;
            if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                printf("Too many invalid attempts. Exiting.\n");
                logTransaction("Program exited due to excessive invalid inputs");
                return 1;
            }
            continue;
        }

        // Check if enough money was inserted
        if (moneyInserted < totalCost) {
            printf("Insufficient funds. Transaction cancelled.\n\n");
            continue;
        }

        // Update stock for purchased items
        for (int i = 0; i < count; i++) {
            int idx = selections[i] - 1;
            items[idx].stock -= quantities[i];
        }

        // Calculate change
        int change = moneyInserted - totalCost;
        // Check if change is negative
        if (change < 0) {
            printf("Error: Negative change calculated. Transaction cancelled.\n");
            logTransaction("Negative change detected");
            invalidInputCount++;
            if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                printf("Too many invalid attempts. Exiting.\n");
                logTransaction("Program exited due to excessive invalid inputs");
                return 1;
            }
            continue;
        }
        // Check if denominations array is valid
        if (numDenoms <= 0) {
            printf("Error: Invalid number of denominations. Transaction cancelled.\n");
            logTransaction("Invalid number of denominations");
            invalidInputCount++;
            if (invalidInputCount >= MAX_INVALID_ATTEMPTS) {
                printf("Too many invalid attempts. Exiting.\n");
                logTransaction("Program exited due to excessive invalid inputs");
                return 1;
            }
            continue;
        }
        // Calculate and display change
        calculateChange(change, denominations, numDenoms);
        // Log successful transaction and reset invalid input counter
        char logMsg[100];
        snprintf(logMsg, sizeof(logMsg), "Transaction completed: Change = %d UGX", change);
        logTransaction(logMsg);
        invalidInputCount = 0;

        // Clear input buffer for next transaction
        while (getchar() != '\n');
    }

    // Return 0 to indicate successful program termination
    return 0;
}
