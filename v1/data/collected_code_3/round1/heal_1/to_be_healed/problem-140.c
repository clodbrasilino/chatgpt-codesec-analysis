#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

void findSingleOccurrence(struct Node* head) {
    struct Node* current = head;
    struct Node* prev = NULL;
    while (current != NULL) {
        if (current->next != NULL && current->data == current->next->data) {
            while (current->next != NULL && current->data == current->next->data) {
                /* Possible weaknesses found:
                 *  leak of 'current' [CWE-401] [-Wanalyzer-malloc-leak]
                 */
                current = current->next;
            }
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
        } else {
            prev = current;
        }
        /* Possible weaknesses found:
         *  leak of 'current' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        current = current->next;
    }
    printList(head);
/* Possible weaknesses found:
 *  leak of 'current' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

int main() {
    struct Node* head = NULL;
    push(&head, 5);
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    findSingleOccurrence(head);
    return 0;
}