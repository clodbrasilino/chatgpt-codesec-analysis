#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *createNode(int data)
{
    struct TreeNode *node = malloc(sizeof *node);
    if (node == NULL) {
        fprintf(stderr, "Error: failed to allocate memory for tree node\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static int treeHeight(const struct TreeNode *node)
{
    int leftHeight;
    int rightHeight;

    if (node == NULL) {
        return 0;
    }

    leftHeight = treeHeight(node->left);
    if (leftHeight == -1) {
        return -1;
    }

    rightHeight = treeHeight(node->right);
    if (rightHeight == -1) {
        return -1;
    }

    if (abs(leftHeight - rightHeight) > 1) {
        return -1;
    }

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

static bool isBalanced(const struct TreeNode *root)
{
    return treeHeight(root) != -1;
}

static void destroyTree(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    free(node);
}

int main(void)
{
    struct TreeNode *balancedTree;
    struct TreeNode *unbalancedTree;

    balancedTree = createNode(1);
    balancedTree->left = createNode(2);
    balancedTree->right = createNode(3);
    balancedTree->left->left = createNode(4);
    balancedTree->left->right = createNode(5);

    printf("Balanced tree check: %s\n",
           isBalanced(balancedTree) ? "balanced" : "not balanced");
    destroyTree(balancedTree);
    balancedTree = NULL;

    unbalancedTree = createNode(1);
    unbalancedTree->left = createNode(2);
    unbalancedTree->left->left = createNode(3);
    unbalancedTree->left->left->left = createNode(4);

    printf("Unbalanced tree check: %s\n",
           isBalanced(unbalancedTree) ? "balanced" : "not balanced");
    destroyTree(unbalancedTree);
    unbalancedTree = NULL;

    return EXIT_SUCCESS;
}