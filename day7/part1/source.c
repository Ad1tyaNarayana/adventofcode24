#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 1024

char *readLine(FILE *file)
{
    char *buffer = malloc(MAX);
    if (!buffer)
        return NULL;

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
                free(buffer);
                return NULL;
            }
            buffer = newBuffer;
        }
        buffer[pos++] = c;
    }

    if (pos == 0 && c == EOF)
    {
        free(buffer);
        return NULL;
    }

    buffer[pos] = '\0';
    return buffer;
}

bool tryOP(int numbers[], int num_count, int pos, long long current, long long target)
{
    // Base case - reached end of numbers
    if (pos == num_count)
    {
        return current == target;
    }

    // Try +
    if (tryOP(numbers, num_count, pos + 1, current + numbers[pos], target))
    {
        return true;
    }

    // Try *
    if (tryOP(numbers, num_count, pos + 1, current * numbers[pos], target))
    {
        return true;
    }

    return false;
}

void processNumbers(int numbers[], int num_count, long long target, long long *sum)
{

    if (tryOP(numbers, num_count, 1, numbers[0], target))
    {
        *sum += target;
    }
}

long long calcOP(char *line)
{
    long long target = 0;
    long long sum = 0;
    int numbers[200];
    int num_count = 0;
    char *ptr = line;

    while (*ptr && *ptr != ':')
    {
        if (*ptr >= '0' && *ptr <= '9')
        {
            target = target * 10LL + (*ptr - '0');
        }
        ptr++;
    }

    if (*ptr == ':')
        ptr++;

    char *token = strtok(ptr, " ");
    while (token != NULL && num_count < 200)
    {
        numbers[num_count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    processNumbers(numbers, num_count, target, &sum);
    return sum;
}

long long getSumOP()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("Error opening file");
        return -1;
    }

    long long sum = 0;
    char *line;

    while ((line = readLine(file)))
    {
        sum += calcOP(line);
        free(line);
    }

    fclose(file);
    return sum;
}

int main(void)
{
    long long sum = getSumOP();
    printf("%lld\n", sum);
    return 0;
}