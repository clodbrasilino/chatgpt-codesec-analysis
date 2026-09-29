#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if(new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* subtractLists(Node* first, Node* second) {
    Node* res = NULL;
    Node* temp, *prev = NULL;
    int carry = 0, diff;

    while (first != NULL && second != NULL) {
        diff = carry + (first->data) - (second->data);
        if (diff < 0) {
            carry = -1;
            diff = diff + 10;
        }
        else
            carry = 0;

        temp = newNode(diff);
        
        if (temp == NULL)
            return NULL;

        if (res == NULL)
            res = temp;
        else
            prev->next = temp;
        
        prev = temp;

        first = first->next;
        second = second->next;
    }

    return res;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(Node* node) {
    Node* temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

int main() {
    Node* first = newNode(1);
    if(first == NULL) {
        return 1;
    }
    Node* temp = newNode(0);
    if(temp == NULL){
        free(first);
        return 1;
    }
    first->next = temp;

    temp = newNode(3);
    if(temp == NULL){
        freeList(first);
        return 1;
    }
    first->next->next = temp;

    Node* second = newNode(1);
    if(second == NULL) {
        freeList(first);
        return 1;
    }
    temp = newNode(1);
    if(temp == NULL){
        freeList(first);
        freeList(second);
        return 1;
    }
    second->next = temp;

    temp = newNode(2);
    if(temp == NULL){
        freeList(first);
        freeList(second);
        return 1;
    }
    second->next->next = temp;

    Node* res = subtractLists(first, second);
    if(res == NULL) {
        freeList(first);
        freeList(second);
        return 1;
    }

    printList(res);
    freeList(first);
    freeList(second);
    freeList(res);
    
    return 0;
}