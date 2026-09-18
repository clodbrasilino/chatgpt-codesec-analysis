#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node 
{
    int data;
    struct Node* next;
};

int sumList(struct Node* head) 
{
    if (head == NULL) 
    {
        return 0;
    } 
    else 
    {
        return head->data + sumList(head->next);
    }
}

void insertNode(struct Node** head_ref, int new_data)
{
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    
    if(new_node == NULL)
    {
        printf("Failed to allocate memory for new node.\n");
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'EXIT_FAILURE' undeclared (first use in this function)
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         *  'EXIT_FAILURE' is defined in header '<stdlib.h>'; did you forget to '#include <stdlib.h>'?
         */
        exit(EXIT_FAILURE);
    }
    
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int main(void) 
{
    struct Node* head = NULL;

    insertNode(&head, 3);
    insertNode(&head, 2);
    insertNode(&head, 1);
    
    printf("The sum is %d.", sumList(head));
  
    return 0;
}