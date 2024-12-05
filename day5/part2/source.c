#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXRULES 1177
#define INITIAL_ARRAY_SIZE 1000
#define MAX_ITERATIONS 100000

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

// Initialize the map
Rule *createMap()
{
    Rule *map = malloc(sizeof(Rule));
    map->mappings = malloc(sizeof(NumberMapping) * MAXRULES);
    map->count = 0;
    return map;
}

// Find or create mapping for a key
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

// Read the rules from the file
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
            // Empty line, skip
            continue;
        }
        else
        {
            // Reached end of rules
            break;
        }
    }
}

bool isValidSequence(int *arr, int numCount, Rule *map)
{
    for (int i = 0; i < numCount; i++)
    {
        NumberMapping *mapping = findMapping(map, arr[i]);
        if (mapping == NULL)
        {
            return false;
        }

        // Check if any previous elements appear in current mapping
        for (int j = 0; j < i; j++)
        {
            int prevValue = arr[j];
            for (int k = 0; k < mapping->count; k++)
            {
                if (mapping->values[k] == prevValue)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to check if value appears in mapping
bool valueInMapping(NumberMapping *mapping, int value)
{
    for (int i = 0; i < mapping->count; i++)
    {
        if (mapping->values[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool fixSequence(int *arr, int length, Rule *map)
{
    int attempts = 0;
    bool madeSwap;

    do
    {
        madeSwap = false;

        for (int i = 0; i < length; i++)
        {
            NumberMapping *mapping = findMapping(map, arr[i]);
            if (!mapping)
            {
                return false;
            }

            for (int j = 0; j < i; j++)
            {
                if (valueInMapping(mapping, arr[j]))
                {
                    // Found rule invalidated: arr[j] appears in mapping of arr[i]
                    // This means arr[i] should come before arr[j]
                    swap(&arr[i], &arr[j]);
                    madeSwap = true;
                    break;
                }
            }

            if (madeSwap)
            {
                break; // Start checking from beginning after swap
            }
        }

        attempts++;
    } while (madeSwap && attempts < 1000);

    return isValidSequence(arr, length, map);
}

int getSumCorrectLines(FILE *file, Rule *map)
{
    int sum = 0;
    char buffer[1000];
    bool foundEmptyLine = false;

    // Skip rules section and find empty line separator
    while (fgets(buffer, sizeof(buffer), file))
    {
        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0 || strchr(buffer, '|') == NULL)
        {
            foundEmptyLine = true;
            break;
        }
    }

    if (!foundEmptyLine)
    {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strlen(buffer) == 0)
        {
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;
        int arr[100];
        int numCount = 0;

        // Parse comma-separated numbers
        char *token = strtok(buffer, ",");
        while (token != NULL && numCount < 100)
        {
            arr[numCount++] = atoi(token);
            token = strtok(NULL, ",");
        }

        if (numCount == 0)
        {
            continue;
        }

        // Store original array for invalid sequences
        int original[100];
        memcpy(original, arr, numCount * sizeof(int));

        bool wasInvalid = !isValidSequence(arr, numCount, map);
        int middleValue = original[numCount / 2];

        if (wasInvalid)
        {
            if (fixSequence(arr, numCount, map))
            {
                int newMiddle = arr[numCount / 2];
                sum += newMiddle;
            }
        }
    }

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