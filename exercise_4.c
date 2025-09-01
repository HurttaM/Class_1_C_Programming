#include <stdio.h>

/*
Write a function called read_integer that takes no parameters and returns an integer. The function
reads a single integer. If the reading fails the function prints “invalid input” and tries to read an
integer again. When an integer is successfully read the function returns the integer.
The declaration of the function is:
int read_integer(void);
Write a program that asks user to enter positive integers or a negative number to stop. The program
must use read_integer-function to read the number. The program calculates and prints the average
of the entered numbers excluding the negative number. For example, if user enters: 1  3  4  2
7 -1, the program prints 3.4 as the average.
The program must print the average with three decimal precision.
 */

int read_integer(void);

int main(void)
{
    int sum = 0;
    int divider = 0;
    int num = 0;

    while (num >= 0)   // treating 0 as a positive number; will count 0 in average
    {
        num = read_integer();
        if (num >= 0)
        {
            sum += num;
            divider++;
        }
        else
        {

        }

    }

    if (divider > 0) {
        double average = (double) sum / divider;
        printf("You entered %d positive numbers. The average is %.3f", divider, average);
    }
    else {
        printf("No positives entered\n");
    }

}

int read_integer(void)
{
    int selection = 0;
    do {
        printf("Enter selection: ");
        if (scanf("%d", &selection) == 1) {
            return selection;
        }
        printf("invalid input\n");
        scanf("%*s");
    } while (1);
}
