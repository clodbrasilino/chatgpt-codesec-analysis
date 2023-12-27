#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* createNode(char value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
        return NULL;
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node* stringToList(char* str)
{
    if (str == NULL)
        return NULL;

    Node* head = createNode(str[0]);
    if(head == NULL)
        return NULL;
    Node* curr = head;

    int i = 1;
    while (str[i] != '\0') {
        Node* newNode = createNode(str[i]);
        if(newNode == NULL)
            return NULL;
        curr->next = newNode;
        curr = newNode;
        i++;
    }

    return head;
}

void printList(Node* head)
{
    if (head == NULL)
        return;

    Node* curr = head;
    while (curr != NULL) {
        printf("%c ", curr->data);
        curr = curr->next;
    }
}

int main()
{
    char str[] = "Hello";
    Node* list = stringToList(str);
    if(list == NULL){
        printf("Error creting the linked list\n");
        return 1;
    }
    printList(list);
    return 0;
}