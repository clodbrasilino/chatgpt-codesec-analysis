#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) return NULL;
    newNode->val = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int checkHeight(TreeNode* root, int* height) {
    if (root == NULL) {
        *height = 0;
        return 1;
    }

    int leftHeight = 0, rightHeight = 0;
    if (!checkHeight(root->left, &leftHeight)) return 0;
    if (!checkHeight(root->right, &rightHeight)) return 0;

    if (abs(leftHeight - rightHeight) > 1) return 0;

    *height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    return 1;
}

int isBalanced(TreeNode* root) {
    int height = 0;
    return checkHeight(root, &height);
}

int main() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    if (isBalanced(root)) {
        printf("The binary tree is balanced.\n");
    } else {
        printf("The binary tree is not balanced.\n");
    }

    // Free allocated memory
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}