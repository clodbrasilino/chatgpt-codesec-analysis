#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* create_node(int data);
int calculate_height(const struct TreeNode* root);
void free_tree(struct TreeNode* root);

struct TreeNode* create_node(int data) {
    struct TreeNode* new_node = malloc(sizeof(struct TreeNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

int calculate_height(const struct TreeNode* root) {
    int left_height;
    int right_height;

    if (root == NULL) {
        return -1;
    }
    
    left_height = calculate_height(root->left);
    right_height = calculate_height(root->right);
    
    if (left_height > right_height) {
        return left_height + 1;
    }
    
    return right_height + 1;
}

void free_tree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    int height;
    struct TreeNode* root = create_node(1);
    
    if (root == NULL) {
        return EXIT_FAILURE;
    }

    root->left = create_node(2);
    if (root->left == NULL) {
        free_tree(root);
        return EXIT_FAILURE;
    }

    root->right = create_node(3);
    if (root->right == NULL) {
        free_tree(root);
        return EXIT_FAILURE;
    }

    root->left->left = create_node(4);
    if (root->left->left == NULL) {
        free_tree(root);
        return EXIT_FAILURE;
    }

    root->left->right = create_node(5);
    if (root->left->right == NULL) {
        free_tree(root);
        return EXIT_FAILURE;
    }

    height = calculate_height(root);
    printf("%d\n", height);

    free_tree(root);

    return EXIT_SUCCESS;
}