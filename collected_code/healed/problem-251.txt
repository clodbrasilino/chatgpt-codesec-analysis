#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertBeforeEach(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if(new_node == NULL) {
        printf("Failed to allocate memory for new node");
        return;
    }
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;
   
    insertBeforeEach(&head, 4);
    insertBeforeEach(&head, 3);
    insertBeforeEach(&head, 2);
    insertBeforeEach(&head, 1);
   
    printList(head);
    
    return 0;
}