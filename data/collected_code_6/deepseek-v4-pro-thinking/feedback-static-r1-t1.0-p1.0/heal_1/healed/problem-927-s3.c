#include <stdio.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
} Node;

int height(Node *root) {
    if (root == NULL) {
        return -1;
    }
    int left_height = height(root->left);
    int right_height = height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

int main(void) {
    Node n1 = {NULL, NULL};
    Node n2 = {NULL, NULL};
    Node n3 = {NULL, NULL};
    Node n4 = {NULL, NULL};
    Node n5 = {NULL, NULL};
    Node n6 = {NULL, NULL};

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n4.left = &n6;

    printf("Height: %d\n", height(&n1));

    return 0;
}