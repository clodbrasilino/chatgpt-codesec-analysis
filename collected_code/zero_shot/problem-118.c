#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(char value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to convert a string to a linked list
Node* stringToList(char* str)
{
    if (str == NULL)
        return NULL;

    Node* head = createNode(str[0]);
    Node* curr = head;

    int i = 1;
    while (str[i] != '\0') {
        Node* newNode = createNode(str[i]);
        curr->next = newNode;
        curr = newNode;
        i++;
    }

    return head;
}

// Function to print the linked list
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
    printList(list);
    return 0;
}
