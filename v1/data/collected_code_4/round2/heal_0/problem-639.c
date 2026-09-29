#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    char name[50];
    struct node* next;
};

int sum_name_length(struct node* head)
{
    int sum = 0;
    while(head != NULL)
    {
        if (isupper(head->name[0]))
            sum += strlen(head->name);

        head = head->next;
    }

    return sum;
}

int main()
{
    struct node* head = NULL;
    head = malloc(sizeof(struct node));
    if (head == NULL)
        return 1;

    struct node* current = head;
    for(int i = 0; i < 5; i++)
    {
        printf("Enter name %d\n", i + 1);
        scanf("%s", current->name);

        if(i != 4)
        {
            current->next = malloc(sizeof(struct node));
            if (current->next == NULL)
                return 1;

            current = current->next;
        }
        else
        {
            current->next = NULL;
        }
    }

    printf("Total length: %d\n", sum_name_length(head));

    current = head;
    struct node* next_node;
    while(current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    return 0;
}