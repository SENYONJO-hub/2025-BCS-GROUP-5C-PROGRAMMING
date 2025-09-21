#include <stdio.h>
#include "Vending.h"

void calculateChange(int change, int denominations[], int numDenoms) {
    if (change > 0) {
        printf("Your change is %d UGX\n", change);
        printf("Change breakdown: ");
        for (int i = 0; i < numDenoms; i++) {
            int numNotes = change / denominations[i];
            change %= denominations[i];
            if (numNotes > 0) {
                printf("%d x %dUGX ", numNotes, denominations[i]);
            }
        }
        printf("\n\n");
    } else {
        printf("There's no change for your transaction please.\n\n");
    }
}