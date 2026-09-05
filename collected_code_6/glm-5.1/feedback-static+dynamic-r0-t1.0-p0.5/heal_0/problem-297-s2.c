#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int is_list;
    union {
        int value;
        struct Node *child;
    } data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} FlatList;

Node *create_value_node(int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 0;
    n->data.value = val;
    n->next = NULL;
    return n;
}

Node *create_list_node(Node *child) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) exit(EXIT_FAILURE);
    n->is_list = 1;
    n->data.child = child;
    n->next = NULL;
    return n;
}

FlatList *create_flat_list() {
    FlatList *fl = (FlatList *)malloc(sizeof(FlatList));
    if (!fl) exit(EXIT_FAILURE);
    fl->head = NULL;
    fl->tail = NULL;
    return fl;
}

void append_to_flat_list(FlatList *fl, Node *n) {
    if (!fl || !n) return;
    n->next = NULL;
    if (!fl->head) {
        fl->head = n;
        fl->tail = n;
    } else {
        fl->tail->next = n;
        fl->tail = n;
    }
}

FlatList *flatten(Node *head) {
    FlatList *fl = create_flat_list();
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        if (curr->is_list) {
            FlatList *child_fl = flatten(curr->data.child);
            if (child_fl->head) {
                if (!fl->head) {
                    fl->head = child_fl->head;
                    fl->tail = child_fl->tail;
                } else {
                    fl->tail->next = child_fl->head;
                    fl->tail = child_fl->tail;
                }
            }
            free(curr);
            free(child_fl);
        } else {
            append_to_flat_list(fl, curr);
        }
        curr = next;
    }
    return fl;
}

void free_nested(Node *head) {
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        if (curr->is_list) {
            free_nested(curr->data.child);
        }
        free(curr);
        curr = next;
    }
}

void free_flat_list_nodes(FlatList *fl) {
    if (!fl) return;
    Node *curr = fl->head;
    while (curr) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(fl);
}

void print_flat_list(FlatList *fl) {
    if (!fl) return;
    Node *curr = fl->head;
    while (curr) {
        printf("%d ", curr->data.value);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    Node *n1 = create_value_node(1);
    Node *n2 = create_value_node(2);
    Node *n3 = create_value_node(3);
    Node *n4 = create_value_node(4);
    Node *n5 = create_value_node(5);
    Node *n6 = create_value_node(6);

    Node *inner_list = n3;
    Node *middle_list = create_list_node(inner_list);
    middle_list->next = n4;

    Node *outer_list = n1;
    outer_list->next = n2;
    outer_list->next->next = middle_list;
    outer_list->next->next->next = n5;
    outer_list->next->next->next->next = n6;

    FlatList *fl = flatten(outer_list);
    print_flat_list(fl);

    free_flat_list_nodes(fl);

    return 0;
}