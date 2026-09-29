#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

void removeSublists(struct Node** head, int start, int end) {
    struct Node* current = *head;
    struct Node* prev = NULL;

    while (current != NULL) {
        struct Node* sublist = current;
        while (sublist != NULL && (sublist->data < start || sublist->data > end)) {
            current = sublist->next;
            sublist = current;
        }
        while (sublist != NULL && !(sublist->data < start || sublist->data > end)) {
            prev = sublist;
            sublist = sublist->next;
        }
        if (prev != NULL)
            prev->next = sublist;
        else
            *head = sublist;
    }
}

void insert(struct Node** head, int newData) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    insert(&head, 9);
    insert(&head, 8);
    insert(&head, 7);
    insert(&head, 6);
    insert(&head, 5);
    insert(&head, 4);
    insert(&head, 3);
    insert(&head, 2);
    insert(&head, 1);

    printf("Original list: ");
    printList(head);

    removeSublists(&head, 3, 8);

    printf("Updated list: ");
    printList(head);

    return 0;
}