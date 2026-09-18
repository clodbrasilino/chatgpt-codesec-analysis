#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL){
      printf("Failed to allocate memory for new node.\n");
      return;
    }
    
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void insertBefore(struct Node** head_ref, int existing_data, int new_data)
{
    if ((*head_ref) == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current_node = *head_ref;
    struct Node* previous_node = NULL;

    while (current_node != NULL) {
        if (current_node->data == existing_data) {
            struct Node* new_node = malloc(sizeof(struct Node));

            if(new_node == NULL){
              printf("Failed to allocate memory for new node.\n");
              return;
            }

            new_node->data = new_data;
            new_node->next = current_node;

            if (previous_node != NULL){
                previous_node->next = new_node;
            }
            else{
                *head_ref = new_node;
            }
        }

        previous_node = current_node;
        current_node = current_node->next;
    }
}

void printList(struct Node* node)
{
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main()
{
    struct Node* head = NULL;
    push(&head, 2);
    push(&head, 4);
    push(&head, 8);
    push(&head, 16);

    printf("Original list :\n");
    printList(head);

    insertBefore(&head, 4, 3);

    printf("\nModified list :\n");
    printList(head);

    return 0;
}