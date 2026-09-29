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
    Node* first = NULL;
    Node* second = NULL;

    first = newNode(2);
    if (first == NULL) {
        return -1;
    }
    first->next = newNode(4);
    first->next->next = newNode(3);

    second = newNode(5);
    second->next = newNode(6);
    second->next->next = newNode(4);

    res = addTwoLists(first, second);
    while(res != NULL) {
        printf("%d ", res->data);
        res = res->next;
    }

    return 0;
}