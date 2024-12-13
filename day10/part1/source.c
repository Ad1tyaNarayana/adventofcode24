#include <stdio.h>
#include <stdlib.h>

#define MAX 49

int matrix[MAX][MAX];
int sum = 0;

int isValid(int x, int y, int level)
{
    return (x >= 0 && x < MAX && y >= 0 && y < MAX && matrix[x][y] == level);
}

int findsum(int x, int y)
{
    int count = 0;
    int uniqueSet[MAX * MAX] = {0};

    void explore(int px, int py, int level)
    {
        if (level == 9)
        {
            uniqueSet[px * MAX + py] = 1;
            return;
        }

        if (isValid(px + 1, py, level + 1))
            explore(px + 1, py, level + 1);
        if (isValid(px - 1, py, level + 1))
            explore(px - 1, py, level + 1);
        if (isValid(px, py + 1, level + 1))
            explore(px, py + 1, level + 1);
        if (isValid(px, py - 1, level + 1))
            explore(px, py - 1, level + 1);
    }

    explore(x, y, matrix[x][y]);

    for (int i = 0; i < MAX * MAX; i++)
    {
        count += uniqueSet[i];
    }

    return count;
}

void getTrails()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {

            if (matrix[i][j] == 0)
            {
                sum += findsum(i, j);
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

    printf("sum of scores of all trailheads: %d\n", sum);

    fclose(file);

    return EXIT_SUCCESS;
}