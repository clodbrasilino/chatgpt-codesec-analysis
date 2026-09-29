#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* interleaveLists(Node *a, Node *b) {
    if(a == NULL || b == NULL) {
        return NULL;
    }
    Node dummy;
    Node* last = &dummy;
    while(a != NULL && b != NULL) {
        Node *n = newNode(a->data);
        if(n == NULL) {
            return NULL;
        }
        last->next = n;
        last = n;
        n = newNode(b->data);
        if(n == NULL) {
            return NULL;
        }
        last->next = n;
        last = n;
        a = a->next;
        b = b->next;
    }
    last->next = NULL;  // ensure the last node doesn't have a next node
    return dummy.next;
}

int main() {
    Node* a = newNode(1);
    /* Possible weaknesses found:
     *  dereference of NULL 'a' [CWE-476] [-Wanalyzer-null-dereference]
     */
    a->next = newNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    a->next->next = newNode(3);

    Node* b = newNode(4);
    /* Possible weaknesses found:
     *  dereference of NULL 'b' [CWE-476] [-Wanalyzer-null-dereference]
     */
    b->next = newNode(5);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    b->next->next = newNode(6);

    Node* result = interleaveLists(a, b);
    if(result == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    while(result != NULL) {
        printf("%d ", result->data);
        Node* toFree = result;
        result = result->next;
        free(toFree);
    }
    printf("\n");

    return 0;
}