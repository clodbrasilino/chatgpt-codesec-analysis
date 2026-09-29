#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

Node *createNode(const char *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode != NULL)
    {
        newNode->data = strdup(data);
        
        if (newNode->data == NULL)
        {
            free(newNode);
            newNode = NULL;
        }
        else
        {
            newNode->next = NULL;
        }
    }

    return newNode;
}

void insertAtBeginning(Node **head, const char *data)
{
    Node *newNode = createNode(data);

    if (newNode != NULL)
    {
        newNode->next = *head;
        *head = newNode;
    }
}

void displayList(Node *head)
{
    Node *temp = head;

    while (temp != NULL)
    {
        printf("%s ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    Node *head = NULL;

    insertAtBeginning(&head, "World");
    insertAtBeginning(&head, "Hello");

    displayList(head);

    return 0;
}
