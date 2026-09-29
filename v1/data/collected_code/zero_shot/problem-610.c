#include <stdio.h>

// Define a structure for list node
struct Node {
    int data;
    struct Node* next;
};

// Function to remove the k'th element from a given list
void removeKthElement(struct Node** head, int k) {
    // If head is null or k is less than or equal to 0, return
    if (*head == NULL || k <= 0) {
        return;
    }
    
    // If k is 1, remove the head node
    if (k == 1) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    // Traverse the list until k-1th node
    struct Node* current = *head;
    struct Node* previous = NULL;
    
    for (int i = 1; i < k; i++) {
        // If k is greater than the length of the list, return
        if (current == NULL) {
            return;
        }
        previous = current;
        current = current->next;
    }
    
    // If current becomes NULL, return
    if (current == NULL) {
        return;
    }
    
    // Remove the k'th element
    previous->next = current->next;
    free(current);
}

int main() {
    // Create a sample list
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    
    head->data = 1;
    head->next = second;
    
    second->data = 2;
    second->next = third;
    
    third->data = 3;
    third->next = NULL;

    // Print the original list
    printf("Original List: ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    // Remove the k'th element
    int k = 2;
    removeKthElement(&head, k);

    // Print the modified list
    printf("Modified List: ");
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    return 0;
}