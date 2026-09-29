#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* copyList(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* newHead = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newHead' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newHead->data = head->data;
    newHead->next = copyList(head->next);

    return newHead;
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data = 1;
    head->next = NULL;

    Node* newHead = copyList(head);

    printf("Original list: %d\n", head->data);
    printf("Copied list: %d\n", newHead->data);

    free(head);
    free(newHead);

    return 0;
}