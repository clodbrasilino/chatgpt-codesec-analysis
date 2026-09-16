#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum { TYPE_INT, TYPE_LIST } NodeType;

typedef struct Node {
    NodeType type;
    int value;
    struct Node *child;
    struct Node *next;
} Node;

static Node *create_int_node(int value)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->type = TYPE_INT;
    node->value = value;
    node->child = NULL;
    node->next = NULL;
    return node;
}

static Node *create_list_node(Node *child)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->type = TYPE_LIST;
    node->value = 0;
    node->child = child;
    node->next = NULL;
    return node;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        if (head->type == TYPE_LIST) {
            free_list(head->child);
        }
        free(head);
        head = next;
    }
}

static bool append(Node **head, Node *node)
{
    if (head == NULL || node == NULL) {
        return false;
    }
    if (*head == NULL) {
        *head = node;
    } else {
        Node *cur = *head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = node;
    }
    return true;
}

static bool nodes_equal(const Node *a, const Node *b)
{
    if (a == NULL || b == NULL) {
        return a == b;
    }
    if (a->type != b->type) {
        return false;
    }
    if (a->type == TYPE_INT) {
        return a->value == b->value;
    }
    const Node *ca = a->child;
    const Node *cb = b->child;
    while (ca != NULL && cb != NULL) {
        if (!nodes_equal(ca, cb)) {
            return false;
        }
        ca = ca->next;
        cb = cb->next;
    }
    return (ca == NULL) && (cb == NULL);
}

static bool is_subset(const Node *sub, const Node *super)
{
    const Node *s;
    for (s = sub; s != NULL; s = s->next) {
        bool found = false;
        const Node *p;
        for (p = super; p != NULL; p = p->next) {
            if (nodes_equal(s, p)) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Node *super = NULL;
    Node *sub = NULL;
    Node *sub2 = NULL;
    Node *inner = NULL;
    Node *inner2 = NULL;
    bool ok = true;

    ok = ok && append(&super, create_int_node(1));
    ok = ok && append(&super, create_int_node(2));
    ok = ok && append(&inner, create_int_node(3));
    ok = ok && append(&inner, create_int_node(4));
    if (ok) {
        Node *ln = create_list_node(inner);
        if (ln == NULL) {
            ok = false;
        } else {
            inner = NULL;
            ok = append(&super, ln);
        }
    }
    ok = ok && append(&super, create_int_node(5));

    ok = ok && append(&sub, create_int_node(2));
    ok = ok && append(&inner2, create_int_node(3));
    ok = ok && append(&inner2, create_int_node(4));
    if (ok) {
        Node *ln = create_list_node(inner2);
        if (ln == NULL) {
            ok = false;
        } else {
            inner2 = NULL;
            ok = append(&sub, ln);
        }
    }

    ok = ok && append(&sub2, create_int_node(9));

    if (!ok) {
        free_list(super);
        free_list(sub);
        free_list(sub2);
        free_list(inner);
        free_list(inner2);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (is_subset(sub, super)) {
        printf("List 1 is a subset of the super list\n");
    } else {
        printf("List 1 is not a subset of the super list\n");
    }

    if (is_subset(sub2, super)) {
        printf("List 2 is a subset of the super list\n");
    } else {
        printf("List 2 is not a subset of the super list\n");
    }

    free_list(super);
    free_list(sub);
    free_list(sub2);
    return EXIT_SUCCESS;
}