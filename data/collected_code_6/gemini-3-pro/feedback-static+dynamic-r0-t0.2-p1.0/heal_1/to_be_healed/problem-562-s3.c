#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int maxSublistLength(Node* head) {
    if (head == NULL) {
        return 0;
    }

    int maxLength = 0;
    int currentLength = 1;
    Node* current = head;

    while (current->next != NULL) {
        if (current->data <= current->next->data) {
            currentLength++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 1;
        }
        current = current->next;
    }

    if (currentLength > maxLength) {
        maxLength = currentLength;
    }

    return maxLength;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(1);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(5);
    head->next->next->next->next->next->next = createNode(6);

    int max_len = maxSublistLength(head);
    printf("%d\n", max_len);

    freeList(head);

    return 0;
}