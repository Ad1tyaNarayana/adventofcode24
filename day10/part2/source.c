#include <stdio.h>
#include <stdlib.h>

#define MAX 49

int matrix[MAX][MAX];
int sum = 0;

int isValid(int x, int y, int level)
{
    return (x >= 0 && x < MAX && y >= 0 && y < MAX && matrix[x][y] == level);
}

void findPaths(int x, int y, int level, int *count)
{
    if (level == 9)
    {
        (*count)++;
        return;
    }

    if (isValid(x + 1, y, level + 1))
        findPaths(x + 1, y, level + 1, count);
    if (isValid(x - 1, y, level + 1))
        findPaths(x - 1, y, level + 1, count);
    if (isValid(x, y + 1, level + 1))
        findPaths(x, y + 1, level + 1, count);
    if (isValid(x, y - 1, level + 1))
        findPaths(x, y - 1, level + 1, count);
}

void getTrails()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {

            if (matrix[i][j] == 0)
            {
                int count = 0;
                findPaths(i, j, 0, &count);
                sum += count;
            }
        }
    }
}

int getMatrix(FILE *file)
{
    char line[51];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX)
    {
        for (int i = 0; line[i] != '\0' && line[i] != '\n' && i < MAX; i++)
        {
            matrix[count][i] = line[i] - '0';
        }
        count++;
    }
    return count;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    getMatrix(file);

    getTrails();

    printf("%d\n", sum);

    fclose(file);

    return EXIT_SUCCESS;
}
