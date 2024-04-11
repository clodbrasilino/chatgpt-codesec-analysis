#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* createNode(char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
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
        printf("%f ", f);
        temp = temp->next;
    }
}

void freeList(Node *head){
    Node *tmp;
    while (head != NULL){
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

int main() {
    Node *head = createNode("10");
    if(head == NULL) {
        return -1;
    }
    head->next = createNode("20");
    if(head->next == NULL) {
        free(head);
        return -1;
    }
    head->next->next = createNode("30");
    if(head->next->next == NULL) {
        freeList(head);
        return -1;
    }
    head->next->next->next = createNode("40");
    if(head->next->next->next == NULL) {
        freeList(head);
        return -1;
    }
    convertToFloat(head);

    freeList(head);

    return 0;
}