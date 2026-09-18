#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void rotateLeft(struct Node** head_ref, int k) {
    if (k == 0 || *head_ref == NULL) {
        return;
    }

    struct Node* current = *head_ref;
    int count = 1;

    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }

    if (current == NULL || current->next == NULL) {
        return;
    }

    struct Node* kthNode = current;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = *head_ref;
    *head_ref = kthNode->next;
    kthNode->next = NULL;
}

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
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

    push(&head, 60);
    push(&head, 50);
    push(&head, 40);
    push(&head, 30);
    push(&head, 20);
    push(&head, 10);

    rotateLeft(&head, 4);

    printList(head);

    freeList(head);

    return 0;
}