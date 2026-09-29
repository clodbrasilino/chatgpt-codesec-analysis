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

    return (left_height > right_height ? left_height : right_height) + 1;
}

static int is_balanced(const struct TreeNode *root)
{
    int balanced = 1;
    (void)check_height(root, &balanced);
    return balanced;
}

static void free_tree(struct TreeNode *root)
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
    struct TreeNode *balanced_root = create_node(1);
    struct TreeNode *unbalanced_root = create_node(1);

    balanced_root->left = create_node(2);
    balanced_root->right = create_node(3);
    balanced_root->left->left = create_node(4);
    balanced_root->left->right = create_node(5);

    unbalanced_root->left = create_node(2);
    unbalanced_root->left->left = create_node(3);
    unbalanced_root->left->left->left = create_node(4);

    if (is_balanced(balanced_root)) {
        printf("Tree 1 is balanced\n");
    } else {
        printf("Tree 1 is not balanced\n");
    }

    if (is_balanced(unbalanced_root)) {
        printf("Tree 2 is balanced\n");
    } else {
        printf("Tree 2 is not balanced\n");
    }

    free_tree(balanced_root);
    free_tree(unbalanced_root);

    return EXIT_SUCCESS;
}