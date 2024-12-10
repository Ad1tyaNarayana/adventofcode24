#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 52
#define MAX_NODES 1000
#define MAX_CHARS 256

typedef struct
{
    int x, y;
} Point;

int N = 0, M = 0;
char grid[MAX_N][MAX_M];

Point nodes[MAX_CHARS][MAX_NODES];
int nodeCount[MAX_CHARS];

int antinodes[MAX_N][MAX_M];

void antinode(Point pr1, Point pr2)
{
    int x1 = pr1.x, y1 = pr1.y;
    int x2 = pr2.x, y2 = pr2.y;
    int dx = x2 - x1;
    int dy = y2 - y1;

    antinodes[x2][y2] = 1;

    int newx = x2 + dx;
    int newy = y2 + dy;

    while (newx >= 0 && newx < N && newy >= 0 && newy < M)
    {
        antinodes[newx][newy] = 1;
        newx += dx;
        newy += dy;
    }
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("Unable to open file");
        return 1;
    }

    while (fgets(grid[N], sizeof(grid[N]), file))
    {
        int len = strlen(grid[N]);
        if (grid[N][len - 1] == '\n')
        {
            grid[N][len - 1] = '\0';
            len--;
        }
        if (len > M)
        {
            M = len;
        }
        N++;
    }
    fclose(file);

    memset(nodeCount, 0, sizeof(nodeCount));
    memset(antinodes, 0, sizeof(antinodes));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char ch = grid[i][j];
            if (ch != '.' && ch != '\0')
            {
                int idx = (unsigned char)ch;
                nodes[idx][nodeCount[idx]].x = i;
                nodes[idx][nodeCount[idx]].y = j;
                nodeCount[idx]++;
            }
        }
    }

    for (int k = 0; k < MAX_CHARS; k++)
    {
        int L = nodeCount[k];
        if (L > 1)
        {
            for (int i = 0; i < L; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    Point node1 = nodes[k][i];
                    Point node2 = nodes[k][j];
                    antinode(node1, node2);
                    antinode(node2, node1);
                }
            }
        }
    }

    int antinodeCount = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (antinodes[i][j])
            {
                antinodeCount++;
            }
        }
    }

    printf("%d\n", antinodeCount);
    return 0;
}