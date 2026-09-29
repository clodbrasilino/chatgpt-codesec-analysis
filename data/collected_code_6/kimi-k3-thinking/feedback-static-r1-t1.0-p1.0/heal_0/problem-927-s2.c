#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

static struct Node *createNode(int data)
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

static int treeHeight(const struct Node *root)
{
    int leftHeight;
    int rightHeight;

    if (root == NULL) {
        return 0;
    }

    leftHeight = treeHeight(root->left);
    rightHeight = treeHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static void freeTree(struct Node *root)
{
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void)
{
    struct Node *root = createNode(1);

    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    root->left = createNode(2);
    root->right = createNode(3);
    if (root->left == NULL || root->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    root->left->left = createNode(4);
    root->left->right = createNode(5);
    if (root->left->left == NULL || root->left->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    printf("Height of the binary tree: %d\n", treeHeight(root));

    freeTree(root);

    return EXIT_SUCCESS;
}