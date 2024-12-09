#include <stdio.h>

int main()
{

    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Unable to open file");
        return 1;
    }

    char matrix[131][131];
    char line[256];
    int count = 0;

    // Read the file line by line into the matrix
    while (fgets(line, sizeof(line), file))
    {
        int i = 0;
        while (line[i] != '\0' && line[i] != '\n')
        {
            matrix[count][i] = line[i];
            i++;
        }
        matrix[count][i] = '\0'; // Null terminate the string in the matrix
        count++;
    }

    fclose(file);
    int steps = 0;
    int end = 1;
    int dir = 0; // 0: up, 1: right, 2: down, 3: left
    int x = -1, y = -1;

    int ox = -1, oy = -1;

    // Find the starting position '^'
    for (int i = 0; i < count && x == -1; i++)
    {
        for (int j = 0; j < 131 && y == -1; j++)
        {
            if (matrix[i][j] == '^')
            {
                x = i;
                y = j;
                ox = i;
                oy = j;
                break;
            }
        }
    }

    if (x == -1 || y == -1)
    {
        printf("Starting position '^' not found\n");
        return 1;
    }

    while (end)
    {
        switch (dir)
        {
        case 0:
            if (x > 0 && matrix[x - 1][y] != '#')
            {
                x--;
            }
            else
            {
                dir = (dir + 1) % 4;
            }
            break;
        case 1:
            if (y < 130 && matrix[x][y + 1] != '#')
            {
                y++;
            }
            else
            {
                dir = (dir + 1) % 4;
            }
            break;
        case 2:
            if (x < 130 && matrix[x + 1][y] != '#')
            {
                x++;
            }
            else
            {
                dir = (dir + 1) % 4;
            }
            break;
        case 3:
            if (y > 0 && matrix[x][y - 1] != '#')
            {
                y--;
            }
            else
            {
                dir = (dir + 1) % 4;
            }
            break;
        }

        if (matrix[x][y] != 'X')
        {
            matrix[x][y] = 'X';
            steps++;
        }

        if (x == 0 || x == 130 || y == 0 || y == 130)
        {
            end = 0;
        }
    }

        printf("Total steps: %d\n", steps);

    return 0;
}