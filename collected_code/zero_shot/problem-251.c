#include<stdio.h>
#include<stdlib.h>

// Structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to insert an element before each element of a list
void insertBeforeEach(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Function to print the list
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

// Driver program to test above functions
int main() {
    struct Node* head = NULL;
    
    // Create a list with some elements
    insertBeforeEach(&head, 4);
    insertBeforeEach(&head, 3);
    insertBeforeEach(&head, 2);
    insertBeforeEach(&head, 1);
    
    // Print the list
    printList(head);
    
    return 0;
}