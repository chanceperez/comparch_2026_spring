#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs

int main(int argc, char *argv[])
{

    // First peek at how many jobs and timeslots there are
    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf))
    {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf))
    {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    int timeslots = atoi(buf);

    // We've read the number of timeslots so close the file and start over
    fclose(fp);

    for (unsigned int slot = 0; slot < timeslots; slot++)
    { // for(let i = 0; i < timeslots; i++)
        // going to translate into javascript for my plebeian mind

        FILE *fp = fopen(argv[1], "r");
        if (!fp)
        {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        } // returns error if can't read file

        char buf[256];

        // First read the number of jobs to be scheduled
        if (!fscanf(fp, "%s\n", buf))
        {
            perror("reading the number of jobs failed");
            exit(EXIT_FAILURE);
        }

        // Next read the maximum number of timeslots
        if (!fscanf(fp, "%s\n", buf))
        {
            perror("reading the number of timeslots failed");
            exit(EXIT_FAILURE);
        }

        char bestjob = 'a';
        int bestStart = 10000000; // super brute force for now...
        int bestEnd = 10000000;
        // Now read the rest of the file
        for (int line = 0; line < jobcount; line++)
        { // reads the jobs? can you do for(char job of jobs)?

            if (!fgets(buf, 256, fp))
            {
                perror("reading a line for a job failed");
                exit(EXIT_FAILURE);
            }

            char job;
            unsigned int start;
            unsigned int end; // was returning start time, is there supposed to be a start variable?

            if (!sscanf(buf, "%c %d %d", &job, &start, &end))
            {
                perror("parsing a line for a job failed");
                exit(EXIT_FAILURE);
            }

            if (start == 0) // can't start at time slot 0
                continue;

            // printf("JOB: ");
            // printf("%c\n", job);

            if (start >= slot) // need to do comparison with other jobs for max amount,
            {
                if (end <= bestEnd)
                {
                    if (end == bestEnd && start > bestStart) // a little ugly but should cover everything
                        continue;
                    bestjob = job;
                    bestStart = start;
                    bestEnd = end;
                }
            }
        }
        if (bestjob == 'a')
            continue;
        slot = bestEnd;
        printf("%c\n", bestjob);

        fclose(fp);
    }

    exit(EXIT_SUCCESS);
}

/*RESOURCES USED*/
/*
    GreedyAlgorithms youtube video: https://www.youtube.com/watch?v=Px3oO-kH-I0
    GeeksForGeeks Algorithm examples (NO code copied): https://www.geeksforgeeks.org/cpp/c-cpp-greedy-algorithms-programs/
    (specifically knapsack and jobsequencing, wasn't super helpful though...)

    w3Schools articles (my favorite):
    https://www.w3schools.com/c/ref_stdio_sscanf.php (sscanf summary)
    https://www.geeksforgeeks.org/c/c-program-for-char-to-int-conversion/ (didn't need this but thought I'd need to convert b to 11)


*/