/*This program is all about applying some key concepts in C programming using this idea of  a Vending Machine Simulator*/
#include <stdlib.h>
#include <stdio.h>
//Structure to represent Vending Machine Items
struct VendingItem{
    char name[50];
    int price;
    int quantity;
};

int main(){
//Initialising Vending Machine Inventory                       
struct VendingItem inventory[] = {
    {"Pepsi",1500,8},
    {"Water",1000,15},
    {"Juice",5500,20}
};
int num_items = sizeof(inventory) / sizeof(inventory[0]);
int choice;
int inserted_money;
int quantity;
printf("Welcome to the 5C's Vending Machine Simulator!\n");
while(1){//Loop for multiple transactions
    printf("\n___Available items;___\n");
        for (int i=0;i<num_items;i++){
            printf("%d. %s - shs%d (quantity: %d)\n", i+1, inventory[i].name, inventory[i].price, inventory[i].quantity);
        }
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    
        if (choice == 0) {
            printf("Exiting...\n");
            break;
        }
        if (choice < 1 || choice > num_items) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
    
        int selected_index = choice - 1;
        if (inventory[selected_index].quantity == 0) {
            printf("Sorry, %s is out of stock.\n", inventory[selected_index].name);
            continue;
        }
    
        printf("Enter the quantity of %s: ", inventory[selected_index].name);
        scanf("%d", &quantity);
    
        if (quantity < 1 || quantity > inventory[selected_index].quantity) {
            printf("Invalid quantity. Please try again.\n");
            continue;
        }
    
        int total_price = inventory[selected_index].price * quantity;
        printf("Please insert money for %s (Total: %d): ", inventory[selected_index].name, total_price);
        scanf("%d", &inserted_money);
    
        if (inserted_money < total_price) {
            printf("Insufficient funds. Please insert more money.\n");
            continue;
        }
    
        // process purchase
        inventory[selected_index].quantity -= quantity;
        int change = inserted_money - total_price;
        
        printf("You purchased %d %s(s). Your change is %d.\n", quantity, inventory[selected_index].name, change);
    }
            return 0;
        }
