#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* findMaxSublist(Node* head, int* maxLength) {
    if (!head || !maxLength) return NULL;

    Node* maxSublistHead = NULL;
    int maxLen = 0;

    Node* current = head;
    while (current) {
        Node* temp = current;
        int currentLen = 1;
        while (temp->next && temp->data <= temp->next->data) {
            currentLen++;
            temp = temp->next;
        }

        if (currentLen > maxLen) {
            maxLen = currentLen;
            maxSublistHead = current;
        }

        current = temp->next;
    }

    *maxLength = maxLen;
    return maxSublistHead;
}

void printSublist(Node* head, int length) {
    Node* temp = head;
    for (int i = 0; i < length && temp != NULL; i++) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;

    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 5);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 6);
    appendNode(&head, 7);
    appendNode(&head, 8);
    appendNode(&head, 2);

    int maxLength = 0;
    Node* maxSublist = findMaxSublist(head, &maxLength);

    if (maxSublist) {
        printSublist(maxSublist, maxLength);
    }

    freeList(head);
    return 0;
}