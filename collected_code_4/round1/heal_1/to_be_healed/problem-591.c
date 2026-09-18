#include <stdio.h>

struct Node {
    int data;
    /* Possible weaknesses found:
     *  unknown type name 'Node'
     */
    Node* next;
};

/* Possible weaknesses found:
 *  unknown type name 'Node'
 */
void swap(Node **head_ref)
{
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    Node* first = *head_ref;
    Node* last = *head_ref;
    Node* prev = NULL;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    prev->next = first;
    *head_ref = last;
    last->next = first->next;
    first->next = NULL;
}

/* Possible weaknesses found:
 *  unknown type name 'Node'
 */
void push(Node** head_ref, int new_data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

/* Possible weaknesses found:
 *  expected 'struct Node *' but argument is of type 'int *'
 */
void printList(struct Node *node) 
{
    while (node != NULL) 
    { 
        printf(" %d ", node->data); 
        /* Possible weaknesses found:
         *  assignment to 'struct Node *' from incompatible pointer type 'int *' [-Wincompatible-pointer-types]
         */
        node = node->next; 
    } 
}

int main()
{
    /* Possible weaknesses found:
     *  unknown type name 'Node'; use 'struct' keyword to refer to the type
     */
    Node* start = NULL; 

    int arr[] = {1, 2, 3, 4, 5};
    int i;
    for (i = 4; i >=0; i--) 
       /* Possible weaknesses found:
        *  implicit declaration of function 'push' [-Wimplicit-function-declaration]
        */
       push(&start, arr[i]); 

    printf("\n Linked list before swapping\n"); 
    /* Possible weaknesses found:
     *  passing argument 1 of 'printList' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    printList(start); 

    /* Possible weaknesses found:
     *  implicit declaration of function 'swap' [-Wimplicit-function-declaration]
     */
    swap(&start); 

    printf("\n Linked list after swapping\n"); 
    /* Possible weaknesses found:
     *  passing argument 1 of 'printList' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    printList(start); 
  
    return 0; 
}