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

Node* createAlternateList(Node* head) {
    if (head == NULL)
        return NULL;

    Node* alternateHead = createNode(head->data);
    Node* alternateCurrent = alternateHead;
    head = head->next;

    while (head != NULL && head->next != NULL) {
        /* Possible weaknesses found:
         *  dereference of NULL 'alternateCurrent' [CWE-476] [-Wanalyzer-null-dereference]
         */
        alternateCurrent->next = createNode(head->next->data);
        alternateCurrent = alternateCurrent->next;
        head = head->next->next;
    }

    return alternateHead;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
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

    printf("Original List: ");
    printList(head);

    Node* alternateHead = createAlternateList(head);

    printf("Alternate List: ");
    printList(alternateHead);

    return 0;
}