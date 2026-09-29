#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode *create_node(int value)
{
    TreeNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static bool insert_node(TreeNode **root, int value)
{
    TreeNode **current;
    TreeNode *node;

    if (root == NULL) {
        return false;
    }

    current = root;

    while (*current != NULL) {
        if (value < (*current)->value) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }

    node = create_node(value);
    if (node == NULL) {
        return false;
    }

    *current = node;
    return true;
}

static size_t tree_height(const TreeNode *root)
{
    size_t left_height;
    size_t right_height;

    if (root == NULL) {
        return 0U;
    }

    left_height = tree_height(root->left);
    right_height = tree_height(root->right);

    return 1U + (left_height > right_height ? left_height : right_height);
}

static void free_tree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void)
{
    const int values[] = {10, 5, 15, 3, 7, 12, 18, 1};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    TreeNode *root = NULL;
    size_t i;
    size_t height;

    for (i = 0U; i < value_count; ++i) {
        if (!insert_node(&root, values[i])) {
            free_tree(root);
            return EXIT_FAILURE;
        }
    }

    height = tree_height(root);

    if (printf("%zu\n", height) < 0) {
        free_tree(root);
        return EXIT_FAILURE;
    }

    free_tree(root);
    return EXIT_SUCCESS;
}