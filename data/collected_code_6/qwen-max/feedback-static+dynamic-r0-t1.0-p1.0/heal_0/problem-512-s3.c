#include <stdio.h>
#include <stdlib.h>

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
    struct node_tuple *subtuples;
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

    for (NodeTuple *cur = t->subtuples; cur != NULL; cur = cur->next) {
        count_element_frequency(cur->tuple, e, count);
    }

    return 0;
}

int main() {
    Tuple root;
    root.head = NULL;
    root.subtuples = NULL;

    Element e1 = {0, .value.i = 5};
    Element e2 = {0, .value.i = 7};
    Element e3 = {1, .value.d = 3.14};
    Element e4 = {2, .value.s = "hello"};

    add_element(&root, e1);
    add_element(&root, e2);
    add_element(&root, e3);
    add_element(&root, e4);

    Tuple sub;
    sub.head = NULL;
    sub.subtuples = NULL;
    add_element(&sub, e1);
    add_element(&sub, e3);

    add_subtuple(&root.subtuples, &sub);

    int count = 0;
    count_element_frequency(&root, e1, &count);
    printf("Element 5 count: %d\n", count);

    return 0;
}