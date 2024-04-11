#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  *  'assert' is defined in header '<assert.h>'; did you forget to '#include <assert.h>'?
  */

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

int GetNth(struct Node* head, int index) {
    struct Node* current = head;
    int count = 0;
    while (current != NULL) {
        if (count == index)
            return(current->data);
        count++;
        current = current->next;
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'assert' [-Wimplicit-function-declaration]
     */
    assert(0);              
}

int main() {
    struct Node* head = NULL;
    push(&head, 1);
    push(&head, 4);
    push(&head, 1);
    push(&head, 12);
    push(&head, 1); 
    printf("Element at index 3 is %d", GetNth(head, 3));  
    return 0; 
}