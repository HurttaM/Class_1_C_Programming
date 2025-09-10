#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Write a function called print_numbers that takes two parameters: pointer to constant integers and
number of integers to print.
void print_numbers(const int *array, int count);
The function prints the numbers on separate lines in eight characters wide field.
Write a program that defines an array of 15 integers and fills the
 */


void print_numbers(const int *array, int count);

int main() {
    const int NumberOfIntegers = 15;
    int numbers[NumberOfIntegers];
    srand(time(NULL));

    for (int i = 0; i < NumberOfIntegers; i++) {
        numbers[i] = rand() % 10000 + 1 ;

    }

    print_numbers(numbers, NumberOfIntegers);

    return 0;
}

void print_numbers(const int *array, int count) {

    for (int i = 0; i < count; i++) {
        printf("%8d\n", array[i]);
    }


}