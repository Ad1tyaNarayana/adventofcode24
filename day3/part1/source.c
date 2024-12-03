#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1024
#define NUM_BUFFER 8

char *readLine(FILE *file)
{
    char *buffer = malloc(MAX);
    if (!buffer)
        return NULL;

    size_t size = MAX;
    size_t pos = 0;
    int c;

    // Read until newline or EOF
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

int isValidNumber(const char *num)
{
    if (!num)
        return 0;

    size_t len = strlen(num);
    if (len < 1 || len > 3)
        return 0;

    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit((unsigned char)num[i]))
            return 0;
    }
    return 1;
}

long long parseMul(const char *line)
{
    long long lineSum = 0;
    const char *pos = line;

    while (*pos)
    {
        if (pos[0] == 'm' && pos[1] == 'u' && pos[2] == 'l' && pos[3] == '(')
        {
            pos += 4;

            int x = 0;
            int digits = 0;
            while (isdigit((unsigned char)*pos) && digits < 3)
            {
                x = x * 10 + (*pos - '0');
                pos++;
                digits++;
            }
            if (digits == 0 || digits > 3)
            {
                pos = strchr(pos, ')');
                if (!pos)
                    break;
                pos++;
                continue;
            }
            if (*pos != ',')
            {
                pos++;
                continue;
            }
            pos++;

            int y = 0;
            digits = 0;
            while (isdigit((unsigned char)*pos) && digits < 3)
            {
                y = y * 10 + (*pos - '0');
                pos++;
                digits++;
                continue;
            }
            if (digits == 0 || digits > 3)
            {
                pos = strchr(pos, ')');
                if (!pos)
                    break;
                pos++;
                continue;
            }
            if (*pos != ')')
            {
                pos++;
                continue;
            }
            pos++;

            lineSum += (long long)x * y;
        }
        else
        {
            pos++;
        }
    }

    return lineSum;
}

long long getSumMul(void)
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
        sum += parseMul(line);
        free(line);
    }

    fclose(file);
    return sum;
}

int main(void)
{
    long long sum = getSumMul();
    printf("%lld\n", sum);
    return 0;
}