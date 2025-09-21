#ifndef VENDING_H
#define VENDING_H

#define ITEMS 6

// Structure to hold item details
typedef struct {
    char name[20];
    int price;
    int stock;
} Item;

// Function prototypes
void displayMenu(Item items[]);
void calculateChange(int change, int denominations[], int numDenoms);

#endif