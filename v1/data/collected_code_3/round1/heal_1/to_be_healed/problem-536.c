#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

struct Node* selectNth(struct Node* head, int n) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        if (count == n)
            return temp;
        count++;
        temp = temp->next;
    }
    return NULL;
}

int main() {
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
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

    struct Node* nthNode = selectNth(head, 2);
    if (nthNode != NULL)
        printf("The nth node is: %d\n", nthNode->data);
    else
        printf("The nth node does not exist.\n");

    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(head);
    free(second);
    free(third);

    return 0;
}