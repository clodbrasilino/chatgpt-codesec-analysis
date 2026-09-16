#include <stdio.h>

struct Node {
    struct Node *left;
    struct Node *right;
};

int height(struct Node *root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}

int main(void) {
    struct Node n1 = {NULL, NULL};
    struct Node n2 = {NULL, NULL};
    struct Node n3 = {NULL, NULL};
    struct Node n4 = {NULL, NULL};
    struct Node n5 = {NULL, NULL};

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    printf("Height: %d\n", height(&n1));

    return 0;
}