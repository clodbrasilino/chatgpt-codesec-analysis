#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    bool is_list;
    union {
        int value;
        struct {
            struct Node *head;
            struct Node *tail;
        } list;
    };
} Node;

Node *create_value(int v) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) exit(EXIT_FAILURE);
    n->is_list = false;
    n->value = v;
    return n;
}

Node *create_list(Node *head, Node *tail) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) exit(EXIT_FAILURE);
    n->is_list = true;
    n->list.head = head;
    n->list.tail = tail;
    return n;
}

bool node_equal(Node *a, Node *b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;
    if (a->is_list != b->is_list) return false;
    if (!a->is_list) return a->value == b->value;
    return node_equal(a->list.head, b->list.head) && node_equal(a->list.tail, b->list.tail);
}

bool is_subset(Node *sub, Node *super) {
    if (sub == NULL) return true;
    if (super == NULL) return false;
    if (sub->is_list && super->is_list) {
        return is_subset(sub->list.head, super->list.head) && is_subset(sub->list.tail, super->list.tail);
    }
    if (!sub->is_list && !super->is_list) {
        return sub->value == super->value;
    }
    if (!sub->is_list && super->is_list) {
        return is_subset(sub, super->list.head) || is_subset(sub, super->list.tail);
    }
    return false;
}

void free_node(Node *n) {
    if (n == NULL) return;
    if (n->is_list) {
        free_node(n->list.head);
        free_node(n->list.tail);
    }
    free(n);
}

int main(void) {
    Node *v1 = create_value(1);
    Node *v2 = create_value(2);
    Node *v3 = create_value(3);

    Node *sub = create_list(v1, create_list(v2, NULL));
    Node *sup = create_list(v1, create_list(v2, create_list(v3, NULL)));

    if (is_subset(sub, sup)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    Node *v4 = create_value(4);
    Node *sub2 = create_list(v1, create_list(v4, NULL));

    if (is_subset(sub2, sup)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    free_node(v1);
    free_node(v2);
    free_node(v3);
    free_node(v4);
    free_node(sub);
    free_node(sup);
    free_node(sub2);

    return 0;
}