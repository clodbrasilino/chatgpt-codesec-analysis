#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

void push(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

    if (new_node == NULL)
        return;
    
    new_node->data  = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

bool isPresent(struct Node *head, int data)
{
    struct Node *current = head;

    while (current != NULL)
    {
        if (current->data == data)
            return true;

        current = current->next;
    }
    return false;
}

struct Node *getIntersection(struct Node *head1, struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *current1 = head1;

    while(current1 != NULL)
    {
        if(isPresent(head2, current1->data))
            push(&result, current1->data);
        current1 = current1->next;
    }
    return result;
}

void printList(struct Node *node)
{
    struct Node *current = node;
    while (current != NULL)
    {
        printf ("%d ", current->data);
        current = current->next;
    }
}

int main(void) 
{
    struct Node *head1 = (struct Node*) malloc(sizeof(struct Node));
    struct Node *head2 = (struct Node*) malloc(sizeof(struct Node));
    struct Node *intersection;

    if (head1 != NULL) 
    {
        head1->data  = 1;
        head1->next = (struct Node*) malloc (sizeof(struct Node));

        if (head1->next != NULL)
        {
            head1->next->data = 2;
            head1->next->next = (struct Node*) malloc (sizeof(struct Node));

            if (head1->next->next != NULL)
            {
                head1->next->next->data = 3;
                head1->next->next->next = (struct Node*) malloc (sizeof(struct Node));

                if (head1->next->next->next != NULL)
                {
                    head1->next->next->next->data = 4;
                    head1->next->next->next->next  = NULL;
                }
            }
        }
    }

    if (head2 != NULL)
    {
        head2->data  = 1;
        head2->next = (struct Node*) malloc(sizeof(struct Node));

        if (head2->next != NULL)
        {
            head2->next->data = 3;
            head2->next->next = (struct Node*) malloc(sizeof(struct Node));

            if(head2->next->next != NULL)
            {
                head2->next->next->data = 5;
                head2->next->next->next = NULL;
            }
        }
    }
    
    intersection = getIntersection(head1, head2);
    printList(intersection);
    
    return 0;
}