#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int findLength(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct Node* head1 = createNode(1);
    if (head1 == NULL) {
        return 1;
    }
    head1->next = createNode(2);
    if (head1->next == NULL) {
        return 1;
    }
    head1->next->next = createNode(3);
    if (head1->next->next == NULL) {
        return 1;
    }
    head1->next->next->next = createNode(4);
    if (head1->next->next->next == NULL) {
        return 1;
    }

    struct Node* head2 = createNode(1);
    if (head2 == NULL) {
        return 1;
    }
    head2->next = createNode(2);
    if (head2->next == NULL) {
        return 1;
    }

    int length1 = findLength(head1);
    int length2 = findLength(head2);

    if (length1 > length2) {
        printf("List 1 is longer with length %d\n", length1);
    } else if (length1 < length2) {
        printf("List 2 is longer with length %d\n", length2);
    } else {
        printf("Both lists have the same length of %d\n", length1);
    }

    return 0;
}