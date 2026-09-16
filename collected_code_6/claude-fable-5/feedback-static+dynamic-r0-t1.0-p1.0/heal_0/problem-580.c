#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NODE_INT,
    NODE_TUPLE
} NodeType;

typedef struct Node {
    NodeType type;
    int value;
    struct Node **items;
    size_t count;
} Node;

static Node *create_int_node(int value)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_INT;
    node->value = value;
    node->items = NULL;
    node->count = 0;
    return node;
}

static Node *create_tuple_node(size_t capacity)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_TUPLE;
    node->value = 0;
    node->count = 0;
    if (capacity > 0) {
        node->items = calloc(capacity, sizeof(Node *));
        if (node->items == NULL) {
            free(node);
            return NULL;
        }
    } else {
        node->items = NULL;
    }
    return node;
}

static void free_node(Node *node)
{
    if (node == NULL) {
        return;
    }
    if (node->type == NODE_TUPLE && node->items != NULL) {
        for (size_t i = 0; i < node->count; i++) {
            free_node(node->items[i]);
        }
        free(node->items);
    }
    free(node);
}

static Node *extract_even(const Node *node)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->type == NODE_INT) {
        if (node->value % 2 == 0) {
            return create_int_node(node->value);
        }
        return NULL;
    }
    Node *result = create_tuple_node(node->count);
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < node->count; i++) {
        Node *child = extract_even(node->items[i]);
        if (node->items[i] != NULL && node->items[i]->type == NODE_INT) {
            if (child != NULL) {
                result->items[result->count] = child;
                result->count++;
            }
        } else {
            if (child == NULL) {
                free_node(result);
                return NULL;
            }
            result->items[result->count] = child;
            result->count++;
        }
    }
    return result;
}

static void print_node(const Node *node)
{
    if (node == NULL) {
        return;
    }
    if (node->type == NODE_INT) {
        printf("%d", node->value);
        return;
    }
    printf("(");
    for (size_t i = 0; i < node->count; i++) {
        print_node(node->items[i]);
        if (i + 1 < node->count) {
            printf(", ");
        }
    }
    printf(")");
}

static Node *build_sample(void)
{
    Node *root = create_tuple_node(4);
    if (root == NULL) {
        return NULL;
    }
    Node *a = create_int_node(4);
    Node *b = create_int_node(5);
    Node *inner = create_tuple_node(2);
    Node *d = create_int_node(10);
    if (a == NULL || b == NULL || inner == NULL || d == NULL) {
        free_node(a);
        free_node(b);
        free_node(inner);
        free_node(d);
        free_node(root);
        return NULL;
    }
    Node *c1 = create_int_node(7);
    Node *c2 = create_int_node(6);
    if (c1 == NULL || c2 == NULL) {
        free_node(c1);
        free_node(c2);
        free_node(a);
        free_node(b);
        free_node(inner);
        free_node(d);
        free_node(root);
        return NULL;
    }
    inner->items[0] = c1;
    inner->count = 1;
    inner->items[1] = c2;
    inner->count = 2;
    root->items[0] = a;
    root->count = 1;
    root->items[1] = b;
    root->count = 2;
    root->items[2] = inner;
    root->count = 3;
    root->items[3] = d;
    root->count = 4;
    return root;
}

int main(void)
{
    Node *input = build_sample();
    if (input == NULL) {
        fprintf(stderr, "Failed to build input tuple\n");
        return EXIT_FAILURE;
    }
    printf("Input:  ");
    print_node(input);
    printf("\n");
    Node *result = extract_even(input);
    if (result == NULL) {
        fprintf(stderr, "Failed to extract even elements\n");
        free_node(input);
        return EXIT_FAILURE;
    }
    printf("Output: ");
    print_node(result);
    printf("\n");
    free_node(input);
    free_node(result);
    return EXIT_SUCCESS;
}