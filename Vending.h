#pragma once 
#define ITEMS 6 /*This line defines ITEMS as a constant with integer 6 meaning that the vending machine is to comprise of 6 items. Note that this value can't be changed during program execution.*/

// Structure to hold item details
typedef struct {
    char name[20];
    int price;
    int stock;
} Item; /* This structure tells us that the items are going to be having a name, price and their number in stock.Item is the data type pointing to the structure.*/
// Function prototypes
void displayMenu(Item items[]);//Declaration of a function that displays vending machine menu.
void calculateChange(int change, int denominations[], int numDenoms);//Declaration of a function that calculates change.


