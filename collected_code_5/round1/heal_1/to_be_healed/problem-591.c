#include <stdio.h>

struct Node {
    int data;
    /* Possible weaknesses found:
     *  must use 'struct' tag to refer to type 'Node'
     */
    Node* next;
};

/* Possible weaknesses found:
 *  must use 'struct' tag to refer to type 'Node'
 */
void swap(Node **head_ref)
{
    if (*head_ref == NULL || (*head_ref)->next == NULL)
        return;

    /* Possible weaknesses found:
     *  must use 'struct' tag to refer to type 'Node'
     */
    Node* first = *head_ref;
    /* Possible weaknesses found:
     *  must use 'struct' tag to refer to type 'Node'
     */
    Node* last = *head_ref;
    /* Possible weaknesses found:
     *  must use 'struct' tag to refer to type 'Node'
     */
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
 *  must use 'struct' tag to refer to type 'Node'
 */
void push(Node** head_ref, int new_data)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'Node'
     *  must use 'struct' tag to refer to type 'Node'
     *  expected expression
     */
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node *node) 
{
    while (node != NULL) 
    { 
        printf(" %d ", node->data); 
        node = node->next; 
    } 
}

int main()
{
    /* Possible weaknesses found:
     *  must use 'struct' tag to refer to type 'Node'
     */
    Node* start = NULL; 

    int arr[] = {1, 2, 3, 4, 5};
    int i;
    for (i = 4; i >=0; i--) 
       push(&start, arr[i]); 

    printf("\n Linked list before swapping\n"); 
    printList(start); 

    swap(&start); 

    printf("\n Linked list after swapping\n"); 
    printList(start); 
  
    return 0; 
}