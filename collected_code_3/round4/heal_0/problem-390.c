#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* insertAtBeginning(Node* head, char* str) {
    Node* temp = head;
    while(temp != NULL) {
        char* newStr = (char*)malloc(strlen(str) + strlen(temp->data) + 1);
        strcpy(newStr, str);
        strcat(newStr, temp->data);
        free(temp->data);
        temp->data = newStr;
        temp = temp->next;
    }
    return head;
}

Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Error! memory not allocated.");
        exit(0);
    }
    newNode->data = (char*)malloc(strlen(data) + 1);
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}

Node* insertNode(Node* head, char* data) {
    if(head == NULL) {
        return createNode(data);
    }
    Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = createNode(data);
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while(temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    Node* head = NULL;
    head = insertNode(head, "Hello");
    head = insertNode(head, "World");
    printList(head);
    head = insertAtBeginning(head, "New");
    printList(head);
    return 0;
}