#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head_ref, int data) {
    struct Node* newNode = createNode(data);
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    struct Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
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

void rotateLeft(struct Node** head_ref, int k) {
    if (k == 0 || *head_ref == NULL || (*head_ref)->next == NULL) {
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

int main(void) {
    struct Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);
    appendNode(&head, 60);

    rotateLeft(&head, 4);

    printList(head);

    freeList(head);

    return 0;
}