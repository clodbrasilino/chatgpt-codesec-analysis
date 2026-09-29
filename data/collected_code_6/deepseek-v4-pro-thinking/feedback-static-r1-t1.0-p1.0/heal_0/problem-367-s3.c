#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(int data);
int isBalanced(TreeNode *root);
int checkHeight(TreeNode *root);
void freeTree(TreeNode *root);

TreeNode *createNode(int data)
{
    TreeNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int checkHeight(TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }

    int leftHeight = checkHeight(root->left);
    if (leftHeight == -1) {
        return -1;
    }

    int rightHeight = checkHeight(root->right);
    if (rightHeight == -1) {
        return -1;
    }

    if (abs(leftHeight - rightHeight) > 1) {
        return -1;
    }

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int isBalanced(TreeNode *root)
{
    return checkHeight(root) != -1;
}

void freeTree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    TreeNode *balancedRoot = createNode(1);
    balancedRoot->left = createNode(2);
    balancedRoot->right = createNode(3);
    balancedRoot->left->left = createNode(4);
    balancedRoot->left->right = createNode(5);

    TreeNode *unbalancedRoot = createNode(1);
    unbalancedRoot->left = createNode(2);
    unbalancedRoot->left->left = createNode(3);

    printf("Balanced tree is %s\n", isBalanced(balancedRoot) ? "balanced" : "not balanced");
    printf("Unbalanced tree is %s\n", isBalanced(unbalancedRoot) ? "balanced" : "not balanced");

    freeTree(balancedRoot);
    freeTree(unbalancedRoot);

    return 0;
}