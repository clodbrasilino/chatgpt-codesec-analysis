#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static int checkHeight(struct TreeNode* root) {
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

    return max(leftHeight, rightHeight) + 1;
}

bool isBalanced(struct TreeNode* root) {
    return checkHeight(root) != -1;
}

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->left->left->left = createNode(6);

    if (isBalanced(root)) {
        printf("The binary tree is balanced.\n");
    } else {
        printf("The binary tree is not balanced.\n");
    }

    freeTree(root);
    root = NULL;

    return 0;
}