#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int height(TreeNode *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    if (leftHeight == -1 || rightHeight == -1) return -1;
    if (abs(leftHeight - rightHeight) > 1) return -1;
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int isBalanced(TreeNode *root) {
    return height(root) != -1;
}

TreeNode* newNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->left->left->left = newNode(8);

    if (isBalanced(root)) {
        printf("The tree is balanced.\n");
    } else {
        printf("The tree is not balanced.\n");
    }

    return 0;
}