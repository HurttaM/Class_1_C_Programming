#include <stdio.h>

/*
Write a program that:
1. Asks user to enter the price of a bus ticket
2. Asks user to enter the price of a taxi trip
3. Asks user to enter how much money he/she has
4. If user has not enough money for either type tells user to walk and then the program stops
5. Asks user to choose taxi or bus (use numbers for selection)
6. Checks if user has enough money for the selected trip type
o If User has enough money reduce the money by the selected trip’s price and print
how much money is left, and go back to step 4
o If user has not enough money for the selected trip type then tell that to user and go
back to step 4
*/

int main(void) {

    double bus_price;
    double taxi_price;
    double money;
    int choice;

    //Asking for the prices of taxi and bus and the amount of money owned
    printf("Enter the price of the bus ticket:\n");
    scanf("%lf", &bus_price);
    printf("Enter the price of the taxi:\n");
    scanf("%lf", &taxi_price);
    printf("How much money do you have?\n");
    scanf("%lf", &money);

    //While user has more money than the price of the bus or taxi the loop continues
    while (bus_price <= money || taxi_price <= money)
    {
        printf("Choose 1 for a bus, 2 for a taxi:\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("You chose a bus.\n");
            if (money >= bus_price) //If more money than the price of bus
            {
                money -= bus_price; //Take bus ticket amount from money
                printf("You have %f money left\n", money);
            }
            else
            {
                printf("Not enough money for a bus. Use a taxi instead. You have %f money left\n", money);
            }
        }
        else if (choice == 2)
        {
            printf("You chose a taxi.\n");
            if (money >= taxi_price) //If more money than the price of bus
            {
                money -= taxi_price;
                printf("You have %f money left\n", money);
            }
            else
            {
                printf("Not enough money for a taxi. Use a bus instead. You have %f money left\n", money);
            }
        }
        else
        {
            printf("Invalid choice. Choose 1 or 2\n");
        }

    }
    printf("No money left for bus or taxi. You need to walk, bye! \n");
    return 0;
}