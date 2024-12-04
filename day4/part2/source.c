#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 140
#define LINE_LENGTH 141

int getXMAS(const char matrix[NUM_LINES][LINE_LENGTH])
{
    int count = 0;
    for (int i = 0; i <= NUM_LINES - 3; i++)
    {
        for (int j = 0; j <= LINE_LENGTH - 3; j++)
        {
            if (matrix[i][j] == 'M')
            {
                // M M
                //  A
                // S S
                if (matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'S' && matrix[i][j + 2] == 'M' && matrix[i + 2][j] == 'S')
                {
                    count++;
                }
                // M S
                //  A
                // M S
                if (matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'S' && matrix[i][j + 2] == 'S' && matrix[i + 2][j] == 'M')
                {
                    count++;
                }
            }
            if (matrix[i][j] == 'S')
            {
                // S M
                //  A
                // S M
                if (matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'M' && matrix[i][j + 2] == 'M' && matrix[i + 2][j] == 'S')
                {
                    count++;
                }
                // S S
                //  A
                // M M
                if (matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'M' && matrix[i][j + 2] == 'S' && matrix[i + 2][j] == 'M')
                {
                    count++;
                }
            }
        }
    }
    return count;
}

int main()
{
    char lines[NUM_LINES][LINE_LENGTH];
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    for (int i = 0; i < NUM_LINES; i++)
    {
        for (int j = 0; j < LINE_LENGTH; j++)
        {
            lines[i][j] = fgetc(file);
            if (lines[i][j] == '\n')
            {
                break;
            }
        }
    }
    fclose(file);

    int count = getXMAS(lines);

    printf("%d \n", count);

    return 0;
}