#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/*
Write a password generator function that takes three parameters: character pointer, integer (size of
the array), a const char pointer (a word) and returns a bool. The function generates password and
stores it in the array and returns true. The length of the generated password is the
*lenght of the word* ×2+1 characters. If the password does not fit in the string function returns false
and does not modify the string.
The password must contain the word given as a parameter so that password starts with a random
printable character and every other letter is a letter from the word and every other is a random
printable character. The password ends with a random printable character. Note that printable
characters are not limited to alphanumerical characters.
Write a program that asks user to enter a word to place in the password or to enter “stop” to stop
the program. The size of the string to read the word into must be 32. If user does not enter stop the
program generates a password using the generator function. If a password is generated successfully
the program prints it otherwise an error message is printed. Then the program asks for another
word.
For example:
User enters: metropolia
Program prints: #m%eGtqrHo&p2o+lBimaY
You don’t need to use colours. They are just a visual aid. The random characters will naturally be
different on your program.
 */

bool generate_password(char *out, int out_size, const char *word);
int read_line(char *buf, int size);
int rand_printable(void);

int main(void)
{
    char word[32];      // buffer for user input word
    char password[64];  // output buffer (enough for word*2+1 + '\0')
    int done = 0;       // loop control flag

    srand((unsigned)time(NULL)); // seed random

    printf("Enter a word (max 31 chars), or 'stop' to quit:\n");

    while (!done)
    {
        printf("> ");
        if (!read_line(word, sizeof(word)))
        {
            // EOF = stop
            done = 1;
        }
        else if (strcmp(word, "stop") == 0)
        {
            done = 1;
        }
        else if (generate_password(password, sizeof(password), word))
        {
            printf("%s\n", password);
        }
        else
        {
            printf("error: output buffer too small\n");
        }
    }

    return 0;
}


// Read one line into buf, strip newline. Return 1 on success, 0 on EOF.
int read_line(char *buf, int size)
{
    if (!fgets(buf, size, stdin))
    {
        return 0;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
    }
    return 1;
}

// Return a random printable ASCII character (codes 33..126).
int rand_printable(void)
{
    return rand() % 94 + 33;
}

/*
Build password of length word_len*2+1.
Pattern: first random, then alternate word[i], random ... ending with random.
Ensure proper null termination. */
bool generate_password(char *out, int out_size, const char *word)
{
    int wlen = (int)strlen(word);
    int need = wlen * 2 + 1;   // visible chars
    int total = need + 1;      // +1 for '\0'

    if (out_size < total)
    {
        return false;
    }

    int pos = 0;

    // start with a random
    out[pos++] = (char)rand_printable();

    // alternate word[i], random
    for (int i = 0; i < wlen; i++)
    {
        out[pos++] = word[i];
        out[pos++] = (char)rand_printable();
    }

    // terminate string
    out[pos] = '\0';

    return true;
}
