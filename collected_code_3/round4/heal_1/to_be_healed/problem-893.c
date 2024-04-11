#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
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

int getLast(struct Node* head) {
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}

int main() {
    struct Node* head = NULL;
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);
    printf("Last element is %d\n", getLast(head));
    return 0;
}