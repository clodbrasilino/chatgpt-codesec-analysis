#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->data  = new_data;
    new_node->next = (*head_ref);

    (*head_ref) = new_node;
}

void printList(struct Node *node)
{
    while(node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}

void splitList(struct Node* source, struct Node** frontRef, struct Node** backRef, int length)
{
    struct Node* fast;

    if(source == NULL || source->next == NULL)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        fast = source;

        int count = 1;
        while(count < length)
        {
            if(fast == NULL)
                break;

            fast = fast->next;
            count++;
        }
        *frontRef = source;
        *backRef = fast->next;
        fast->next = NULL;
    }
}

int main()
{
    struct Node* head = NULL;
    struct Node* a = NULL;
    struct Node* b = NULL;

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    push(&head, 6);

    printf("Original linked List: ");
    printList(head);

    int length = 3;
    splitList(head, &a, &b, length);

    printf("\nFirst part: ");
    printList(a);

    printf("\nSecond part: ");
    printList(b);

    return 0;
}