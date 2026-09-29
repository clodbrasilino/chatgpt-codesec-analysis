#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int check_height(struct TreeNode *root) {
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
    
    return (left_height > right_height ? left_height : right_height) + 1;
}

bool is_balanced(struct TreeNode *root) {
    return check_height(root) != -1;
}

struct TreeNode *create_node(int val) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(struct TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    struct TreeNode *root1 = create_node(1);
    if (root1 != NULL) {
        root1->left = create_node(2);
        root1->right = create_node(3);
        if (root1->left != NULL) {
            root1->left->left = create_node(4);
            root1->left->right = create_node(5);
        }
    }

    struct TreeNode *root2 = create_node(1);
    if (root2 != NULL) {
        root2->left = create_node(2);
        if (root2->left != NULL) {
            root2->left->left = create_node(3);
            if (root2->left->left != NULL) {
                root2->left->left->left = create_node(4);
            }
        }
    }

    printf("Tree 1 balanced: %s\n", is_balanced(root1) ? "true" : "false");
    printf("Tree 2 balanced: %s\n", is_balanced(root2) ? "true" : "false");

    free_tree(root1);
    free_tree(root2);

    return 0;
}