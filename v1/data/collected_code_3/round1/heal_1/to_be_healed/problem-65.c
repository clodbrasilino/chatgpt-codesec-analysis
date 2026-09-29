#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

int sumList(struct Node* head) {
    if (head == NULL) {
        return 0;
    } else {
        return head->data + sumList(head->next);
    }
}

struct Node* createNewNode(int data) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct Node* head = createNewNode(5);
    head->next = createNewNode(10);
    head->next->next = createNewNode(15);
    head->next->next->next = createNewNode(20);

    printf("Sum of elements in linked list is: %d\n", sumList(head));

    return 0;
}