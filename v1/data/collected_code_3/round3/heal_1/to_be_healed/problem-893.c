#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

void printLast(struct Node* head) {
    if (head == NULL)
        printf("List is empty\n");

    struct Node* temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    printf("%d\n", temp->data);
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data = 1;
    head->next = second;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'second' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second->data = 2;
    second->next = third;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'third' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third->data = 3;
    third->next = NULL;

    printLast(head);

    return 0;
}