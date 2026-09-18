#include <stdio.h>
#include <stdlib.h>

// Struct for list node
struct Node {
    int data;
    struct Node* next;
};

// Function to add a new node at the beginning of list
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Function to remove all negative numbers from the list
void removeNegative(struct Node** head_ref) {
    struct Node* temp = *head_ref, *prev;

    // Check head node (if it holds negative data)
    while (temp != NULL && temp->data < 0) {
        *head_ref = temp->next;
        free(temp);
        temp = *head_ref;
    }
    
    //Check rest of the list (if any node holds Negative data)
    while (temp != NULL) {
        while (temp != NULL && temp->data >= 0) {
            prev = temp;
            temp = temp->next;
        }
        //Break if the list ends
        if (temp == NULL)
            return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

int main() {
    struct Node* head = NULL;
    push(&head, -10);
    push(&head, 20);
    push(&head, -30);
    push(&head, 40);
    push(&head, 50);

    struct Node* temp = head;
    printf("Before removing negative numbers:\n");
    while(temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    
    removeNegative(&head);
    printf("\nAfter removing negative numbers:\n");
    temp = head;
    while(temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return 0;
}