#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
Write a program that reads lines of text in to an array of strings. The maximum length of the line is
80 characters and the maximum number of lines is 100.
The program asks user to enter a filename. Then program tries to open the file in textmode for
reading. If opening the file fails the program prints an error message with the filename to stderr and
then exits. The program reads lines from the file into the array until the file ends or the array is full
(100 lines read). Then program closes the file.
Then program converts all letters to upper case (see toupper() – function).
Then program opens the file for writing in text mode and writes all read lines to file and closes the
file.
 */

#define MAX_LINES 100
#define MAX_LEN 81 // 80 chars as per exercise + 1 for 'he' terminator

int read_lines(FILE *fp, char lines[][MAX_LEN], int max_lines);
void write_lines(FILE *fp, char lines[][MAX_LEN], int line_count);
void convert_to_uppercase(char lines[][MAX_LEN], int line_count);

int main(void)
{
    char filename[300];
    char lines[MAX_LINES][MAX_LEN]; //
    int line_count = 0;

    // Ask user for filename
    printf("Enter filename (eg. 'numbers.txt'): ");
    if (scanf("%299s", filename) != 1)
    {
        fprintf(stderr, "Error: failed to read filename\n");
        return 1;
    }

    // Open file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: could not open file '%s' for reading\n", filename);
        return 1;
    }

    // Read lines
    line_count = read_lines(fp, lines, MAX_LINES);
    fclose(fp);

    // Convert lines to uppercase
    convert_to_uppercase(lines, line_count);

    // Open file for writing
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: could not open file '%s' for writing\n", filename);
        return 1;
    }

    // Write lines
    write_lines(fp, lines, line_count);
    fclose(fp);

    printf("File '%s' successfully converted to uppercase.\n", filename);

    return 0;
}

//function to read lines from file into array
int read_lines(FILE *fp, char lines[][MAX_LEN], int max_lines)
{
    int count = 0;
    while (count < max_lines && fgets(lines[count], MAX_LEN + 1, fp) != NULL)
    {
        count++;
    }
    return count;
}

//function to write lines from array into file
void write_lines(FILE *fp, char lines[][MAX_LEN], int line_count)
{
    for (int i = 0; i < line_count; i++)
    {
        fputs(lines[i], fp);
    }
}

//function to convert lines to uppercase
void convert_to_uppercase(char lines[][MAX_LEN], int line_count)
{
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; lines[i][j] != '\0'; j++)
        {
            lines[i][j] = toupper((unsigned char)lines[i][j]);
        }
    }
}

