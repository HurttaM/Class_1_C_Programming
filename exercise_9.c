#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Write a function called find_first that takes two parameters: pointer to constant unsigned integers
and an unsigned integer to find and returns an integer.
int find_first(const unsigned int *array, unsigned int what);
The function searches for the given number in the array until it is found or the current number in the
array is zero. If the number is not found until a zero is seen the program returns -1. If the number is
found function returns the index at which the number was found. Note that we don’t pass the size of
the array as a parameter but we use zero as an end marker to stop at the end of the array.
Write a program that defines an array of 20 integers and fills the first 19 elements with random
numbers in range 1 - 20 and puts a zero as the last number in the array. The program prints the array
one number per line.
Program then asks user to enter number to search for or zero to stop. If the number is not zero
program calls find_first to see if the number occurs in the array. If the number is found it prints the
index where the number is found or “not found”. If user enters zero, the program stops otherwise
program asks again user to enter a number to find.
 */

int read_integer(const char *prompt);
int find_first(const unsigned int *array, unsigned int what);

int main() {
    const int NumberOfIntegers = 20;
    int numbers[NumberOfIntegers];
    srand(time(NULL));

    for (int i = 0; i < NumberOfIntegers -1; i++) {
        numbers[i] = rand() % 20 + 1; //1-20
    }
    numbers[NumberOfIntegers-1] = 0; //last element is 0

    int value;
    do {
        value = read_integer("Enter number to search (0 to stop): "); //getting a value from user
        if (value != 0) {
            int index = find_first(numbers, value);
            if (index == -1) {
                printf("Not found\n");
            } else {
                printf("%u found at index %d\n", value, index);
            }
        }
    } while (value != 0);


    return 0;
}

int read_integer(const char *prompt) {
    int selection = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &selection) == 1) {
            return selection;
        }
        printf("invalid input\n");
        scanf("%*s"); // discard invalid input
    }
}

int find_first(const unsigned int *array, unsigned int what) {
    int i = 0;

    while (1)
    {
        if (array[i] == 0) // reached terminator
        {
            return -1; // not found
        }
        if (array[i] == what) // found it
        {
            return i; // return index
        }
        i++;

    }
}