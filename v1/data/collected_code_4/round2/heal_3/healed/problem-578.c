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
    *tailPointer = a ? a : b;
    return result;
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
    if(a == NULL) return 1;
    a->next = newNode(2);
    if(a->next == NULL) return 1;
    a->next->next = newNode(3);
    if(a->next->next == NULL) return 1;

    Node* b = newNode(4);
    if(b == NULL) return 1;
    b->next = newNode(5);
    if(b->next == NULL) return 1;
    b->next->next = newNode(6);
    if(b->next->next == NULL) return 1;

    Node* result = interleaveLists(a, b);
    if(result == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    while(result != NULL) {
        printf("%d ", result->data);
        result = result->next;
    }
    printf("\n");

    freeList(a);
    freeList(b);
    freeList(result);

    return 0;
}