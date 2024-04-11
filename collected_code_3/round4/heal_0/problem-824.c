#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeEven(struct Node** head_ref) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data % 2 == 0) {
            if (prev == NULL) {
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

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;

    push(&head, 7);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);
    push(&head, 5);
    push(&head, 6);

    printf("Given linked list\n");
    printList(head);

    removeEven(&head);

    printf("\nLinked list after removing even numbers\n");
    printList(head);

    return 0;
}