#ifndef VENDING_H
#define VENDING_H

// Define the number of items in the vending machine (6 items)
#define ITEMS 6

// Structure to represent an item in the vending machine
typedef struct {
    char name[20]; // Item name (up to 19 characters)
    int price;     // Item price in UGX
    int stock;     // Number of items in stock
} Item;

// Function prototypes for vending machine operations
void displayMenu(Item items[]); // Displays the menu of available items
void calculateChange(int change, int denominations[], int numDenoms); // Calculates and prints change breakdown

#endif
