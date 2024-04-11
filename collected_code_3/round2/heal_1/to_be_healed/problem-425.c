#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int countSublists(struct Node* start, int x) {
    struct Node* current = start;
    int count = 0;
    while (current != NULL) {
        if (current->data == x) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int main() {
    struct Node* start = newNode(1);
    start->next = newNode(2);
    start->next->next = newNode(1);
    start->next->next->next = newNode(3);
    start->next->next->next->next = newNode(1);

    printf("Count of sublists containing 1 is %d", countSublists(start, 1));

    return 0;
}