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
    (*head_ref) = new_node;
}

struct Node* getDifference(struct Node* head1, struct Node* head2) {
    struct Node* result = NULL;
    struct Node* t1 = head1;
    struct Node* t2 = head2;

    while(t1 != NULL) {
        while(t2 != NULL) {
            if(t1->data == t2->data)
                break;
            t2 = t2->next;
        }
        if(t2 == NULL)
            push(&result, t1->data);
        t2 = head2;
        t1 = t1->next;
    }
    return result;
}

void printList(struct Node *node) {
    while(node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    struct Node* diff = NULL;

    push(&head1, 1);
    push(&head1, 2);
    push(&head1, 3);
    push(&head1, 4);
    push(&head1, 5);

    push(&head2, 2);
    push(&head2, 3);
    push(&head2, 7);
    push(&head2, 8);

    diff = getDifference(head1, head2);

    printList(diff);

    return 0;
}