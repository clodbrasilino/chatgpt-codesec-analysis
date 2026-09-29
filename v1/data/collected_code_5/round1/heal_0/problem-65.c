#include <stdio.h>

struct Node 
{
    int data;
    struct Node* next;
};

int sumList(struct Node* head) 
{
    if (head == NULL) 
    {
        return 0;
    } 
    else 
    {
        return head->data + sumList(head->next);
    }
}

void insertNode(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    
    if(new_node == NULL)
    {
        printf("Failed to allocate memory for new node.\n");
        exit(EXIT_FAILURE);
    }
    
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int main(void) 
{
    struct Node* head = NULL;

    insertNode(&head, 3);
    insertNode(&head, 2);
    insertNode(&head, 1);
    
    printf("The sum is %d.", sumList(head));
  
    return 0;
}