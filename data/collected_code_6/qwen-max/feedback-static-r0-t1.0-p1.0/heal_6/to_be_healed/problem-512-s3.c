#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int type;
    union {
        int i;
        double d;
        char *s;
    } value;
} Element;

typedef struct node {
    Element e;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    /* Possible weaknesses found:
     *  unknown type name 'NodeTuple'
     */
    NodeTuple *subtuples;
} Tuple;

typedef struct node_tuple {
    Tuple *tuple;
    struct node_tuple *next;
} NodeTuple;

void add_element(Tuple *t, Element e) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->e = e;
    new_node->next = t->head;
    t->head = new_node;
}

/* Possible weaknesses found:
 *  expected 'NodeTuple **' {aka 'struct node_tuple **'} but argument is of type 'int **'
 */
void add_subtuple(NodeTuple **nt, Tuple *t) {
    NodeTuple *new_node = (NodeTuple *)malloc(sizeof(NodeTuple));
    new_node->tuple = t;
    new_node->next = *nt;
    *nt = new_node;
}

int count_element_frequency(Tuple *t, Element e, int *count) {
    if (t == NULL)
        return 0;

    for (Node *cur = t->head; cur != NULL; cur = cur->next) {
        if (cur->e.type == e.type) {
            if (e.type == 0 && cur->e.value.i == e.value.i) (*count)++;
            if (e.type == 1 && cur->e.value.d == e.value.d) (*count)++;
            if (e.type == 2 && !strcmp(cur->e.value.s, e.value.s)) (*count)++;
        }
    }

    /* Possible weaknesses found:
     *  initialization of 'NodeTuple *' {aka 'struct node_tuple *'} from incompatible pointer type 'int *' [-Wincompatible-pointer-types]
     */
    for (NodeTuple *cur = t->subtuples; cur != NULL; cur = cur->next) {
        count_element_frequency(cur->tuple, e, count);
    }

    return 0;
}

int main() {
    Tuple root = {NULL, NULL};

    Element e1 = {0, .value.i = 5};
    Element e2 = {0, .value.i = 7};
    Element e3 = {1, .value.d = 3.14};
    Element e4 = {2, .value.s = "hello"};

    add_element(&root, e1);
    add_element(&root, e2);
    add_element(&root, e3);
    add_element(&root, e4);

    Tuple sub = {NULL, NULL};
    add_element(&sub, e1);
    add_element(&sub, e3);

    /* Possible weaknesses found:
     *  passing argument 1 of 'add_subtuple' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    add_subtuple(&(root.subtuples), &sub);

    int count = 0;
    count_element_frequency(&root, e1, &count);
    printf("Element 5 count: %d\n", count);

    return 0;
}