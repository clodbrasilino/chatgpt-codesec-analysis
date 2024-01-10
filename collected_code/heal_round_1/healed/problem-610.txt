#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeKthElement(struct Node** head, int k) {
    if (*head == NULL || k <= 0) {
        return;
    }
    
    if (k == 1) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    struct Node* current = *head;
    struct Node* previous = NULL;
    
    for (int i = 1; i < k; i++) {
        if (current == NULL) {
            return;
        }
        previous = current;
        current = current->next;
    }
    
    if (current == NULL || previous == NULL) {
        return;
    }
    
    previous->next = current->next;
    free(current);
}

int main() {
    struct Node* head = malloc(sizeof(struct Node));
    struct Node* second = malloc(sizeof(struct Node));
    struct Node* third = malloc(sizeof(struct Node));
    
    if(head == NULL || second == NULL || third == NULL){
        return -1;
    }

    head->data = 1;
    head->next = second;
    
    second->data = 2;
    second->next = third;
    
    third->data = 3;
    third->next = NULL;

    printf("Original List: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    int k = 2;
    removeKthElement(&head, k);

    printf("Modified List: ");
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    return 0;
}