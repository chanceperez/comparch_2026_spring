#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t min(size_t x, size_t y) // MIN FUNCTION HERE!!!
{
    return x < y ? x : y;
}

size_t levenshtein_recursive(char *source, char *target)
{ // all the code

    // printf( "source=%s\n", source );
    // printf( "target=%s\n", target );
    int srclength = strlen(source);
    int tarlength = strlen(target);

    int matrix[srclength + 1][tarlength + 1]; // srclength = rows, tarlength = columns?

    // creates a matrix based on the levenshtein function, bottom right determines minimum edits needed(?)

    // recursive takes WAY too long... matrix recommended by professor
    for (int i = 0; i <= srclength; i++)
    {
        matrix[i][0] = i; // first column
    }
    for (int j = 0; j <= tarlength; j++)
    {
        matrix[0][j] = j; // first row
    } // initializes an ixj matrix (0 1 2 3 4 5 etc)
    for (int x = 1; x <= srclength; x++)
    {
        for (int y = 1; y <= tarlength; y++)
        {
            int weight = (source[x - 1] == target[y - 1]) ? 0 : 1; // if letters are equal, don't increase weight. Otherwise increase

            int insert = matrix[x - 1][y] + 1;
            int delete = matrix[x][y - 1] + 1;
            int substitute = matrix[x - 1][y - 1] + weight; // add weight if substitution needed / if letters are different

            matrix[x][y] = min(min(insert, delete), substitute);
        }
    }
    return matrix[srclength][tarlength];
}

int main(int argc, char *argv[])
{

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile)
    {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char source[32];
    char target[32];

    fscanf(inputFile, "%s\n%s", source, target);

    printf("%ld\n", levenshtein_recursive(source, target));

    return EXIT_SUCCESS;
}

/* RESOURCES */
/*
W3Schools: https://www.w3schools.com/c/c_arrays_multi.php

Medium article: https://medium.com/@ethannam/understanding-the-levenshtein-distance-equation-for-beginners-c4285a5604f0

Docusign: https://www.docusign.com/blog/developers/understanding-levenshtein-distance-applications-to-ai-generated-text
(included code samples, did not copy but did read, please let me know if this does not follow academic integrity guidelines (code included c# but not C))

YouTube video: https://www.youtube.com/watch?v=K21k-5s9w6g
(matrix pseudocode for levenshtein)

QUESTION:
G4G: https://www.geeksforgeeks.org/dsa/introduction-to-levenshtein-distance/
Unsure if this fell under "websites that offer ready-made answers clearly specific to this assignment and this class"," so I refrained from using this as a guide.
Please let me know if I'm allowed to use this or if it would fall under academic disintegrity.
*/