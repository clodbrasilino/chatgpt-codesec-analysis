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
        struct Node *child;
    } data;
    struct Node *next;
} Node;

static Node *create_int_node(int value)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_INT;
    node->data.value = value;
    node->next = NULL;
    return node;
}

static Node *create_list_node(Node *child)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_LIST;
    node->data.child = child;
    node->next = NULL;
    return node;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        if (head->type == NODE_LIST) {
            free_list(head->data.child);
        }
        free(head);
        head = next;
    }
}

static int flatten_helper(const Node *head, Node **tail)
{
    while (head != NULL) {
        if (head->type == NODE_INT) {
            Node *new_node = create_int_node(head->data.value);
            if (new_node == NULL) {
                return -1;
            }
            (*tail)->next = new_node;
            *tail = new_node;
        } else {
            if (flatten_helper(head->data.child, tail) != 0) {
                return -1;
            }
        }
        head = head->next;
    }
    return 0;
}

static Node *flatten(const Node *head)
{
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    if (flatten_helper(head, &tail) != 0) {
        free_list(dummy.next);
        return NULL;
    }
    return dummy.next;
}

static void print_list(const Node *head)
{
    printf("[");
    while (head != NULL) {
        if (head->type == NODE_INT) {
            printf("%d", head->data.value);
        } else {
            print_list(head->data.child);
        }
        if (head->next != NULL) {
            printf(", ");
        }
        head = head->next;
    }
    printf("]");
}

static Node *build_sample(void)
{
    Node *n1 = create_int_node(1);
    if (n1 == NULL) {
        return NULL;
    }

    Node *n3 = create_int_node(3);
    if (n3 == NULL) {
        free_list(n1);
        return NULL;
    }

    Node *n4 = create_int_node(4);
    if (n4 == NULL) {
        free_list(n1);
        free_list(n3);
        return NULL;
    }
    n3->next = n4;

    Node *inner = create_list_node(n3);
    if (inner == NULL) {
        free_list(n1);
        free_list(n3);
        return NULL;
    }

    Node *n2 = create_int_node(2);
    if (n2 == NULL) {
        free_list(n1);
        free_list(inner);
        return NULL;
    }
    n2->next = inner;

    Node *outer = create_list_node(n2);
    if (outer == NULL) {
        free_list(n1);
        free_list(n2);
        return NULL;
    }
    n1->next = outer;

    Node *n5 = create_int_node(5);
    if (n5 == NULL) {
        free_list(n1);
        return NULL;
    }
    outer->next = n5;

    return n1;
}

int main(void)
{
    Node *nested = build_sample();
    if (nested == NULL) {
        fprintf(stderr, "Failed to build nested list\n");
        return EXIT_FAILURE;
    }

    printf("Nested list: ");
    print_list(nested);
    printf("\n");

    Node *flat = flatten(nested);
    if (flat == NULL) {
        fprintf(stderr, "Failed to flatten list\n");
        free_list(nested);
        return EXIT_FAILURE;
    }

    printf("Flattened list: ");
    print_list(flat);
    printf("\n");

    free_list(nested);
    free_list(flat);
    return EXIT_SUCCESS;
}