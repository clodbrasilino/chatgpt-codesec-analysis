#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static bool insert_node(TreeNode **root, int value)
{
    TreeNode *node;

    if (root == NULL) {
        return false;
    }

    if (*root == NULL) {
        node = malloc(sizeof(*node));
        if (node == NULL) {
            return false;
        }

        node->value = value;
        node->left = NULL;
        node->right = NULL;
        *root = node;
        return true;
    }

    if (value < (*root)->value) {
        return insert_node(&(*root)->left, value);
    }

    if (value > (*root)->value) {
        return insert_node(&(*root)->right, value);
    }

    return true;
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

static bool get_balanced_height(const TreeNode *root, size_t *height)
{
    size_t left_height;
    size_t right_height;

    if (height == NULL) {
        return false;
    }

    if (root == NULL) {
        *height = 0U;
        return true;
    }

    if (!get_balanced_height(root->left, &left_height) ||
        !get_balanced_height(root->right, &right_height)) {
        return false;
    }

    if (left_height > right_height) {
        if (left_height - right_height > 1U) {
            return false;
        }
        *height = left_height + 1U;
    } else {
        if (right_height - left_height > 1U) {
            return false;
        }
        *height = right_height + 1U;
    }

    return true;
}

bool is_balanced(const TreeNode *root)
{
    size_t height;

    return get_balanced_height(root, &height);
}

int main(void)
{
    const int values[] = {50, 30, 70, 20, 40, 60, 80};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    TreeNode *root = NULL;
    size_t index;
    int result;

    for (index = 0U; index < value_count; ++index) {
        if (!insert_node(&root, values[index])) {
            free_tree(root);
            return EXIT_FAILURE;
        }
    }

    result = puts(is_balanced(root)
                      ? "The binary tree is balanced."
                      : "The binary tree is not balanced.");

    free_tree(root);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}