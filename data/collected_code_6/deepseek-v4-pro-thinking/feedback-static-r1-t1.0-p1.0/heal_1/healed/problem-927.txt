#include <stdio.h>
#include <stddef.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
} Node;

int height(const Node *root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

int main(void) {
    Node n4 = {NULL, NULL};
    Node n5 = {NULL, NULL};
    Node n2 = {NULL, NULL};
    Node n3 = {&n4, &n5};
    Node n1 = {&n2, &n3};

    printf("%d\n", height(&n1));

    return 0;
}