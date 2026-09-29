#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int count;
    struct node *next;
};

int findMaxSublistLength(struct node *head) {
    struct node *temp = head;
    int maxCount = 0;

    while (temp != NULL) {
        if(temp->count > maxCount) {
            maxCount = temp->count;
        }
        temp = temp->next;
    }

    return maxCount;
}

void push(struct node** head_ref, int new_data, int new_count)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->data  = new_data;
    new_node->count  = new_count;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

int main()
{
    struct node* head = NULL;
    push(&head, 1, 5);
    push(&head, 2, 2);
    push(&head, 3, 9);
    push(&head, 4, 1);

    printf("Max sublist length is %d\n", findMaxSublistLength(head));

    return 0;
}