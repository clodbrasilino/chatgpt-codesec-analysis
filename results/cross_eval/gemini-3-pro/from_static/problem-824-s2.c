#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeEvenNumbers(struct Node** head) {
    if (head == NULL || *head == NULL) {
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->data % 2 == 0) {
        *head = temp->next;
        free(temp);
        temp = *head;
    }

    while (temp != NULL) {
        while (temp != NULL && temp->data % 2 != 0) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            return;
        }

        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void push(struct Node** head, int new_data) {
    if (head == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = (*head);
    (*head) = new_node;
}

void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    struct Node* head = NULL;

    push(&head, 6);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printList(head);

    removeEvenNumbers(&head);

    printList(head);

    freeList(head);

    return 0;
}