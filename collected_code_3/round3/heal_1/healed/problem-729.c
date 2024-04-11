#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* addTwoLists(Node* first, Node* second) {
    if (!first || !second) {
        return NULL;
    }
    Node* res = NULL;
    Node *temp, *prev = NULL;
    int carry = 0, sum;

    while (first != NULL || second != NULL) {
        sum = carry + (first ? first->data : 0) + (second ? second->data : 0);
        carry = (sum >= 10) ? 1 : 0;
        sum = sum % 10;
        temp = newNode(sum);

        if (!temp) {
            return NULL;
        }

        if (res == NULL) {
            res = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;

        if (first) {
            first = first->next;
        }
        if (second) {
            second = second->next;
        }
    }

    if (carry > 0) {
        temp = newNode(carry);
        if (!temp) {
            return NULL;
        }
        prev->next = temp;
    }
    return res;
}

int main() {
    Node *res = NULL, *first = NULL, *second = NULL;

    first = newNode(2);
    if(!first){
        return 1;
    }
    first->next = newNode(4);
    if(!first->next){
        return 1;
    }
    first->next->next = newNode(3);
    if(!first->next->next){
        return 1;
    }

    second = newNode(5);
    if(!second){
        return 1;
    }
    second->next = newNode(6);
    if(!second->next){
        return 1;
    }
    second->next->next = newNode(4);
    if(!second->next->next){
        return 1;
    }

    res = addTwoLists(first, second);
    if(!res){
        return 1;
    }
    while (res) {
        printf("%d ", res->data);
        res = res->next;
    }
    return 0;
}