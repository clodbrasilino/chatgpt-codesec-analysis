#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static bool balanced_height(const TreeNode *root, size_t *height)
{
    size_t left_height;
    size_t right_height;

    if (root == NULL) {
        *height = 0U;
        return true;
    }

    if (!balanced_height(root->left, &left_height) ||
        !balanced_height(root->right, &right_height)) {
        return false;
    }

    if ((left_height > right_height && left_height - right_height > 1U) ||
        (right_height > left_height && right_height - left_height > 1U)) {
        return false;
    }

    *height = (left_height > right_height ? left_height : right_height) + 1U;
    return true;
}

bool is_balanced(const TreeNode *root)
{
    size_t height = 0U;

    return balanced_height(root, &height);
}

int main(void)
{
    TreeNode node4 = {4, NULL, NULL};
    TreeNode node5 = {5, NULL, NULL};
    TreeNode node6 = {6, NULL, NULL};
    TreeNode node7 = {7, NULL, NULL};
    TreeNode node2 = {2, &node4, &node5};
    TreeNode node3 = {3, &node6, &node7};
    TreeNode root = {1, &node2, &node3};

    if (printf("The binary tree is %s.\n",
               is_balanced(&root) ? "balanced" : "not balanced") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}