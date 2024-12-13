#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <search.h>
#include <assert.h>

// Linked List and HashTable implementation
typedef struct node
{
    int num;
    struct node *next;
    struct node *prev;
} List;

#define HASH_SIZE 1000

unsigned int hash(int key)
{
    return key % HASH_SIZE;
}

List *createNode(int num)
{
    List *newNode = (List *)malloc(sizeof(List));
    newNode->num = num;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void appendNode(List **head, int num)
{
    List *newNode = createNode(num);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    List *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void removeNode(List **head, int position)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    List *temp = *head;

    if (position == 0)
    {
        *head = temp->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }

    for (int i = 0; i < position && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Position out of bounds\n");
        return;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    free(temp);
}

void insertNode(List **head, int num, int position)
{
    List *newNode = createNode(num);
    if (position == 0)
    {
        newNode->next = *head;
        if (*head != NULL)
        {
            (*head)->prev = newNode;
        }
        *head = newNode;
        return;
    }

    List *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL)
    {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

void printList(List *head)
{
    List *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->num);
        temp = temp->next;
    }
    printf("\n");
}

int countNodes(List *head)
{
    int count = 0;
    List *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int countDigits(int num)
{
    return (int)log10(num) + 1;
}

void blink(List **head)
{
    List *temp = *head;
    int pos = 0;

    while (temp != NULL)
    {
        int num = temp->num;
        int digits = countDigits(num);
        List *nextNode = temp->next;

        ENTRY entry;
        entry.key = malloc(25);
        sprintf(entry.key, "%d %d", num, pos);
        ENTRY *result = hsearch(entry, FIND);

        if (result != NULL)
        {
            num = *(int *)result->data;
            free(entry.key);
        }
        else
        {
            if (num == 0)
            {
                num = 1;
            }
            else if (digits % 2 == 0)
            {
                int divisor = (int)pow(10, digits / 2);
                int firstPart = num / divisor;
                int secondPart = num % divisor;
                removeNode(head, pos);
                insertNode(head, firstPart, pos);
                insertNode(head, secondPart, pos + 1);
                pos += 1;
                free(entry.key);
                continue;
            }
            else
            {
                num *= 2024;
            }

            entry.data = malloc(sizeof(int));
            *(int *)entry.data = num;
            hsearch(entry, ENTER);
        }

        removeNode(head, pos);
        insertNode(head, num, pos);

        temp = nextNode;
        pos++;
    }
}

void freeList(List **head)
{
    List *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main()
{
    char line[] = "9759 0 256219 60 1175776 113 6 92833";
    List *head = NULL;

    char *token = strtok(line, " ");
    while (token != NULL)
    {
        int num = atoi(token);
        appendNode(&head, num);
        token = strtok(NULL, " ");
    }

    printList(head);

    int times = 25;
    assert(hcreate(400000));
    for (int i = 0; i < times; i++)
    {
        blink(&head);
    }

    int count = countNodes(head);
    printf("%d\n", count);

    freeList(&head);
    hdestroy();

    return 0;
}