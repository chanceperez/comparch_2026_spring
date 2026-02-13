#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Struct to hold the open and close braces and the pointer to the next element.
struct element
{
    // char open; // not needed
    char close; // store closing bracket instead of opening?
    struct element *next;
};

// Append the new element to the start of the stack
// This is one potential way to write this function signature
struct element *push( // no stack capacity
    struct element *stack,
    // char open, // not needed
    char close)
{
}

// Remove element from the top of the stack
char pop(struct element **stack) // needs stack as an argument, double pointer too
{

    if (*stack != NULL)
    {
        char popped = (*stack)->close; // Note to self: *a->b means (**a).b - it's SHORTHAND!
    }
    else
    {
        return '\0';
    }
}

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    struct element *root = NULL; // root pointer?
    bool balanced = true;

    char buff;
    while (fscanf(fp, "%c", &buff) == 1)
    { // need break for all cases(?)

        switch (buff)
        {
        case '<':
            root = push(root, '>'); // storing close bracket and matching with each case
            break;
        case '(':
            root = push(root, ')');
            break;
        case '[':
            root = push(root, ']');
            break;
        case '{':
            root = push(root, '}');
            break;
        case '>':
            if (pop(&root) != '>') // pop function needs address of root
                balanced = false;
            break;
        case ')':
            if (pop(&root) != ')')
                balanced = false;
            break;
        case ']':
            if (pop(&root) != ']')
                balanced = false;
            break;
        case '}':
            if (pop(&root) != '}')
                balanced = false;
            break;
        default:
            printf("Invalid character\n");
            break;
        }
    }

    /* ... */

    printf(balanced ? "yes" : "no");
    fclose(fp);
    return 0;
}

/* RESOURCES */
/*
G4G - Stacks: https://www.geeksforgeeks.org/c/implement-stack-in-c/
(also realized I could just use "words words %x", 5 from this example)

G4G - Arrows: https://www.geeksforgeeks.org/c/arrow-operator-in-c-c-with-examples/

G4G - Stacks vs Heaps: https://www.geeksforgeeks.org/dsa/stack-vs-heap-memory-allocation/

Youtube: https://www.youtube.com/watch?v=CM6QPHsPI2I

*/