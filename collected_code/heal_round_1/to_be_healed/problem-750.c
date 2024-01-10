#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

void addTupleToList(Node **head, Tuple tuple) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    Node *newNode = (Node *)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = tuple;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

int main() {
    Node *list = NULL;

    Tuple tuple1 = {1, 2};
    Tuple tuple2 = {3, 4};
    Tuple tuple3 = {5, 6};

    addTupleToList(&list, tuple1);
    addTupleToList(&list, tuple2);
    addTupleToList(&list, tuple3);

    Node *current = list;

    while (current != NULL) {
        printf("(%d, %d)\n", current->data.first, current->data.second);
        current = current->next;
    }

    return 0;
}