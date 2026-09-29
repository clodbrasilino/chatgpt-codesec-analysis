#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        exit(EXIT_FAILURE); 
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

struct Node* findMinLengthSublist(struct Node* head) {
    struct Node* start = NULL;
    struct Node* end = NULL;
    struct Node* temp = head;
    int minLen = 0, len = 0;

    while (temp != NULL) {
        if (temp->data < 0) {
            if (len < minLen || minLen == 0) {
                start = temp;
                minLen = len;
            }
            len = 0;
        } else {
            len++;
        }
        temp = temp->next;
    }

    if (len < minLen && len != 0) {
        start = temp;
    }

    if (start != NULL) {
        end = start;
        while (minLen--) {
            if (end->next == NULL) {
                break;
            }
            end = end->next;
        }
    }
    
    return start;
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(-2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(-4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(-6);
    head->next->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->next->next = createNode(-8);

    struct Node* sublist = findMinLengthSublist(head);

    while (sublist != NULL) {
        printf("%d ", sublist->data);
        sublist = sublist->next;
    }

    return 0;
}