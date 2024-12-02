#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_NUMS 100

int is_seq_safe(int nums[], int count)
{
    if (count < 2)
        return 0;

    int diff = nums[1] - nums[0];
    if (diff == 0 || abs(diff) > 3)
        return 0;

    int direction = (diff > 0) ? 1 : -1;

    for (int i = 1; i < count - 1; i++)
    {
        diff = nums[i + 1] - nums[i];
        if (diff == 0 || abs(diff) > 3)
            return 0;
        if (((diff > 0) ? 1 : -1) != direction)
            return 0;
    }
    return 1;
}

int is_safe_line(int nums[], int count)
{
    if (is_seq_safe(nums, count))
        return 1;

    for (int i = 0; i < count; i++)
    {
        int temp_nums[MAX_NUMS];
        int temp_count = 0;
        for (int j = 0; j < count; j++)
        {
            if (j != i)
            {
                temp_nums[temp_count++] = nums[j];
            }
        }
        if (is_seq_safe(temp_nums, temp_count))
            return 1;
    }
    return 0;
}

int count_safe_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LENGTH];
    int safe_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        int nums[MAX_NUMS];
        int num_count = 0;
        char *ptr = line;

        while (num_count < MAX_NUMS && sscanf(ptr, "%d", &nums[num_count]) == 1)
        {
            num_count++;

            while (*ptr && *ptr != ' ' && *ptr != '\n')
                ptr++;
            while (*ptr == ' ')
                ptr++;
        }

        if (num_count > 0 && is_safe_line(nums, num_count))
        {
            safe_count++;
        }
    }

    fclose(file);
    return safe_count;
}

int main()
{
    int result = count_safe_lines("input.txt");
    printf("Safe lines: %d\n", result);
    return 0;
}