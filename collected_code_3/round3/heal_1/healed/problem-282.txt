#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* subtractLists(Node* first, Node* second) {
    Node* result = NULL;
    Node *temp, *prev = NULL;
    int carry = 0, diff;

    while (first != NULL) {
        diff = carry + (first->data) - (second ? second->data : 0);
        carry = (diff < 0) ? 1 : 0;
        diff = diff + carry * 10;
        temp = newNode(diff);
        if (temp == NULL) {
            return NULL;
        }
        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
        if (first) first = first->next;
        if (second) second = second->next;
    }
    return result;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* first = newNode(1);
    if (first == NULL) {
        return -1;
    }
    first->next = newNode(2);
    if (first->next == NULL) {
        return -1;
    }
    first->next->next = newNode(3);
    if (first->next->next == NULL) {
        return -1;
    }

    Node* second = newNode(1);
    if (second == NULL) {
        return -1;
    }
    second->next = newNode(1);
    if (second->next == NULL) {
        return -1;
    }

    Node* result = subtractLists(first, second);
    if (result == NULL) {
        return -1;
    }

    printList(result);

    return 0;
}