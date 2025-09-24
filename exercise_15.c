#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Write a program that reads data from a text file into an array of structures. The size of the array is 40
elements.
The structure is defined as:
typedef struct menu_item_ {
char name[50];
double price;
} menu_item;
The program asks user to enter a filename. Then program tries to open the file in textmode for
reading. If opening the file fails the program prints an error message with the filename to stderr and
then exits.
Program reads data from the text file into the array until end of file or the array is full. Each row of
the file contains data of one structure. The members are separated by semicolons. For example:
Mega double burger with bacon and cheese; 23.50
Belgian style fries with vegan mayo; 5.60
When reading ends the program closes the file and prints the content of the array in formatted
columns. Price is printed into a field of eight characters with two decimals precision followed by the
name of the item. Unused elements are not printed.
 */

#define MAX_ITEMS 40
#define NAME_MAX 50
#define LINE_MAX 256



typedef struct menu_item_ {
    char name[NAME_MAX];
    double price;
} menu_item;

int read_items(FILE *fp, menu_item items[], int max_items);
void print_items(menu_item items[], int count);

int main(void)
{
    char filename[300];
    FILE *fp;
    menu_item items[MAX_ITEMS];
    int count;

    printf("Enter filename: ");
    if (scanf("%299s", filename) != 1)
    {
        fprintf(stderr, "Error: failed to read filename\n");
        return 1;
    }

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        return 1;
    }

    count = read_items(fp, items, MAX_ITEMS);
    fclose(fp);

    print_items(items, count);

    return 0;
}

int read_items(FILE *fp, menu_item items[], int max_items) {
    char line[LINE_MAX];
    int count = 0;

    while (count < max_items && fgets(line, sizeof line, fp) != NULL) {
        // remove trailing newline if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // find semicolon
        char *semi = strchr(line, ';');
        if (semi != NULL)
        {
            *semi = '\0';  // split name and price

            // copy name safely
            strncpy(items[count].name, line, NAME_MAX - 1);
            items[count].name[NAME_MAX - 1] = '\0';  // always end with '\0'

            // parse price, only accept if valid
            if (sscanf(semi + 1, "%lf", &items[count].price) == 1)
            {
                count++;
            }
            else
            {
                fprintf(stderr, "Skipping line (invalid price): %s\n", line);
            }
        }
        else
        {
            fprintf(stderr, "Skipping line (missing semicolon): %s\n", line);
        }
    }
    return count;
}

//function to print items
void print_items(menu_item items[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%8.2f %s\n", items[i].price, items[i].name);
    }
}