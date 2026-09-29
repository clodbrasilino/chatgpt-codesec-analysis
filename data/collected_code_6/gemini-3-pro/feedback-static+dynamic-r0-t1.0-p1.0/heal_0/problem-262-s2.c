#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void splitList(struct Node* head, int length, struct Node** firstList, struct Node** secondList) {
    if (head == NULL) {
        *firstList = NULL;
        *secondList = NULL;
        return;
    }

    if (length <= 0) {
        *firstList = NULL;
        *secondList = head;
        return;
    }

    struct Node* current = head;
    int count = 1;

    while (current != NULL && count < length) {
        current = current->next;
        count++;
    }

    if (current == NULL) {
        *firstList = head;
        *secondList = NULL;
        return;
    }

    *firstList = head;
    *secondList = current->next;
    current->next = NULL;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int main(void) {
    struct Node* head = NULL;
    struct Node* firstList = NULL;
    struct Node* secondList = NULL;

    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    int splitIndex = 3;

    splitList(head, splitIndex, &firstList, &secondList);

    printList(firstList);
    printList(secondList);

    freeList(firstList);
    freeList(secondList);

    return 0;
}