#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode {
    /* Possible weaknesses found:
     *  struct member 'BinaryTreeNode::value' is never used. [unusedStructMember]
     */
    int value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

static size_t binary_tree_height(const BinaryTreeNode *root)
{
    if (root == NULL) {
        return 0U;
    }

    const size_t left_height = binary_tree_height(root->left);
    const size_t right_height = binary_tree_height(root->right);

    return 1U + (left_height > right_height ? left_height : right_height);
}

int main(void)
{
    BinaryTreeNode node4 = {4, NULL, NULL};
    BinaryTreeNode node5 = {5, NULL, NULL};
    BinaryTreeNode node2 = {2, &node4, &node5};
    BinaryTreeNode node3 = {3, NULL, NULL};
    BinaryTreeNode root = {1, &node2, &node3};

    if (printf("%zu\n", binary_tree_height(&root)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}