#include <stdio.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    /* Possible weaknesses found:
     *  struct member 'Node::next' is never used. [unusedStructMember]
     */
    struct Node *next;
} Node;

typedef struct List {
    /* Possible weaknesses found:
     *  struct member 'List::head' is never used. [unusedStructMember]
     */
    Node *head;
    struct List *next;
} List;

int count_lists(const List *list) {
    int count = 0;
    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

int main(void) {
    Node n1 = {1, NULL};
    Node n2 = {2, NULL};
    Node n3 = {3, NULL};

    List l1 = {&n1, NULL};
    List l2 = {&n2, NULL};
    List l3 = {&n3, NULL};

    l1.next = &l2;
    l2.next = &l3;

    printf("%d\n", count_lists(&l1));
    return 0;
}