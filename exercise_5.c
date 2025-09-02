#include <stdio.h>

/*
Write a function read_range that takes two integer parameters and returns an integer. The function
asks user to enter a number in the range given as parameters. The first parameter is the lowest
acceptable value and the second is the highest acceptable value. When user enters a number the
input is validated in the following ways:
• A number was successfully read
• The number is in the specified range
If the input is invalid then a descriptive error message is printed and user is asked to enter number
again. The function returns only if correct input is given. The function returns the entered number.
The declaration of the function is:
int read_range(int low, int high);
Write a program that “plays” a dice game with user. The game consists of three rounds where
program asks user to roll a die and enter the result (1 – 6). The program must use read_range to
validate input.
The program cheats and always claims to have one higher than what user rolled except when user
rolls six – then program says that it is a tie.
 */

int read_range(int low, int high);

int main() {

    printf("Let's play three rounds!\n");

    for (int round = 1; round < 4; round++)
    {
        int user_roll = read_range(1, 6);

        if (user_roll == 6)
        {
            printf("You rolled a 6. I also rolled a 6. It's a tie!\n");

        }
        else
        {
            int program_roll = user_roll + 1;
            printf("You rolled a %d. I rolled %d, I win!\n", user_roll, program_roll);

        }

        printf("\n"); // extra spacing between rounds
    }

    printf("Better luck next time, bye!\n");

}

int read_range(int low, int high)
{
    int selection = 0;
    do {
        printf("Roll a dice between %d and %d and enter the result: ", low, high);

        if (scanf("%d", &selection) == 1) {
            if (selection >= low && selection <= high) {
                return selection;  // valid input and in range
            } else {
                printf("That number isn't even on the dice... cheater!\n");
            }
        } else {
            printf("That's just nonsense. At least give me a number.\n");
            scanf("%*s");
        }

    } while (1);
}