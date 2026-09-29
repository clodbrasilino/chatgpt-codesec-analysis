#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* removeKthElement(struct Node* head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    if (k == 1) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node* curr = head;
    struct Node* prev = NULL;
    int count = 1;

    while (curr != NULL && count < k) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (curr == NULL) {
        return head;
    }

    prev->next = curr->next;
    free(curr);

    return head;
}

void printList(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        struct Node* temp = curr;
        curr = curr->next;
        free(temp);
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

    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    head = removeKthElement(head, 3);
    printList(head);

    head = removeKthElement(head, 1);
    printList(head);
    
    head = removeKthElement(head, 10);
    printList(head);

    freeList(head);
    return 0;
}