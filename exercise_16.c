#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Write a program that asks user to enter numbers or to enter end to stop entering numbers. If user
enters any other text except end the program prints an error message and discards the input. The
program must store the numbers in a linked list where each node is dynamically allocated.
typedef struct node {
int number;
struct node *next;
} nnode;
When user enters end the program prints all entered numbers, frees the allocated memory and then
ends.
 */


struct node *create_node(int value);             // allocate and init a node
void list_append(struct node **head, int value); // append with double pointer
void list_print(const struct node *head);        // print list contents
void list_free(struct node **head);              // free the whole list
int read_line(char *buf, size_t size);           // read one line, strip newline


typedef struct node {
    int number;
    struct node *next;
} nnode;

int main(void)
{
    nnode *head = NULL;
    char line[128];
    int done = 0;  // loop control flag

    printf("Enter integers (one per line). Type 'end' to finish.\n");

    while (!done)
    {
        printf("");

        if (!read_line(line, sizeof line))
        {
            // EOF: treat like "end"
            done = 1;
        }
        else if (strcmp(line, "end") == 0)
        {
            done = 1;
        }
        else
        {
            int value;
            if (sscanf(line, "%d", &value) == 1)
            {
                list_append(&head, value);
            }
            else
            {
                printf("invalid input\n");
            }
        }
    }

    list_print(head);
    list_free(&head);
    return 0;
}

// ------------------- Function definitions -------------------

// Read one line from stdin, strip trailing newline. Return 1 on success, 0 on EOF.
int read_line(char *buf, size_t size)
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

// Create a new node with given value.
nnode *create_node(int value) {
    nnode *nd = (nnode *)malloc(sizeof *nd);
    if (!nd)
    {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    nd->number = value;
    nd->next = NULL;
    return nd;
}

// Append a new node at the end using double pointer.
void list_append(nnode **head, int value)
{
    while (*head)
    {
        head = &(*head)->next;
    }
    *head = create_node(value);
}

// Print all numbers in the list.
void list_print(const nnode *head)
{
    printf("Numbers entered:\n");
    for (const nnode *p = head; p; p = p->next)
    {
        printf("%d\n", p->number);
    }
}

// Free the whole list and set head to NULL.
void list_free(nnode **head)
{
    nnode *p = *head;
    while (p)
    {
        nnode *next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
}
