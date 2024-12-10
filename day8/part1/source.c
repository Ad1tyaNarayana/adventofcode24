#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 50
#define MAX_NODES 1000

typedef struct
{
    int x, y;
} Point;

char grid[MAX_N][MAX_M];
Point nodes[256][MAX_NODES];
int nodeCount[256];
Point antinodes[MAX_N * MAX_M * MAX_N * MAX_M];
int antinodeCount = 0;

int N, M;

int is_valid(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < M);
}

void add_antinode(int x, int y)
{
    for (int i = 0; i < antinodeCount; i++)
    {
        if (antinodes[i].x == x && antinodes[i].y == y)
        {
            return;
        }
    }

    antinodes[antinodeCount].x = x;
    antinodes[antinodeCount].y = y;
    antinodeCount++;
}

void calculate_antinode(Point pr1, Point pr2)
{
    int x1 = pr1.x, y1 = pr1.y;
    int x2 = pr2.x, y2 = pr2.y;
    int newx = x2 + (x2 - x1);
    int newy = y2 + (y2 - y1);
    if (is_valid(newx, newy))
    {
        add_antinode(newx, newy);
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

    N = 0;
    M = 0;
    while (fgets(grid[N], sizeof(grid[N]), file))
    {
        int len = strlen(grid[N]);
        if (len > 0 && grid[N][len - 1] == '\n')
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

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (grid[i][j] != '.' && grid[i][j] != '\0')
            {
                int nodeIndex = (unsigned char)grid[i][j];
                int count = nodeCount[nodeIndex];
                if (count < MAX_NODES)
                {
                    nodes[nodeIndex][count].x = i;
                    nodes[nodeIndex][count].y = j;
                    nodeCount[nodeIndex]++;
                }
            }
        }
    }

    for (int k = 0; k < 256; k++)
    {
        if (nodeCount[k] > 1)
        {
            for (int i = 0; i < nodeCount[k]; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    Point node1 = nodes[k][i];
                    Point node2 = nodes[k][j];
                    calculate_antinode(node1, node2);
                    calculate_antinode(node2, node1);
                }
            }
        }
    }

    printf("%d\n", antinodeCount + 1);

    return 0;
}