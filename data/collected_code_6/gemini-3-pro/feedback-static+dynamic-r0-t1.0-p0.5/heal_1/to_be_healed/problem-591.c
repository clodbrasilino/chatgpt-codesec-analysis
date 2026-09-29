#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void swapFirstAndLast(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    struct Node* prev = NULL;
    struct Node* curr = *head_ref;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == *head_ref) {
        curr->next = *head_ref;
        (*head_ref)->next = NULL;
        *head_ref = curr;
    } else {
        struct Node* temp = (*head_ref)->next;
        curr->next = temp;
        prev->next = *head_ref;
        (*head_ref)->next = NULL;
        *head_ref = curr;
    }
}

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    struct Node* head = NULL;

    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    swapFirstAndLast(&head);
    printList(head);

    freeList(head);

    return 0;
}