#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 131

bool causes_infinite_loop(char matrix[SIZE][SIZE], int obs_x, int obs_y, int start_x, int start_y, int start_dir)
{

    char temp_matrix[SIZE][SIZE];
    memcpy(temp_matrix, matrix, sizeof(char) * SIZE * SIZE);

    temp_matrix[obs_x][obs_y] = '#';

    int x = start_x, y = start_y, dir = start_dir;

    int visited_states[SIZE * SIZE * 4][3];
    int visited_count = 0;

    while (true)
    {

        for (int i = 0; i < visited_count; i++)
        {
            if (visited_states[i][0] == x && visited_states[i][1] == y && visited_states[i][2] == dir)
            {

                return true;
            }
        }

        visited_states[visited_count][0] = x;
        visited_states[visited_count][1] = y;
        visited_states[visited_count][2] = dir;
        visited_count++;

        int nx = x, ny = y;
        switch (dir)
        {
        case 0:
            nx--;
            break;
        case 1:
            ny++;
            break;
        case 2:
            nx++;
            break;
        case 3:
            ny--;
            break;
        }

        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && temp_matrix[nx][ny] != '#')
        {
            x = nx;
            y = ny;
        }
        else
        {

            dir = (dir + 1) % 4;
        }

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        {

            return false;
        }
    }
}

int main()
{

    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Unable to open file");
        return 1;
    }

    char matrix[SIZE][SIZE];
    memset(matrix, 0, sizeof(matrix));
    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < SIZE)
    {
        int i = 0;
        while (line[i] != '\0' && line[i] != '\n' && i < SIZE)
        {
            matrix[count][i] = line[i];
            i++;
        }
        count++;
    }
    fclose(file);

    int rows = count;
    int cols = strlen(matrix[0]);

    int start_x = -1, start_y = -1, start_dir = -1;
    for (int i = 0; i < rows && start_x == -1; i++)
    {
        for (int j = 0; j < cols && start_y == -1; j++)
        {
            char c = matrix[i][j];
            if (c == '^')
            {
                start_x = i;
                start_y = j;
                start_dir = 0;
            }
            else if (c == '>')
            {
                start_x = i;
                start_y = j;
                start_dir = 1;
            }
            else if (c == 'v')
            {
                start_x = i;
                start_y = j;
                start_dir = 2;
            }
            else if (c == '<')
            {
                start_x = i;
                start_y = j;
                start_dir = 3;
            }
        }
    }

    if (start_x == -1 || start_y == -1 || start_dir == -1)
    {
        printf("Starting position not found\n");
        return 1;
    }

    int x = start_x, y = start_y, dir = start_dir;
    bool visited_positions[SIZE][SIZE];
    memset(visited_positions, false, sizeof(visited_positions));
    int steps = 0;
    int inf = 0;

    while (true)
    {
        if (!visited_positions[x][y])
        {
            visited_positions[x][y] = true;
            steps++;
        }

        int new_x = x, new_y = y;
        switch (dir)
        {
        case 0:
            new_x--;
            break;
        case 1:
            new_y++;
            break;
        case 2:
            new_x++;
            break;
        case 3:
            new_y--;
            break;
        }
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && matrix[new_x][new_y] != '#')
        {
            if (causes_infinite_loop(matrix, new_x, new_y, x, y, (dir + 1) % 4))
            {
                inf++;
            }
        }

        int nx = x, ny = y;
        switch (dir)
        {
        case 0:
            nx--;
            break;
        case 1:
            ny++;
            break;
        case 2:
            nx++;
            break;
        case 3:
            ny--;
            break;
        }

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && matrix[nx][ny] != '#')
        {
            x = nx;
            y = ny;
        }
        else
        {

            dir = (dir + 1) % 4;
        }

        if (x < 0 || x >= rows || y < 0 || y >= cols)
        {

            break;
        }
    }

    printf("Total steps: %d\n", steps);

    int distinct_positions = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited_positions[i][j])
            {
                distinct_positions++;
            }
        }
    }
    printf("Distinct positions visited: %d\n", distinct_positions);
    printf("infinite loops %d\n", inf);
    return 0;
}