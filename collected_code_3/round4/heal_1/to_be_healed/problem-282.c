#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

Node* subtractLists(Node* first, Node* second) {
    Node* result = NULL;
    Node *temp, *prev = NULL;
    int carry = 0, difference;

    while (first != NULL) {
        difference = carry + (first->data) - ((second != NULL) ? second->data : 0);
        carry = (difference < 0) ? 1 : 0;
        difference = difference + carry * 10;
        temp = newNode(difference);
        if (result == NULL)
            result = temp;
        else
            prev->next = temp;
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
    first->next = newNode(0);
    first->next->next = newNode(0);

    Node* second = newNode(1);
    second->next = newNode(2);

    Node* result = subtractLists(first, second);

    printList(result);

    return 0;
}