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
        if(n == NULL) return result;
        *tailPointer = n;
        tailPointer = &(n->next);

        n = newNode(b->data);
        if(n == NULL) return result;
        *tailPointer = n;
        tailPointer = &(n->next);

        a = a->next;
        b = b->next;
    }
    *tailPointer = (a == NULL) ? b : a;
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
    if(a->next == NULL) {
        free(a);
        return 1;
    }
    a->next->next = newNode(3);
    if(a->next->next == NULL) {
        free(a->next);
        free(a);
        return 1;
    }

    Node* b = newNode(4);
    if(b == NULL) {
        freeList(a);
        return 1;
    }
    b->next = newNode(5);
    if(b->next == NULL) {
        free(b);
        freeList(a);
        return 1;
    }
    b->next->next = newNode(6);
    if(b->next->next == NULL) {
        freeList(b);
        freeList(a);
        return 1;
    }

    Node* result = interleaveLists(a, b);
    if(result == NULL) {
        printf("Error allocating memory\n");
        freeList(a);
        freeList(b);
        return 1;
    }

    Node* temp = result;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    freeList(a);
    freeList(b);
    freeList(result);

    return 0;
}