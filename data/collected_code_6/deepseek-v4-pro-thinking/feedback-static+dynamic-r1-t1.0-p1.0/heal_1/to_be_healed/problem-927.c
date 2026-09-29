#include <stdio.h>
#include <stddef.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
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
    Node n4 = {4, NULL, NULL};
    Node n5 = {5, NULL, NULL};
    Node n2 = {2, NULL, NULL};
    Node n3 = {3, &n4, &n5};
    Node n1 = {1, &n2, &n3};

    printf("%d\n", height(&n1));

    return 0;
}