#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static bool balanced_height(const TreeNode *node, size_t *height)
{
    size_t left_height;
    size_t right_height;
    size_t difference;

    if (node == NULL) {
        *height = 0U;
        return true;
    }

    if (!balanced_height(node->left, &left_height) ||
        !balanced_height(node->right, &right_height)) {
        return false;
    }

    difference = left_height > right_height
                     ? left_height - right_height
                     : right_height - left_height;

    if (difference > 1U ||
        left_height == SIZE_MAX ||
        right_height == SIZE_MAX) {
        return false;
    }

    *height = (left_height > right_height ? left_height : right_height) + 1U;
    return true;
}

bool is_binary_tree_balanced(const TreeNode *root)
{
    size_t height;

    return balanced_height(root, &height);
}

int main(void)
{
    TreeNode node4 = {NULL, NULL};
    TreeNode node5 = {NULL, NULL};
    TreeNode node6 = {NULL, NULL};
    TreeNode node2 = {&node4, &node5};
    TreeNode node3 = {&node6, NULL};
    TreeNode root = {&node2, &node3};

    if (printf("%s\n",
               is_binary_tree_balanced(&root)
                   ? "The binary tree is balanced."
                   : "The binary tree is not balanced.") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}