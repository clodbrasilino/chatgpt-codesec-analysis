#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* interleaveLists(Node* first, Node* second) {
    if (first == NULL || second == NULL) {
        return NULL;
    }

    Node* result = (Node*) malloc(sizeof(Node));
    if (!result){
        return NULL;
    }

    Node* temp = result;

    while (first != NULL && second != NULL) {
        temp->next = first;
        first = first->next;

        temp = temp->next;

        if (second != NULL) {
            temp->next = second;
            second = second->next;
            temp = temp->next;
        }
    }

    temp->next = first ? first : second;

    Node* toReturn = result->next;
    free(result);
    return toReturn;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

Node* newNode(int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));

    if (!new_node) {
        return NULL;
    }

    new_node->data = new_data;
    new_node->next = NULL;

    return new_node;
}

int main() {
    Node* first = newNode(1);
    Node* second = newNode(5);

    if (!first || !second) {
        return -1;
    }

    first->next = newNode(2);
    first->next->next = newNode(3);
    first->next->next->next = newNode(4);

    second->next = newNode(6);
    second->next->next = newNode(7);
    second->next->next->next = newNode(8);

    Node *result = interleaveLists(first, second);

    if (!result) {
        return -1;
    }

    printList(result);

    return 0;
}