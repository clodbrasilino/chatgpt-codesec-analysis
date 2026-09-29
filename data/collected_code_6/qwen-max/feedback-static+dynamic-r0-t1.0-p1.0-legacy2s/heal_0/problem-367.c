#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* newNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(TreeNode* node) {
    if (node == NULL) return 0;
    return 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
}

int isBalanced(TreeNode* node) {
    if (node == NULL) return 1;
    int lh = height(node->left);
    int rh = height(node->right);

    if (abs(lh - rh) <= 1 && isBalanced(node->left) && isBalanced(node->right))
        return 1;

    return 0;
}

int main() {
    TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->left->left->left = newNode(6);

    if (isBalanced(root)) {
        printf("The tree is balanced\n");
    } else {
        printf("The tree is not balanced\n");
    }

    return 0;
}