#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 141

typedef struct
{
    int x;
    int y;
} Position;

Position deltas[] = {
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool is_within_grid(int x, int y, int rows, int cols)
{
    return x >= 0 && x < cols && y >= 0 && y < rows;
}

void flood_fill(char **farm, int rows, int cols, Position pos, char plant_type, bool visited[MAX][MAX], int *area, int *perimeter)
{
    if (!is_within_grid(pos.x, pos.y, rows, cols) || visited[pos.y][pos.x] || farm[pos.y][pos.x] != plant_type)
    {
        return;
    }

    visited[pos.y][pos.x] = true;
    (*area)++;

    for (int i = 0; i < 4; i++)
    {
        Position neighbor = {pos.x + deltas[i].x, pos.y + deltas[i].y};

        if (!is_within_grid(neighbor.x, neighbor.y, rows, cols) || farm[neighbor.y][neighbor.x] != plant_type)
        {
            (*perimeter)++;
        }
        else
        {
            flood_fill(farm, rows, cols, neighbor, plant_type, visited, area, perimeter);
        }
    }
}

int calc_total_fencing_price(char **farm, int rows, int cols)
{
    bool visited[MAX][MAX] = {false};
    int total_price = 0;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            if (!visited[y][x])
            {
                char plant_type = farm[y][x];
                int area = 0, perimeter = 0;
                Position start = {x, y};

                flood_fill(farm, rows, cols, start, plant_type, visited, &area, &perimeter);

                int price = area * perimeter;
                total_price += price;
            }
        }
    }

    return total_price;
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        fprintf(stderr, "\n");
        return 1;
    }

    char **farm = malloc(MAX * sizeof(char *));
    for (int i = 0; i < MAX; i++)
    {
        farm[i] = malloc(MAX + 1);
    }

    int rows = 0;
    while (fgets(farm[rows], MAX + 1, file) != NULL && rows < MAX)
    {

        farm[rows][strcspn(farm[rows], "\n")] = '\0';
        rows++;
    }

    fclose(file);

    int cols = strlen(farm[0]);
    int total_fencing_price = calc_total_fencing_price(farm, rows, cols);

    printf("Total Price: %d\n", total_fencing_price);

    for (int i = 0; i < MAX; i++)
    {
        free(farm[i]);
    }
    free(farm);

    return 0;
}
