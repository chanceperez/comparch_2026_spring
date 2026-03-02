#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>
// https://www.cplusplus.com/reference/cfloat/
#include <float.h>

#define FLOAT_SZ sizeof(float) * CHAR_BIT
#define EXP_SZ (FLOAT_SZ - FLT_MANT_DIG)
#define FRAC_SZ (FLT_MANT_DIG - 1)

int main(int argc, char *argv[])
{

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP
    char buff;
    unsigned int multiplier = 0;
    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--)
    { // read MSB first as that is what comes first in the file
        fscanf(fp, " %c", &buff);
        multiplier = multiplier << 1;

        if (buff == '1')
        {
            multiplier = multiplier | 1; // last bit should be 1 either way
        }
    }

    // notice that you are reading two different lines; caution with reading
    /* ... */
    unsigned int multiplicand = 0;
    for (int i = EXP_SZ + FRAC_SZ; 0 <= i; i--)
    { // read MSB first as that is what comes first in the file
        fscanf(fp, " %c", &buff);
        multiplicand = multiplicand << 1;

        if (buff == '1')
        {
            multiplicand = multiplicand | 1; // last bit should be 1 either way
        }
    }

    // first, read the binary number representation of multiplcand
    bool signMultiplier = (multiplier >> 31) & 1;
    bool signMultiplicand = (multiplicand >> 31) & 1;

    int expMultiplier = ((multiplier >> 23) & 0xFF) - 127;
    int expMultiplicand = ((multiplicand >> 23) & 0xFF) - 127;

    float product = *(float *)&multiplier * *(float *)&multiplicand; // you are not allowed to print from this.
    unsigned int ref_bits = *(unsigned int *)&product;               // you are not allowed to print from this. But you can use it to validate your solution. //thanks professor preciate it

    // SIGN
    bool sign = signMultiplier != signMultiplicand;
    printf("%d_", sign);
    assert(sign == (1 & ref_bits >> (EXP_SZ + FRAC_SZ)));

    // EXP
    // get the exp field of the multiplier and multiplicand
    // add the two exp together
    // subtract bias //do I need to subtract the bias again? //no
    int expProduct = expMultiplier + expMultiplicand;

    // FRAC
    // get the frac field of the multiplier and multiplicand //unused?
    // int fracMultiplier = multiplier & 0x7FFFFF; // 7FFFFF = 23
    // int fracMultiplicand = multiplicand & 0x7FFFFF;
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    double mantissaMultiplier = 1.0 + (multiplier & 0x7FFFFF) / (double)(1 << 23);
    double mantissaMultiplicand = 1.0 + (multiplicand & 0x7FFFFF) / (double)(1 << 23);
    // multiply the mantissas
    double mantissaProduct = mantissaMultiplicand * mantissaMultiplier;

    // overflow and normalize
    while (mantissaProduct >= 2 || mantissaProduct < 1)
    {
        if (mantissaProduct >= 2)
        {
            mantissaProduct /= 2;
            expProduct += 1;
        }
        else
        {
            mantissaProduct *= 2;
            expProduct -= 1;
        }
    }

    int fraction = 0;
    double fractionProduct = mantissaProduct - 1.0;

    // move decimal point
    for (int i = 0; i < FRAC_SZ; i++)
    {
        fractionProduct *= 2;
        fraction = fraction << 1;
        if (fractionProduct >= 1.0)
        {
            fraction = fraction | 1;
            fractionProduct -= 1.0;
        }
    }

    // rounding //should I round before or after? //EDIT: works after moving rounding to be AFTER decimal point moving.
    if (fractionProduct >= 0.5)
    {
        fraction += 1;
        if (fraction > 0x7FFFFF)
        {
            fraction = 0;
            expProduct += 1;
        }
    }

    int exp = expProduct + 127; // add bias back for printing
    int frac = fraction;

    // PRINTING
    // print exp
    for (int bit_index = EXP_SZ - 1; 0 <= bit_index; bit_index--)
    {
        bool trial_bit = 1 & exp >> bit_index;
        printf("%d", trial_bit);
        assert(trial_bit == (1 & ref_bits >> (bit_index + FRAC_SZ)));
    }
    printf("_");

    // print frac
    for (int bit_index = FRAC_SZ - 1; 0 <= bit_index; bit_index--)
    {
        bool trial_bit = 1 & frac >> bit_index;
        printf("%d", trial_bit);
        assert(trial_bit == (1 & ref_bits >> (bit_index)));
    }

    return (EXIT_SUCCESS);
}
