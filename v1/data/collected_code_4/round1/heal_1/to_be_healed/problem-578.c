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
    Node* temp = result;

    while (first != NULL && second != NULL) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        temp->next = first;
        first = first->next;

        temp = temp->next;
        temp->next = second;
        second = second->next;

        temp = temp->next;
    }

    /* Possible weaknesses found:
     *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return result->next;
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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

int main() {
    Node* first = newNode(1);
    first->next = newNode(2);
    first->next->next = newNode(3);
    first->next->next->next = newNode(4);

    Node* second = newNode(5);
    second->next = newNode(6);
    second->next->next = newNode(7);
    second->next->next->next = newNode(8);

    Node *result = interleaveLists(first, second);
    printList(result);

    return 0;
}