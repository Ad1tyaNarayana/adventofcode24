#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 1000
#define MAX_LENGTH 20

int Lines(FILE *file, int *stack1, int *stack2);
void insertSorted(int *arr, int n, int value);
int calculateDistance(int *stack1, int *stack2);

void main()
{
    FILE *file;
    int stack1[MAX_LINES];
    int stack2[MAX_LINES];

    int sum = 0;

    int count = Lines(file, stack1, stack2);
    if (count == 1)
        return;

    sum = calculateDistance(stack1, stack2);
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
        int num1, num2;
        sscanf(line, "%d %d", &num1, &num2);
        insertSorted(stack1, count, num1);
        insertSorted(stack2, count, num2);
        count++;
    }
    fclose(file);
    return count;
}

void insertSorted(int *arr, int n, int value)
{
    int i;

    for (i = n - 1; (i >= 0 && arr[i] > value); i--)
    {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = value;
}

int calculateDistance(int *stack1, int *stack2)
{
    int sum = 0;
    for (int i = 0; i < MAX_LINES; i++)
    {
        sum += abs(stack1[i] - stack2[i]);
    }
    return sum;
}
