#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *createNode(int value)
{
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void freeTree(struct TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

static int checkHeight(const struct TreeNode *node)
{
    if (node == NULL) {
        return 0;
    }

    int leftHeight = checkHeight(node->left);
    if (leftHeight == -1) {
        return -1;
    }

    int rightHeight = checkHeight(node->right);
    if (rightHeight == -1) {
        return -1;
    }

    int diff = leftHeight - rightHeight;
    if (diff < -1 || diff > 1) {
        return -1;
    }

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static bool isBalanced(const struct TreeNode *root)
{
    return checkHeight(root) != -1;
}

int main(void)
{
    struct TreeNode *root = createNode(1);
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    root->left = createNode(2);
    if (root->left == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    root->right = createNode(3);
    if (root->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    root->left->left = createNode(4);
    if (root->left->left == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    if (isBalanced(root)) {
        printf("The tree is balanced\n");
    } else {
        printf("The tree is not balanced\n");
    }

    root->left->left->left = createNode(5);
    if (root->left->left->left == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    if (isBalanced(root)) {
        printf("The tree is balanced\n");
    } else {
        printf("The tree is not balanced\n");
    }

    freeTree(root);
    return EXIT_SUCCESS;
}