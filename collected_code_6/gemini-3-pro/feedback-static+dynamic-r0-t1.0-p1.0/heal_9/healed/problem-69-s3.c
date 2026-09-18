#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

bool isSublist(Node* list, Node* sublist) {
    if (sublist == NULL) return true;
    if (list == NULL) return false;

    Node* currentList = list;
    while (currentList != NULL) {
        Node* ptr1 = currentList;
        Node* ptr2 = sublist;
        
        while (ptr1 != NULL && ptr2 != NULL && ptr1->data == ptr2->data) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        
        if (ptr2 == NULL) return true;
        currentList = currentList->next;
    }
    
    return false;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void parseLine(Node** head) {
    Node* tail = NULL;
    int c;
    long long num = 0;
    int sign = 1;
    int has_digit = 0;
    bool line_ended = false;

    while (!line_ended && (c = getchar()) != EOF) {
        if (c == '\n') {
            line_ended = true;
        } else if (c == '-') {
            sign = -1;
        } else if (c >= '0' && c <= '9') {
            if (num < 922337203685477580LL) {
                num = num * 10 + (c - '0');
            }
            has_digit = 1;
        } else {
            if (has_digit) {
                Node* newNode = createNode((int)(num * sign));
                if (*head == NULL) {
                    *head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
                has_digit = 0;
                num = 0;
                sign = 1;
            }
        }
    }
    
    if (has_digit) {
        Node* newNode = createNode((int)(num * sign));
        if (*head == NULL) {
            *head = newNode;
        } else {
            tail->next = newNode;
        }
    }
}

int main(void) {
    Node* list = NULL;
    Node* sublist = NULL;

    parseLine(&list);
    parseLine(&sublist);

    if (isSublist(list, sublist)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    freeList(list);
    freeList(sublist);

    return 0;
}