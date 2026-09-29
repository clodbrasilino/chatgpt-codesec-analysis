#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int height(struct Node *root)
{
    int leftHeight;
    int rightHeight;

    if (root == NULL) {
        return 0;
    }

    leftHeight = height(root->left);
    rightHeight = height(root->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

void freeTree(struct Node *root)
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
    struct Node *root = NULL;
    int treeHeight;

    root = createNode(1);
    if (root == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    root->left = createNode(2);
    if (root->left == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    root->right = createNode(3);
    if (root->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    root->left->left = createNode(4);
    if (root->left->left == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    root->left->right = createNode(5);
    if (root->left->right == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    treeHeight = height(root);
    printf("Height of the binary tree: %d\n", treeHeight);

    freeTree(root);
    root = NULL;

    return EXIT_SUCCESS;
}