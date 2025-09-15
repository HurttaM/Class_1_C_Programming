#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
Write a function count_words that takes two strings as a parameter and returns an integer. The
function counts the number of times the second string occurs in the first string and returns the
count. Use strstr() from standard library to find the strings. Note that if the string is found you need
to advance past the current occurrence before searching again. Hint: use a pointer to the string and
use pointer arithmetic to advance it past the current match.
Prototype of the function:
int count_words(const char* str, const char *word);
Write a program that asks user to enter a string and a word. Then program calls count_words and
prints the return value. If the word was “stop” the program stops otherwise it asks user to enter a
string and a word again.
*/

int count_words(const char* str, const char *word);
void to_lower_str(char *s);

int main()
{
    char text[256];
    char word[64];

    while (1) {
        printf("Enter a string: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // remove newline

        printf("Enter of word or a letter to see how many times it comes up (type 'stop' to quit): ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = '\0'; // remove newline

        if (strcmp(word, "stop") == 0)
        {
            return 0; // quit program
        }

        // make lowercase copies for searching
        char text_copy[256];
        char word_copy[64];
        strcpy(text_copy, text);
        strcpy(word_copy, word);
        to_lower_str(text_copy);
        to_lower_str(word_copy);

        int count = count_words(text_copy, word_copy);
        printf("'%s' appeared %d time(s)\n", word_copy, count);

    }
}

int count_words(const char* str, const char* word)
{
    int count = 0;
    const char *p = str;
    size_t wlen = strlen(word);

    if (wlen == 0) return 0; // avoid infinite loop

    while ((p = strstr(p, word)) != NULL)
    {
        count++;
        p += wlen; // move past this occurrence
    }

    return count;
}

void to_lower_str(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        s[i] = tolower((unsigned char)s[i]);
    }
}