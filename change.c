#include <stdio.h>
#include "Vending.h"

// Calculates and prints the change breakdown in denominations
void calculateChange(int change, int denominations[], int numDenoms) {
    // Check if there is change to return
    if (change > 0) {
        // Print total change amount
        printf("Your change is %d UGX\n", change);
        // Print header for change breakdown
        printf("Change breakdown: ");
        // Loop through denominations to calculate number of notes/coins
        for (int i = 0; i < numDenoms; i++) {
            int numNotes = change / denominations[i]; // Calculate notes/coins for this denomination
            change %= denominations[i];              // Update remaining change
            // Print only if there are notes/coins to return
            if (numNotes > 0) {
                printf("%d x %dUGX ", numNotes, denominations[i]);
            }
        }
        // Print newlines for formatting
        printf("\n\n");
    } else {
        // Handle case where no change is due (change <= 0)
        printf("There's no change for your transaction please.\n\n");
    }
}
