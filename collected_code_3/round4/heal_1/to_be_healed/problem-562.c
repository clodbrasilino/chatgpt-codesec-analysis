#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

int maxSubListLength(struct Node* head) {
    int maxCount = 0;
    while (head != NULL) {
        struct Node* temp = head;
        int count = 0;
        while (temp != NULL && temp->data == head->data) {
            count++;
            temp = temp->next;
        }
        if (count > maxCount) {
            maxCount = count;
        }
        head = head->next;
    }
    return maxCount;
}

struct Node* newNode(int data) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

int main() {
    struct Node* head = newNode(1);
    head->next = newNode(1);
    head->next->next = newNode(2);
    head->next->next->next = newNode(2);
    head->next->next->next->next = newNode(2);
    head->next->next->next->next->next = newNode(3);
    head->next->next->next->next->next->next = newNode(3);
    head->next->next->next->next->next->next->next = newNode(3);
    head->next->next->next->next->next->next->next->next = newNode(3);

    printf("Max length of sublist is %d\n", maxSubListLength(head));

    return 0;
}