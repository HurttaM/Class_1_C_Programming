#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*
 Write a program that asks user to enter a filename. Then program tries to open the file in textmode
for reading. If opening the file fails the program prints an error message with the filename to stderr
and then exits. If the file is opened the program starts reading integers from the file until reading
fails or the file ends. When reading stops the program prints the count of numbers and the lowest
and highest number that was read from the file. Then program closes the file.
For testing make a few text files with integers using your favourite text editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void read_numbers_from_file(const char *filename, int *count, int *min, int *max);

int main(void) {
    char filename[300];
    int count, min, max;

    printf("Enter filename (eg. 'numbers.txt'): ");
    if (scanf("%299s", filename) != 1)
    {
        fprintf(stderr, "Error: failed to read filename\n");
        return 1;
    }

    read_numbers_from_file(filename, &count, &min, &max);

    if (count > 0)
    {
        printf("Count: %d\nLowest: %d\nHighest: %d\n", count, min, max);
    }
    else
    {
        printf("Count: 0\nNo integers read from file.\n");
    }
    return 0;
}

void read_numbers_from_file(const char *filename, int *count, int *min, int *max)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: could not open '%s'\n", filename);
        exit(1); // required to exit if opening fails
    }

    int value;
    *count = 0;
    *min = INT_MAX;
    *max = INT_MIN;

    while (fscanf(fp, "%d", &value) == 1)
    {
        if (value < *min) *min = value;
        if (value > *max) *max = value;
        (*count)++;
    }


    // Check why the loop stopped
    if (feof(fp))
    {
        printf("File read in its entirety.\n");
    } else
    {
        printf("Stopped reading: encountered a non-integer in the file.\n");
    }

    fclose(fp);
}
