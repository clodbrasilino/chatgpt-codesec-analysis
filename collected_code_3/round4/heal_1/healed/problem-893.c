#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

int getLast(struct Node* head) {
    struct Node* temp = head;
    if (temp == NULL) {
        fprintf(stderr, "Empty list\n");
        return -1;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}

int main() {
    struct Node* head = NULL;
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);
    printf("Last element is %d\n", getLast(head));
    return 0;
}