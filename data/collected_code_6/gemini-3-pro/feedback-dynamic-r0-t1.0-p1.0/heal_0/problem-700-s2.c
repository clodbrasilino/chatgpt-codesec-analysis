#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int countElementsInRange(const struct Node* head, int minRange, int maxRange) {
    if (head == NULL) {
        return 0;
    }
    if (minRange > maxRange) {
        return 0;
    }

    int count = 0;
    const struct Node* current = head;

    while (current != NULL) {
        if (current->data >= minRange && current->data <= maxRange) {
            count++;
        }
        current = current->next;
    }

    return count;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node* head = createNode(5);
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    head->next = createNode(10);
    head->next->next = createNode(15);
    head->next->next->next = createNode(20);
    head->next->next->next->next = createNode(25);

    int minRange = 10;
    int maxRange = 20;

    int count = countElementsInRange(head, minRange, maxRange);

    printf("%d\n", count);

    freeList(head);

    return EXIT_SUCCESS;
}