#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_INT,
    NODE_LIST
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        struct Node *list;
    } data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int error;
} FlattenResult;

Node *create_int_node(int val) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->type = NODE_INT;
    n->data.value = val;
    n->next = NULL;
    return n;
}

Node *create_list_node(Node *list) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->type = NODE_LIST;
    n->data.list = list;
    n->next = NULL;
    return n;
}

void free_list(Node *head) {
    while (head) {
        Node *next = head->next;
        if (head->type == NODE_LIST) {
            free_list(head->data.list);
        }
        free(head);
        head = next;
    }
}

FlattenResult flatten(Node *head) {
    FlattenResult res = {NULL, 0};
    Node **tail = &res.head;

    while (head) {
        if (head->type == NODE_INT) {
            Node *new_node = create_int_node(head->data.value);
            if (!new_node) {
                free_list(res.head);
                res.head = NULL;
                res.error = 1;
                return res;
            }
            *tail = new_node;
            tail = &new_node->next;
        } else if (head->type == NODE_LIST) {
            FlattenResult sub = flatten(head->data.list);
            if (sub.error) {
                free_list(res.head);
                free_list(sub.head);
                res.head = NULL;
                res.error = 1;
                return res;
            }
            if (sub.head) {
                *tail = sub.head;
                while (*tail) {
                    tail = &(*tail)->next;
                }
            }
        }
        head = head->next;
    }
    return res;
}

void print_flattened(Node *head) {
    while (head) {
        printf("%d ", head->data.value);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node *i1 = create_int_node(1);
    if (!i1) return EXIT_FAILURE;

    Node *i2 = create_int_node(2);
    if (!i2) { free_list(i1); return EXIT_FAILURE; }

    Node *i3 = create_int_node(3);
    if (!i3) { free_list(i1); free_list(i2); return EXIT_FAILURE; }

    Node *i4 = create_int_node(4);
    if (!i4) { free_list(i1); free_list(i2); free_list(i3); return EXIT_FAILURE; }

    i2->next = i3;
    Node *l1 = create_list_node(i2);
    if (!l1) { free_list(i1); free_list(i2); free_list(i3); free_list(i4); return EXIT_FAILURE; }

    i1->next = l1;
    l1->next = i4;

    FlattenResult res = flatten(i1);
    if (res.error) {
        free_list(i1);
        return EXIT_FAILURE;
    }

    print_flattened(res.head);

    free_list(i1);
    free_list(res.head);

    return EXIT_SUCCESS;
}