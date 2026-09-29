#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int isBalancedUtil(TreeNode* node, int* height) {
    if (node == NULL) {
        *height = 0;
        return 1;
    }

    int leftHeight = 0, rightHeight = 0;
    int l = isBalancedUtil(node->left, &leftHeight);
    int r = isBalancedUtil(node->right, &rightHeight);

    *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    if (l == 0 || r == 0 || (leftHeight - rightHeight > 1) || (rightHeight - leftHeight > 1))
        return 0;

    return 1;
}

int isBalanced(TreeNode* root) {
    int height = 0;
    return isBalancedUtil(root, &height);
}

TreeNode* newNode(int value) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->val = value;
    temp->left = temp->right = NULL;
    return temp;
}

int main() {
    TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->left->left->left = newNode(8);

    if (isBalanced(root))
        printf("Tree is balanced\n");
    else
        printf("Tree is not balanced\n");

    return 0;
}