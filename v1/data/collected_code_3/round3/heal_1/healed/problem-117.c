#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* createNode(char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void convertToFloat(Node *head) {
    Node *temp = head;
    while(temp != NULL) {
        float f = atof(temp->data);
        printf("%.2f ", f);
        temp = temp->next;
    }
}

int main() {
    Node *head = createNode("10");
    if (head == NULL) {
        return 1;
    }
    head->next = createNode("20");
    if (head->next == NULL) {
        return 1;
    }
    head->next->next = createNode("30");
    if (head->next->next == NULL) {
        return 1;
    }
    head->next->next->next = createNode("40");
    if (head->next->next->next == NULL) {
        return 1;
    }

    convertToFloat(head);

    return 0;
}