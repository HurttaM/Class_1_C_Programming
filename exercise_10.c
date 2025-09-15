#include <stdio.h>
#include <string.h>

/*
Write a program that asks user to enter a string. Program must use fgets to read user input and
remove the linefeed at the end of the string. Then program prints the length of the string and checks
if the string is “stop”. If it is the program stops else program asks user to enter a new string (and
prints the length etc.).
 */


char* get_input(char *buffer, int size);

int main () {
    char str[100];

    // initializing to something that is not "stop"
    strcpy(str, "");

    // looping until user types "stop"
    while (strcmp(str, "stop") != 0) {
        printf("Enter a string (or type 'stop' to stop): ");
        get_input(str, sizeof(str));
    }
    return 0;
}




char* get_input(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) != NULL)
        {
        // if newline wasn't stored, flush the rest of the line
            if (strchr(buffer, '\n') == NULL)
            {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            else
            {
            // remove newline if present
                buffer[strcspn(buffer, "\n")] = '\0';
            }

        // print length
            printf("Length: %zu\n", strlen(buffer));
        }
    return buffer; // return pointer to the string
}