#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input); // input = file number

    // print bits; you will see this kind of for loop often in this assignment
    // for (int bit = sizeof(signed int) * 8 - 1; 0 <= bit; bit--)
    // {
    //     size_t bit_val = ((1 << 1) - 1) & input >> bit * 1; // shift and mask
    //     char character = bit_val ? '1' : '0';
    //     printf("%c", character);
    // }

    printf("%04X", (short)input & 0xFFFF); // 0xFFFF cuts off the other 4 digits for a negative number

    return EXIT_SUCCESS;
}

/* RESOURCES */
/*

conversion - https://log2base2.com/c-questions/io/how-to-print-hexadecimal-in-c.html

digit restriction - https://stackoverflow.com/questions/53153352/can-you-define-a-minimum-and-maximum-amount-of-digits-to-print-from-a-digit-in-c - https://stackoverflow.com/questions/14733761/printf-formatting-for-hexadecimal

masking - https://www.andreinc.net/2023/02/01/demystifying-bitwise-ops

*/