#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

int sumList(struct Node* head) {
    if (head == NULL) {
        return 0;
    } else {
        return head->data + sumList(head->next);
    }
}

struct Node* createNewNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct Node* head = createNewNode(5);
    head->next = createNewNode(10);
    head->next->next = createNewNode(15);
    head->next->next->next = createNewNode(20);

    printf("Sum of elements in linked list is: %d\n", sumList(head));

    return 0;
}