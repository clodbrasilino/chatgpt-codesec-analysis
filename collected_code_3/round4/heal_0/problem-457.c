#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int findMinLength(struct Node* head) {
    int min_len = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        min_len++;
        temp = temp->next;
    }

    return min_len;
}

int main() {
    struct Node* head = NULL;
    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);

    printf("Minimum length of linked list is %d\n", findMinLength(head));

    return 0;
}