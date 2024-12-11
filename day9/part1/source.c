#include <stdio.h>
#include <stdlib.h>

#define MAX 2500

int linelen = 0;

char *readLine()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    char *buffer = malloc(MAX);
    if (!buffer)
    {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t size = MAX;
    size_t pos = 0;
    int c;

    while ((c = fgetc(file)) != EOF && c != '\n')
    {
        if (pos + 1 >= size)
        {
            size *= 2;
            char *newBuffer = realloc(buffer, size);
            if (!newBuffer)
            {
                perror("Memory reallocation failed");
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = newBuffer;
        }
        buffer[pos++] = c;
    }

    fclose(file);

    if (pos == 0 && c == EOF)
    {
        free(buffer);
        return NULL;
    }

    buffer[pos] = '\0';
    linelen = pos;
    return buffer;
}

int calculateDataSize(const char *line)
{
    int size = 0;
    for (int i = 0; i < linelen; i++)
    {
        size += line[i] - '0';
    }
    return size;
}

void makeDataLine(const char *line, int **dataLine)
{
    int count = 0;
    int id = 0;

    for (int i = 0; i < linelen; i++)
    {
        int repeat = line[i] - '0';

        if (i % 2 != 0)
        {
            for (int j = 0; j < repeat; j++)
            {
                (*dataLine)[count++] = -1;
            }
        }
        else
        {
            for (int j = 0; j < repeat; j++)
            {
                (*dataLine)[count++] = id;
            }
            id++;
        }
    }
}

void compactDisk(int *disk, int *diskSize)
{
    for (int i = 0; i < *diskSize; i++)
    {
        if (disk[i] == -1)
        {
            disk[i] = disk[*diskSize - 1];
            (*diskSize)--;
            while (disk[*diskSize - 1] == -1)
            {
                (*diskSize)--;
            }
        }
    }
}

long long calcCheckSum(int *disk, int diskSize)
{
    long long sum = 0;
    for (int i = 0; i < diskSize; i++)
    {
        sum += (long long)disk[i] * i;
    }
    return sum;
}

int main()
{
    char *line = readLine();
    if (!line)
    {
        fprintf(stderr, "Failed to read line");
        return EXIT_FAILURE;
    }

    int dataSize = calculateDataSize(line);
    int *disk = (int *)malloc(dataSize * sizeof(int));
    if (!disk)
    {
        perror("Memory allocation failed");
        free(line);
        return EXIT_FAILURE;
    }

    makeDataLine(line, &disk);

    // Initial Disk Layout
    printf("Initial Disk Layout: ");
    for (int i = 0; i < dataSize; i++)
    {
        if (disk[i] == -1)
        {
            printf(".");
        }
        else
        {
            printf("%d", disk[i]);
        }
    }
    printf("\n");

    compactDisk(disk, &dataSize);

    printf("Compacted Disk Layout: ");
    for (int i = 0; i < dataSize; i++)
    {
        if (disk[i] == -1)
        {
            printf(".");
        }
        else
        {
            printf("%d", disk[i]);
        }
    }
    printf("\n");

    long long sum = calcCheckSum(disk, dataSize);
    printf("Checksum: %lld\n", sum);

    free(line);
    free(disk);

    return EXIT_SUCCESS;
}
