#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int calculateHeight(TreeNode *node) {
    if (node == NULL) return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

TreeNode* createNode(int value) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) exit(1);
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Height of the tree: %d\n", calculateHeight(root));

    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right->left);
    free(root->right->right);
    free(root->right);
    free(root);

    return 0;
}