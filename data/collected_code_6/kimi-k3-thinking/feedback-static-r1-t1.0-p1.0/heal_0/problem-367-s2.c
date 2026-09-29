#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

static struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static int check_height(const struct Node *root, bool *balanced)
{
    int left_height;
    int right_height;

    if (root == NULL) {
        return 0;
    }

    left_height = check_height(root->left, balanced);
    right_height = check_height(root->right, balanced);

    if (abs(left_height - right_height) > 1) {
        *balanced = false;
    }

    return 1 + (left_height > right_height ? left_height : right_height);
}

static bool is_balanced(const struct Node *root)
{
    bool balanced = true;
    (void)check_height(root, &balanced);
    return balanced;
}

static void free_tree(struct Node *root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void)
{
    struct Node *root = create_node(1);
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    root->left = create_node(2);
    root->right = create_node(3);
    if (root->left == NULL || root->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tree(root);
        return EXIT_FAILURE;
    }

    root->left->left = create_node(4);
    root->left->right = create_node(5);
    if (root->left->left == NULL || root->left->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tree(root);
        return EXIT_FAILURE;
    }

    if (is_balanced(root)) {
        printf("The binary tree is balanced\n");
    } else {
        printf("The binary tree is not balanced\n");
    }

    free_tree(root);
    return EXIT_SUCCESS;
}