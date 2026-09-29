#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
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
    struct Node* head = NULL;
    push(&head, 1);
    push(&head, 3);
    push(&head, 1);
    push(&head, 2);
    push(&head, 1);

    printf("Count of sublists containing 1 is %d", countSublists(head, 1));
    return 0;
}