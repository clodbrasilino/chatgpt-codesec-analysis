#include <stdio.h>

/// Structure for linked list node
struct Node {
  int data;
  struct Node* next;
};

/// Function to insert new node at the end of the list
struct Node* newNode(int data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/// Function to print the first element of the list
void printFirstElement(struct Node* node)
{
    if (node != NULL) {
        printf("First Element: %d\n", node->data);
    }
}

int main()
{
    /// Create linked list: 10->20->30->40->50
    struct Node* head = newNode(10);
    head->next = newNode(20);
    head->next->next = newNode(30);
    head->next->next->next = newNode(40);
    head->next->next->next->next = newNode(50);

    printFirstElement(head);

    return 0;
}