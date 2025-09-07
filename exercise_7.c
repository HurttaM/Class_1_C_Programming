#include <stdio.h>
#include <stdbool.h>

/*
 Write a function named read_positive. The function takes a pointer to int as a parameter and
returns a bool.
bool read_positive(int *value);
The function asks (=prints) user to enter a positive number. If user enters a valid number and the
number is positive the function stores the number using the pointer and returns true. If reading
number fails or number is not positive function returns false without making changes to the value
using pointer.
Write a program that “plays” a guessing game with user. The program asks user to guess how much
money it has and after the guess claims to twice as much plus 20 euros. Program must use the
function above to ask user to enter the number. If reading fails, function returns false, program asks
to enter a number again. Program stops when user has entered an incorrect value three times.
 */

bool read_positive(int *value);

int main() {
 int guess;
 int incorrect_inputs = 0;

 while (incorrect_inputs < 3)
 {
   if (read_positive(&guess))
   {
   int computer_money = 2 * guess + 20;
   printf("You guessed %d euros. I have %d euros. I win!\n", guess, computer_money);
   }
   else
    {
     printf("Incorrect input\n");
     incorrect_inputs++;
    }
 }
 printf("Your guesses are just too bad! I give up!\n");
 return 0;
}

bool read_positive(int *value)
{
 int temp;  // local so we don't modify *value unless input is valid

 printf("Enter a positive number: ");

 if (scanf("%d", &temp) != 1)
  {
    scanf("%*s");
    return false;
  }

 if (temp <= 0)
  {
    return false;
  }
 *value = temp;
 return true;
}