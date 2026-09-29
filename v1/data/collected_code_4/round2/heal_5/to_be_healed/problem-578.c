#include <stdlib.h>
#include <stdio.h>

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
    if(a == NULL && b == NULL) {
        return NULL;
    }
    Node* result = NULL;
    Node** tailPointer = &result;
    while(a != NULL && b != NULL) {
        Node *n = newNode(a->data);
        if(n == NULL) return NULL;
        *tailPointer = n;
        tailPointer = &(n->next);

        n = newNode(b->data);
        if(n == NULL) return NULL;
        *tailPointer = n;
        tailPointer = &(n->next);

        a = a->next;
        b = b->next;
    }
    *tailPointer = (a == NULL) ? b : a;
    return result;
/* Possible weaknesses found:
 *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

void freeList(Node *head) {
    Node* tmp;

    while (head != NULL) {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

int main() {
    Node* a = newNode(1);
    Node* a_local = a;
    if(a == NULL) return 1;
    a->next = newNode(2);
    if(a->next == NULL) return 1;
    a->next->next = newNode(3);
    if(a->next->next == NULL) return 1;

    Node* b = newNode(4);
    Node* b_local = b;
    if(b == NULL) return 1;
    b->next = newNode(5);
    if(b->next == NULL) return 1;
    b->next->next = newNode(6);
    if(b->next->next == NULL) return 1;

    Node* result = interleaveLists(a, b);
    
    Node* result_local = result;

    if(result == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    while(result != NULL) {
        printf("%d ", result->data);
        result = result->next;
    }
    printf("\n");

    freeList(a_local);
    freeList(b_local);
    freeList(result_local);

    return 0;
}