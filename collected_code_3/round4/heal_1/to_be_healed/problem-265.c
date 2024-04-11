#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void splitList(Node* head, int n, Node** first, Node** second) {
    Node* current = head;
    int count = 0;
    while (current != NULL && count < n) {
        count++;
        if (count == n) {
            *second = current->next;
            current->next = NULL;
            *first = head;
        }
        current = current->next;
    }
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    /* Possible weaknesses found:
     *  dereference of NULL 'head' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next = createNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next = createNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next = createNode(4);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next = createNode(5);

    Node* first = NULL;
    Node* second = NULL;

    splitList(head, 3, &first, &second);

    printList(first);
    printList(second);

    return 0;
}