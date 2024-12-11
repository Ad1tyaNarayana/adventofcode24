#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FILE_NAME "input.txt"

typedef struct FileNode FileNode;

struct FileNode
{
    int id;
    int size;
    int freeSpace;
    FileNode *next;
    FileNode *prev;
};

char *readInputFromFile(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror("Error opening file");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *str = (char *)malloc(fileSize + 1);
    if (str)
    {
        fread(str, 1, fileSize, f);
        str[fileSize] = '\0';
    }
    fclose(f);

    return str;
}

int main()
{

    char *str = readInputFromFile(FILE_NAME);
    if (str == NULL)
    {
        return EXIT_FAILURE;
    }

    int len = strlen(str);

    FileNode *start = calloc(1, sizeof(FileNode));
    start->id = 0;
    start->size = str[0] - '0';
    start->freeSpace = str[1] - '0';

    FileNode *end = start;

    for (int i = 2; i < len; i += 2)
    {
        FileNode *newEnd = calloc(1, sizeof(FileNode));
        newEnd->id = i / 2;
        newEnd->size = str[i] - '0';
        if (i + 1 < len)
        {
            newEnd->freeSpace = str[i + 1] - '0';
        }
        end->next = newEnd;
        newEnd->prev = end;
        end = newEnd;
    }

    FileNode *n1 = end;
    while (n1 != NULL)
    {
        FileNode *prev = n1->prev;

        for (FileNode *n2 = start; n2 != n1 && n2 != NULL; n2 = n2->next)
        {
            if (n2->freeSpace >= n1->size)
            {
                if (n1->prev != NULL)
                {
                    n1->prev->next = n1->next;
                    n1->prev->freeSpace += n1->size + n1->freeSpace;
                }
                if (n1->next != NULL)
                {
                    n1->next->prev = n1->prev;
                }

                if (n2->next != NULL)
                {
                    n2->next->prev = n1;
                    n1->next = n2->next;
                }
                n1->freeSpace = n2->freeSpace - n1->size;
                n2->freeSpace = 0;
                n2->next = n1;
                n1->prev = n2;
                break;
            }
        }
        n1 = prev;
    }

    long sum = 0;
    int position = 0;
    for (FileNode *n = start; n != NULL; n = n->next)
    {
        for (int i = 0; i < n->size; i++)
        {
            sum += n->id * position;
            position++;
        }
        for (int i = 0; i < n->freeSpace; i++)
        {
            position++;
        }
    }

    printf("%ld\n", sum);

    FileNode *n = start;
    while (n != NULL)
    {
        FileNode *toFree = n;
        n = n->next;
        free(toFree);
    }

    free(str);

    return 0;
}
