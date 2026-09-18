#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data){
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* subtractLists(Node* first, Node* second) {
    Node* result = NULL; 
    Node *temp, *prev = NULL;
    int diff;

    while (first) {
        diff = first->data;
        if(second) {
            diff -= second->data;
            second = second->next;
        }

        temp = newNode(diff);

        if (!result) {
            result = temp;
        } else if(prev) {
            prev->next = temp;
        }

        prev = temp;
        first = first->next;
    }

    return result;
}

void printList(Node* node) {
    while(node) {
        printf("%d ", node->data); 
        node = node->next;
    } 
}

int main() {
    Node* first = newNode(1);
    if(!first)
        return 1;

    first->next = newNode(2);
    if(!first->next)
        return 1;

    first->next->next = newNode(8);
    if(!first->next->next)
        return 1;
        
    first->next->next->next = newNode(6);

    Node* second = newNode(4);
    if(!second)
        return 1;

    second->next = newNode(2);
    if(!second->next)
        return 1;

    second->next->next = newNode(5);
    if(!second->next->next)
        return 1;

    Node* res = subtractLists(first, second);
    printList(res);

    return 0;
}