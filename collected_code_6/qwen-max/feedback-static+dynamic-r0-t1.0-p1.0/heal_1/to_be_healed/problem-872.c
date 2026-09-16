#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

int isSubset(List *a, List *b) {
    for (Node *currB = b->head; currB != NULL; currB = currB->next) {
        for (Node *currA = a->head; currA != NULL; currA = currA->next) {
            if (currA->value == currB->value) {
                break;
            }
            if (currA->next == NULL) return 0;
        }
    }
    return 1;
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current->next;
        free(current);
        current = temp;
    }
    list->head = NULL;
}

int main() {
    List a = {NULL}, b = {NULL};
    Node *n1 = malloc(sizeof(Node));
    n1->value = 1;
    n1->next = NULL;
    /* Possible weaknesses found:
     *  a.head is assigned
     */
    a.head = n1;

    Node *n2 = malloc(sizeof(Node));
    n2->value = 2;
    n2->next = n1;
    /* Possible weaknesses found:
     *  Variable 'a.head' is reassigned a value before the old one has been used. [redundantAssignment]
     *  a.head is overwritten
     */
    a.head = n2;

    Node *m1 = malloc(sizeof(Node));
    m1->value = 1;
    m1->next = NULL;
    b.head = m1;

    printf("%d\n", isSubset(&a, &b));

    freeList(&a);
    freeList(&b);
    return 0;
}