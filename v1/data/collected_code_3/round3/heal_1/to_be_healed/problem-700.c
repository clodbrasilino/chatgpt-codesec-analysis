#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

int countRange(struct Node* head, int min, int max) {
    struct Node* current = head;
    int count = 0;
    while (current != NULL) {
        if (current->data >= min && current->data <= max)
            count++;
        current = current->next;
    }
    return count;
}

struct Node* newNode(int data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int main() {
    struct Node* head = newNode(10);
    head->next = newNode(15);
    head->next->next = newNode(20);
    head->next->next->next = newNode(25);
    head->next->next->next->next = newNode(30);

    int count = countRange(head, 15, 30);
    printf("Count of nodes in given range is %d", count);
    return 0;
}