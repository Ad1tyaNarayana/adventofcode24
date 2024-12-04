#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 140
#define LINE_LENGTH 141

int getNXMAS(const char matrix[NUM_LINES][LINE_LENGTH])
{
    int count = 0;
    for (int i = 0; i < NUM_LINES; i++)
    {
        for (int j = 0; j < LINE_LENGTH; j++)
        {
            // horizontal
            if (j <= LINE_LENGTH - 4)
            {
                if (matrix[i][j] == 'X' && matrix[i][j + 1] == 'M' && matrix[i][j + 2] == 'A' && matrix[i][j + 3] == 'S')
                    count++;
                if (matrix[i][j] == 'S' && matrix[i][j + 1] == 'A' && matrix[i][j + 2] == 'M' && matrix[i][j + 3] == 'X')
                    count++;
            }

            // vertical down
            if (i <= NUM_LINES - 4)
            {
                if (matrix[i][j] == 'X' && matrix[i + 1][j] == 'M' && matrix[i + 2][j] == 'A' && matrix[i + 3][j] == 'S')
                    count++;
                if (matrix[i][j] == 'S' && matrix[i + 1][j] == 'A' && matrix[i + 2][j] == 'M' && matrix[i + 3][j] == 'X')
                    count++;
            }
            // diagonal bottom right
            if (i <= NUM_LINES - 4 && j <= LINE_LENGTH - 4)
            {
                if (matrix[i][j] == 'X' && matrix[i + 1][j + 1] == 'M' && matrix[i + 2][j + 2] == 'A' && matrix[i + 3][j + 3] == 'S')
                    count++;
                if (matrix[i][j] == 'S' && matrix[i + 1][j + 1] == 'A' && matrix[i + 2][j + 2] == 'M' && matrix[i + 3][j + 3] == 'X')
                    count++;
            }

            // diagonal bottom left
            if (i <= NUM_LINES - 4 && j >= 3)
            {
                if (matrix[i][j] == 'X' && matrix[i + 1][j - 1] == 'M' && matrix[i + 2][j - 2] == 'A' && matrix[i + 3][j - 3] == 'S')
                    count++;
                if (matrix[i][j] == 'S' && matrix[i + 1][j - 1] == 'A' && matrix[i + 2][j - 2] == 'M' && matrix[i + 3][j - 3] == 'X')
                    count++;
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

    int count = getNXMAS(lines);

    printf("%d \n", count);

    return 0;
}