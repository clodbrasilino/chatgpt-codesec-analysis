#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void swap(struct Node **head_ref)
{
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    struct Node* first = *head_ref;
    struct Node* last = *head_ref;
    struct Node* prev = NULL;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    prev->next = first;
    *head_ref = last;
    last->next = first->next;
    first->next = NULL;
}

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main()
{
    struct Node* start = NULL;

    int arr[] = {1, 2, 3, 4, 5};
    int i;
    for (i = 4; i >=0; i--)
       push(&start, arr[i]);

    printf("\n Linked list before swapping\n");
    printList(start);

    swap(&start);

    printf("\n Linked list after swapping\n");
    printList(start);

    return 0;
}