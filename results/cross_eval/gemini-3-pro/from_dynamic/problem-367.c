#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (!newNode) {
        return NULL;
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(struct TreeNode* root) {
    if (!root) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int checkHeight(struct TreeNode* root) {
    if (!root) {
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

bool isBalanced(struct TreeNode* root) {
    if (!root) {
        return true;
    }
    return checkHeight(root) != -1;
}

int main(void) {
    struct TreeNode* root = createNode(1);
    if (!root) return 1;
    
    root->left = createNode(2);
    if (!root->left) {
        freeTree(root);
        return 1;
    }
    
    root->right = createNode(3);
    if (!root->right) {
        freeTree(root);
        return 1;
    }
    
    root->left->left = createNode(4);
    if (!root->left->left) {
        freeTree(root);
        return 1;
    }
    
    if (isBalanced(root)) {
        printf("The tree is balanced.\n");
    } else {
        printf("The tree is not balanced.\n");
    }
    
    freeTree(root);
    return 0;
}