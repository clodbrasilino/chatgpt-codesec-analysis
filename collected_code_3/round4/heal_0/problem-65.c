#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

int sumList(struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + sumList(head->next);
}

struct Node* createNewNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct Node* head = createNewNode(1);
    head->next = createNewNode(2);
    head->next->next = createNewNode(3);
    head->next->next->next = createNewNode(4);
    head->next->next->next->next = createNewNode(5);

    printf("Sum of elements in linked list is: %d\n", sumList(head));

    return 0;
}