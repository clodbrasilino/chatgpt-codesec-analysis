#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int maxSubListLength(struct Node* head) {
    int count = 0;
    int maxCount = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        if (count > maxCount) {
            maxCount = count;
        }
        current = current->next;
    }
    return maxCount;
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int main() {
    struct Node* head = newNode(1);
    if (head == NULL) {
        return 1;
    }
    head->next = newNode(2);
    if (head->next == NULL) {
        return 1;
    }
    head->next->next = newNode(3);
    if (head->next->next == NULL) {
        return 1;
    }
    head->next->next->next = newNode(4);
    if (head->next->next->next == NULL) {
        return 1;
    }
    head->next->next->next->next = newNode(5);
    if (head->next->next->next->next == NULL) {
        return 1;
    }

    printf("Max length of sublist is %d\n", maxSubListLength(head));

    return 0;
}