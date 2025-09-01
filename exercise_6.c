#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*
Write a program that prints a menu and asks user to select an operation. The operations are:
• Roll D6
• Roll D10
• Quit
Input must be validated and a descriptive error message must be printed if input is invalid. Rolling
D6 prints a random number in the range of 1 – 6 and rolling D10 prints a random number in the
range of 1 – 10.  If user does not select quit the program prints the menu again.
Use functions to structure your program.

*/
int read_range(int low, int high);

int main()
{
    srand(time(NULL)); //seed random number generator

    int choice;

    do {
        choice = read_range(1, 3);

        if (choice == 1)
        {
            int roll =(rand() % 6) + 1; //random number between 1 and 6
            printf ("You rolled %d\n", roll);
        }
        else if (choice == 2)
        {
            int roll =(rand() % 10) + 1; //random number between 1 and 10
            printf ("You rolled %d\n", roll);
        }

    } while (choice != 3);

    printf("Thank you for playing!\n");

}

int read_range(int low, int high)
{
    int selection = 0;
    do {
        printf("Choose between 1-3.\n 1. Roll a D6\n 2. Roll a D10\n 3. Exit program\n ");

        if (scanf("%d", &selection) == 1) {
            if (selection >= low && selection <= high) {
                return selection;  // valid input and in range
            } else {
                printf("Choose a number between %d and %d.\n", low, high);
            }
        } else {
            printf("That's not a number. Please choose between %d and %d.\n", low, high);
            scanf("%*s");
        }

    } while (1);
}