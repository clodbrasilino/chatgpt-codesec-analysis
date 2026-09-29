#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node* addTwoLists(Node* first, Node* second) {
    Node* res = NULL;
    Node *temp, *prev = NULL;
    int carry = 0, sum;

    while (first != NULL || second != NULL) {
        sum = carry + (first? first->data: 0) + (second? second->data: 0);
        carry = (sum >= 10)? 1 : 0;
        sum = sum % 10;

        temp = newNode(sum);
        if (temp == NULL) {
            return NULL;
        }

        if(res == NULL)
            res = temp;
        else
            prev->next = temp;

        prev = temp;

        if (first) first = first->next;
        if (second) second = second->next;
    }

    if (carry > 0) {
        temp->next = newNode(carry);
        if(temp->next == NULL) {
            return NULL;
        }
    }

    return res;
}

int main() {
    Node* res = NULL;
    Node* first = newNode(2);
    if (first == NULL) {
        return -1;
    }

    Node* node = newNode(4);
    if (node == NULL) {
        free(first);
        return -1;
    }
    first->next = node;

    node = newNode(3);
    if (node == NULL) {
        free(first->next);
        free(first);
        return -1;
    }
    first->next->next = node;

    Node* second = newNode(5);
    if (second == NULL) {
        free(first->next->next);
        free(first->next);
        free(first);
        return -1;
    }

    node = newNode(6);
    if (node == NULL) {
        free(second);
        free(first->next->next);
        free(first->next);
        free(first);
        return -1;
    }
    second->next = node;

    node = newNode(4);
    if (node == NULL) {
        free(second->next);
        free(second);
        free(first->next->next);
        free(first->next);
        free(first);
        return -1;
    }
    second->next->next = node;

    res = addTwoLists(first, second);
    while(res != NULL) {
        printf("%d ", res->data);
        res = res->next;
    }

    return 0;
}