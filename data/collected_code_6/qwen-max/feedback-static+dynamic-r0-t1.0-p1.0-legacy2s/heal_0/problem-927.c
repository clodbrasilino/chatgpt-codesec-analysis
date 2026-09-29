#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int height(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = 1;
    root->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->right = (TreeNode *)malloc(sizeof(TreeNode));
    root->left->val = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right->val = 3;
    root->right->left = (TreeNode *)malloc(sizeof(TreeNode));
    root->right->right = NULL;
    root->right->left->val = 4;
    root->right->left->left = NULL;
    root->right->left->right = NULL;

    printf("Height of the tree: %d\n", height(root));

    free(root->right->left);
    free(root->right);
    free(root->left);
    free(root);

    return 0;
}