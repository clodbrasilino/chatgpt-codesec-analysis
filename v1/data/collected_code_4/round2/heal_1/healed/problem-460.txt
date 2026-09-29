#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

struct Node* newNode(int data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    if(new_node == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }


    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void printFirstElement(struct Node* node)
{
    if (node != NULL) {
        printf("First Element: %d\n", node->data);
    }
}

int main()
{
    struct Node* head = newNode(10);
    if(head == NULL)
    {
        return -1;
    }
    head->next = newNode(20);
    if(head->next == NULL)
    {
        return -1;
    }
    head->next->next = newNode(30);
    if(head->next->next == NULL)
    {
        return -1;
    }
    head->next->next->next = newNode(40);
    if(head->next->next->next == NULL)
    {
        return -1;
    }
    head->next->next->next->next = newNode(50);
    if(head->next->next->next->next == NULL)
    {
        return -1;
    }

    printFirstElement(head);

    return 0;
}