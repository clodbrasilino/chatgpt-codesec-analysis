#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

int sumList(struct Node* node) {
    if (node == NULL)
        return 0;
    else
        return (node->data + sumList(node->next));
}

void push(struct Node** head_ref, int new_data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int main() {
    struct Node* head = NULL;
    push(&head, 7);
    push(&head, 2);
    push(&head, 1);
    push(&head, 3);
    push(&head, 8);

    printf("Sum of elements in linked list is %d\n", sumList(head));

    return 0;
}