#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[CHAR_BIT]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i = CHAR_BIT - 1; 0 <= i; i--)
    { // read MSB first as that is what comes first in the file
        fscanf(fp, " %c", &buff);
        minuend[i] = (buff == '1');
    }

    // second, read the subtrahend (number to subtract)
    bool subtrahend[CHAR_BIT]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i = CHAR_BIT - 1; 0 <= i; i--)
    { // read MSB first as that is what comes first in the file
        fscanf(fp, " %c", &buff);
        subtrahend[i] = (buff == '1');
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    for (int i = 0; i < sizeof(subtrahend) / sizeof(subtrahend[0]); i++)
    {
        subtrahend[i] = !subtrahend[i];
    }

    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i = 0; i < CHAR_BIT; i++)
    { // iterate from LSB to MSB
        bool newCarry = (subtrahend[i] && carry);
        subtrahend[i] = (subtrahend[i] != carry);

        carry = newCarry;
    }

    // Add the minuend and the negated subtrahend
    bool difference[CHAR_BIT];
    carry = false;
    for (int i = 0; i < CHAR_BIT; i++)
    {                                                                                                       // iterate from LSB to MSB
        bool newCarry = (minuend[i] && subtrahend[i]) || (minuend[i] && carry) || (subtrahend[i] && carry); // should be true if any of them are true
        difference[i] = (subtrahend[i] != carry) != minuend[i];

        carry = newCarry;
    }

    // print the difference bit string
    for (int i = CHAR_BIT - 1; 0 <= i; i--)
        printf("%d", difference[i]);

    return EXIT_SUCCESS;
}

/* RESOURCES */

/*
array length in C (don't ask how I forgot...) - https://www.geeksforgeeks.org/c/length-of-array-in-c/

adding binary w/ booleans - https://www.geeksforgeeks.org/digital-logic/binary-adder-with-logic-gates/

*/