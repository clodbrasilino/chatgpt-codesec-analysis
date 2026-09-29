#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

int findLength(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

struct Node* createNode(int data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct Node* head1 = createNode(1);
    head1->next = createNode(2);
    head1->next->next = createNode(3);

    struct Node* head2 = createNode(1);
    head2->next = createNode(2);

    int length1 = findLength(head1);
    int length2 = findLength(head2);

    if (length1 > length2) {
        printf("List 1 is longer with length %d\n", length1);
    } else if (length2 > length1) {
        printf("List 2 is longer with length %d\n", length2);
    } else {
        printf("Both lists have the same length of %d\n", length1);
    }

    return 0;
}