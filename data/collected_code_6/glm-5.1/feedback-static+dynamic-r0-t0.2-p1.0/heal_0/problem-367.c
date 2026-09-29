#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_node(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int check_height(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = check_height(root->left);
    if (left_height == -1) {
        return -1;
    }
    int right_height = check_height(root->right);
    if (right_height == -1) {
        return -1;
    }
    int diff = left_height - right_height;
    if (diff > 1 || diff < -1) {
        return -1;
    }
    return (left_height > right_height ? left_height : right_height) + 1;
}

int is_balanced(TreeNode *root) {
    return check_height(root) != -1;
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    TreeNode *root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);

    if (is_balanced(root)) {
        printf("Tree is balanced\n");
    } else {
        printf("Tree is not balanced\n");
    }

    free_tree(root);

    root = create_node(1);
    root->left = create_node(2);
    root->left->left = create_node(3);

    if (is_balanced(root)) {
        printf("Tree is balanced\n");
    } else {
        printf("Tree is not balanced\n");
    }

    free_tree(root);

    return 0;
}