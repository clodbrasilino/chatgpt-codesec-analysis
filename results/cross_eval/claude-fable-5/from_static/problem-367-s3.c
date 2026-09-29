#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

static struct TreeNode *create_node(int value)
{
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static int check_height(const struct TreeNode *node, int *balanced)
{
    int left_height;
    int right_height;
    int diff;

    if (node == NULL) {
        return 0;
    }

    left_height = check_height(node->left, balanced);
    if (*balanced == 0) {
        return 0;
    }

    right_height = check_height(node->right, balanced);
    if (*balanced == 0) {
        return 0;
    }

    diff = left_height - right_height;
    if (diff < -1 || diff > 1) {
        *balanced = 0;
        return 0;
    }

    return 1 + (left_height > right_height ? left_height : right_height);
}

static int is_balanced(const struct TreeNode *root)
{
    int balanced = 1;
    (void)check_height(root, &balanced);
    return balanced;
}

static void free_tree(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void)
{
    struct TreeNode *root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);

    if (is_balanced(root)) {
        printf("Tree is balanced\n");
    } else {
        printf("Tree is not balanced\n");
    }

    root->left->left->left = create_node(6);
    root->left->left->left->left = create_node(7);

    if (is_balanced(root)) {
        printf("Tree is balanced\n");
    } else {
        printf("Tree is not balanced\n");
    }

    free_tree(root);
    return EXIT_SUCCESS;
}