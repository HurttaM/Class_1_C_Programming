#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/*
Write a program that asks user to enter a number in the range from 0 to 15 or a negative number to
stop. If user enters a number between 0 and 15 the program generates a random number and prints
it in hexadecimal. Then program shifts the number to the right by the amount user entered and uses
bitwise and to clear all other bits except bits 0-5 and prints the result in hexadecimal with two digits
and leading zeros.
Note: bit numbering starts from 0
 */

int read_line(char *buf, int size);                       // fgets + strip newline
int parse_int(const char *s, int *out);                   // parse int from string
unsigned int random_u32(void);                            // 32-bit random number
unsigned int shift_and_mask(unsigned int x, int shift);   // (x >> shift) & 0x3F
void print_hex_u32(unsigned int x);                       // print as 0xXXXXXXXX

int main(void)
{
    char line[64];
    int amount = 0;
    int valid = 1;

    srand((unsigned)time(NULL));

    printf("Enter a number from 0 to 15 (negative to stop):\n");
    valid = read_line(line, sizeof line);

    while (valid && parse_int(line, &amount) && amount >= 0)
    {
        if (amount <= 15)
        {
            unsigned int r = random_u32();
            printf("Random: ");
            print_hex_u32(r);
            printf("\n");

            unsigned int result = shift_and_mask(r, amount);
            printf("Result: 0x%02X\n", result);
        }
        else
        {
            printf("out of range (0..15)\n");
        }

        printf("> ");
        valid = read_line(line, sizeof line);
    }

    return 0;
}


int read_line(char *buf, int size)
{
    if (!fgets(buf, size, stdin))
    {
        return 0;
    }
    size_t n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n')
    {
        buf[n - 1] = '\0';
    }
    return 1;
}

int parse_int(const char *s, int *out)
{
    int tmp;
    char extra;
    if (sscanf(s, " %d %c", &tmp, &extra) == 1)
    {
        *out = tmp;
        return 1;
    }
    return 0;
}

unsigned int random_u32(void)
{
    return ((unsigned int)rand() << 16) ^ (unsigned int)rand();
}

unsigned int shift_and_mask(unsigned int x, int shift)
{
    return (x >> shift) & 0x3Fu;
}

void print_hex_u32(unsigned int x)
{
    printf("0x%08X", x);
}
