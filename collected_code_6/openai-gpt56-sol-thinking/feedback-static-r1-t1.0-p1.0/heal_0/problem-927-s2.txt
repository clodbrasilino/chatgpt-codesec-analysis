#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    const Node *node;
    size_t depth;
} StackEntry;

static Node *create_node(int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void destroy_tree(Node *root)
{
    while (root != NULL) {
        if (root->left != NULL) {
            Node *left = root->left;
            root->left = left->right;
            left->right = root;
            root = left;
        } else {
            Node *right = root->right;
            free(root);
            root = right;
        }
    }
}

static bool push_entry(StackEntry **stack, size_t *size, size_t *capacity,
                       const Node *node, size_t depth)
{
    if (*size == *capacity) {
        size_t new_capacity;
        StackEntry *resized_stack;

        if (*capacity == 0U) {
            new_capacity = 16U;
        } else {
            if (*capacity > SIZE_MAX / 2U) {
                return false;
            }
            new_capacity = *capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(**stack)) {
            return false;
        }

        resized_stack = realloc(*stack, new_capacity * sizeof(**stack));
        if (resized_stack == NULL) {
            return false;
        }

        *stack = resized_stack;
        *capacity = new_capacity;
    }

    (*stack)[*size].node = node;
    (*stack)[*size].depth = depth;
    ++(*size);

    return true;
}

static bool calculate_tree_height(const Node *root, size_t *height)
{
    StackEntry *stack = NULL;
    size_t size = 0U;
    size_t capacity = 0U;
    size_t maximum_depth = 0U;

    if (height == NULL) {
        return false;
    }

    *height = 0U;

    if (root == NULL) {
        return true;
    }

    if (!push_entry(&stack, &size, &capacity, root, 1U)) {
        return false;
    }

    while (size > 0U) {
        StackEntry current = stack[--size];

        if (current.depth > maximum_depth) {
            maximum_depth = current.depth;
        }

        if ((current.node->left != NULL || current.node->right != NULL) &&
            current.depth == SIZE_MAX) {
            free(stack);
            return false;
        }

        if (current.node->left != NULL &&
            !push_entry(&stack, &size, &capacity, current.node->left,
                        current.depth + 1U)) {
            free(stack);
            return false;
        }

        if (current.node->right != NULL &&
            !push_entry(&stack, &size, &capacity, current.node->right,
                        current.depth + 1U)) {
            free(stack);
            return false;
        }
    }

    free(stack);
    *height = maximum_depth;

    return true;
}

int main(void)
{
    Node *root = create_node(1);
    size_t height;

    if (root == NULL) {
        return EXIT_FAILURE;
    }

    root->left = create_node(2);
    if (root->left == NULL) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    root->right = create_node(3);
    if (root->right == NULL) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    root->left->left = create_node(4);
    if (root->left->left == NULL) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    root->left->right = create_node(5);
    if (root->left->right == NULL) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    root->left->left->left = create_node(6);
    if (root->left->left->left == NULL) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    if (!calculate_tree_height(root, &height)) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", height) < 0) {
        destroy_tree(root);
        return EXIT_FAILURE;
    }

    destroy_tree(root);

    return EXIT_SUCCESS;
}