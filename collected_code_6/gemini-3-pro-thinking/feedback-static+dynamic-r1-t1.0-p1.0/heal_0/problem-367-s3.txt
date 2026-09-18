#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* create_node(int val) {
    struct TreeNode* new_node = malloc(sizeof(struct TreeNode));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void free_tree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int check_height(const struct TreeNode* root) {
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
    if (diff < -1 || diff > 1) {
        return -1;
    }

    return (left_height > right_height ? left_height : right_height) + 1;
}

bool is_balanced(const struct TreeNode* root) {
    return check_height(root) != -1;
}

int main(void) {
    struct TreeNode* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);

    if (is_balanced(root)) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    free_tree(root);

    return EXIT_SUCCESS;
}