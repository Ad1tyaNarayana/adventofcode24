#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXRULES 1177
#define INITIAL_ARRAY_SIZE 1000

typedef struct
{
    int key;
    int *values;
    int count;
    int capacity;
} NumberMapping;

typedef struct
{
    NumberMapping *mappings;
    int count;
} Rule;

Rule *createMap()
{
    Rule *map = malloc(sizeof(Rule));
    map->mappings = malloc(sizeof(NumberMapping) * MAXRULES);
    map->count = 0;
    return map;
}

NumberMapping *findOrCreateMapping(Rule *map, int key)
{
    // Look for existing mapping
    for (int i = 0; i < map->count; i++)
    {
        if (map->mappings[i].key == key)
        {
            return &map->mappings[i];
        }
    }

    // Create new mapping if not found
    if (map->count < MAXRULES)
    {
        NumberMapping *mapping = &map->mappings[map->count];
        mapping->key = key;
        mapping->values = malloc(sizeof(int) * INITIAL_ARRAY_SIZE);
        mapping->count = 0;
        mapping->capacity = INITIAL_ARRAY_SIZE;
        map->count++;
        return mapping;
    }
    return NULL;
}

// Find mapping for a key
NumberMapping *findMapping(Rule *map, int key)
{
    for (int i = 0; i < map->count; i++)
    {
        if (map->mappings[i].key == key)
        {
            return &map->mappings[i];
        }
    }
    return NULL;
}

// Add value to mapping
void addValue(NumberMapping *mapping, int value)
{
    if (mapping->count >= mapping->capacity)
    {
        mapping->capacity *= 2;
        mapping->values = realloc(mapping->values, sizeof(int) * mapping->capacity);
    }
    mapping->values[mapping->count++] = value;
}

// Free the map and all its resources
void freeMap(Rule *map)
{
    for (int i = 0; i < map->count; i++)
    {
        free(map->mappings[i].values);
    }
    free(map->mappings);
    free(map);
}

void read_rules(FILE *file, Rule *map)
{
    char line[32];
    while (fgets(line, sizeof(line), file))
    {
        int r1, r2;
        if (sscanf(line, "%d|%d", &r1, &r2) == 2)
        {
            NumberMapping *mapping = findOrCreateMapping(map, r1);
            if (mapping != NULL)
            {
                addValue(mapping, r2);
            }
        }
        else if (line[0] == '\n' || line[0] == '\0')
        {
            continue;
        }
        else
        {
            break;
        }
    }
}

int getSumCorrectLines(FILE *file, Rule *map)
{
    int sum = 0;

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strchr(buffer, '|') == NULL)
        {
            break;
        }
    }

    do
    {
        buffer[strcspn(buffer, "\n")] = 0;
        int arr[100];

        // Parse numbers from line
        char *token = strtok(buffer, ",");
        int numCount = 0;
        while (token != NULL && numCount < 100)
        {
            arr[numCount] = atoi(token);
            token = strtok(NULL, ",");
            numCount++;
        }

        int valid = 1;

        // Iterate through each element in the array
        for (int i = 0; i < numCount; i++)
        {
            NumberMapping *mapping = findMapping(map, arr[i]);
            if (mapping == NULL)
            {
                valid = 0;
                break;
            }

            // Check if any previous elements appear in the current mapping's values
            for (int j = 0; j < i; j++)
            {
                int prevValue = arr[j];
                int found = 0;
                for (int k = 0; k < mapping->count; k++)
                {
                    if (mapping->values[k] == prevValue)
                    {
                        found = 1;
                        break;
                    }
                }
                if (found)
                {
                    valid = 0;
                    break;
                }
            }

            if (!valid)
            {
                break;
            }
        }

        if (valid)
        {
            sum += arr[numCount / 2];
        }

    } while (fgets(buffer, sizeof(buffer), file));

    return sum;
}

int main()
{
    Rule *map = createMap();
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    read_rules(file, map);

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    int sum = getSumCorrectLines(file, map);

    printf("sum: %d\n", sum);

    fclose(file);

    // Clean up
    freeMap(map);
    return 0;
}