#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

/// Structure for linked list node
struct Node {
  int data;
  struct Node* next;
};

/// Function to insert new node at the end of the list
struct Node* newNode(int data)
{
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
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