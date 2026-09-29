#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if (!new_node)
       return;
       
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void removeNegative(struct Node** head_ref) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if(temp->data < 0) {
            if(prev == NULL) {
                *head_ref = temp->next;
                free(temp);
                temp = *head_ref;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
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