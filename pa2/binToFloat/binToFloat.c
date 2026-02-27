#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[])
{

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    unsigned int binary = 0;
    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--)
    { // read MSB first as that is what comes first in the file
        fscanf(fp, " %c", &buff);
        binary = binary << 1;

        if (buff == '1')
        {
            binary = binary | 1; // last bit should be 1 either way
        }
    }

    // float number = *(float *)&binary; // you are not allowed to do this. //thank you for letting me know

    bool sign = (binary >> 31) & 1; // reads the sign digit

    // E
    int e = ((binary >> 23) & 0xFF) - 127; // reads the 8 exponend digits

    // M
    double m = 1 + (binary & 0x7FFFFF) / (double)(1 << 23);

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp(m, e);
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;
}

/* RESOURCES */

/*
Binary reading - https://www.geeksforgeeks.org/computer-organization-architecture/ieee-standard-754-floating-point-numbers/

operations - https://www.geeksforgeeks.org/c/bitwise-operators-in-c-cpp/
*/