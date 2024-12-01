#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 1000
#define MAX_LENGTH 20

int Lines(FILE *file, int *stack1, int *stack2);
int calculateSimilarity(int *stack1, int *stack2);

void main()
{
    FILE *file;
    int stack1[MAX_LINES];
    int stack2[MAX_LINES];

    int sum = 0;

    int count = Lines(file, stack1, stack2);
    if (count == 1)
        return;

    sum = calculateSimilarity(stack1, stack2);
    printf("%d \n", sum);
}

int Lines(FILE *file, int *stack1, int *stack2)
{
    char line[MAX_LENGTH * 2];
    int count = 0;
    file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("error");
        return 1;
    }

    while (fgets(line, sizeof(line), file) && count < MAX_LINES)
    {
        sscanf(line, "%d %d", &stack1[count], &stack2[count]);
        count++;
    }
    fclose(file);
    return count;
}

int calculateSimilarity(int *stack1, int *stack2)
{
    int sum = 0;
    for (int i = 0; i < MAX_LINES; i++)
    {
        int occr = 0;
        int num = stack1[i];
        for (int j = 0; j < MAX_LINES; j++)
        {
            if (num == stack2[j])
            {
                occr++;
            }
        }
        sum += num * occr;
    }
    return sum;
}
