#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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

    if (abs(left_height - right_height) > 1) {
        return -1;
    }

    return 1 + (left_height > right_height ? left_height : right_height);
}

int is_balanced(TreeNode *root) {
    return check_height(root) != -1;
}

TreeNode *create_node(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
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
    TreeNode *root1 = create_node(1);
    if (root1 == NULL) { return 1; }
    root1->left = create_node(2);
    if (root1->left == NULL) { free_tree(root1); return 1; }
    root1->right = create_node(3);
    if (root1->right == NULL) { free_tree(root1); return 1; }
    root1->left->left = create_node(4);
    if (root1->left->left == NULL) { free_tree(root1); return 1; }

    printf("Tree 1 balanced: %s\n", is_balanced(root1) ? "Yes" : "No");
    free_tree(root1);

    TreeNode *root2 = create_node(1);
    if (root2 == NULL) { return 1; }
    root2->left = create_node(2);
    if (root2->left == NULL) { free_tree(root2); return 1; }
    root2->left->left = create_node(3);
    if (root2->left->left == NULL) { free_tree(root2); return 1; }

    printf("Tree 2 balanced: %s\n", is_balanced(root2) ? "Yes" : "No");
    free_tree(root2);

    return 0;
}