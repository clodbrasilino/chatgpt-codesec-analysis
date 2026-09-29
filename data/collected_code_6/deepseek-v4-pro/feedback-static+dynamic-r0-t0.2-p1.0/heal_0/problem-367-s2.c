#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int checkHeight(TreeNode* root) {
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

bool isBalanced(TreeNode* root) {
    return checkHeight(root) != -1;
}

void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = createNode(1);
    if (root == NULL) {
        return 1;
    }
    root->left = createNode(2);
    root->right = createNode(3);
    if (root->left == NULL || root->right == NULL) {
        freeTree(root);
        return 1;
    }
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    if (root->left->left == NULL || root->left->right == NULL) {
        freeTree(root);
        return 1;
    }
    root->right->right = createNode(6);
    if (root->right->right == NULL) {
        freeTree(root);
        return 1;
    }
    
    if (isBalanced(root)) {
        printf("Tree is balanced\n");
    } else {
        printf("Tree is not balanced\n");
    }
    
    freeTree(root);
    return 0;
}