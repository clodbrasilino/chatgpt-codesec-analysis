#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    struct Node *left;
    struct Node *right;
} Node;

static int checkHeight(const Node *node) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = checkHeight(node->left);
    if (leftHeight == -1) {
        return -1;
    }

    int rightHeight = checkHeight(node->right);
    if (rightHeight == -1) {
        return -1;
    }

    int diff = leftHeight - rightHeight;
    if (diff < -1 || diff > 1) {
        return -1;
    }

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

bool isBalanced(const Node *root) {
    return checkHeight(root) != -1;
}

int main(void) {
    Node n1 = {1, NULL, NULL};
    Node n2 = {2, NULL, NULL};
    Node n3 = {3, NULL, NULL};
    Node n4 = {4, NULL, NULL};
    Node n5 = {5, NULL, NULL};

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;

    printf("%s\n", isBalanced(&n1) ? "balanced" : "not balanced");

    Node m1 = {1, NULL, NULL};
    Node m2 = {2, NULL, NULL};
    Node m3 = {3, NULL, NULL};
    Node m4 = {4, NULL, NULL};
    Node m5 = {5, NULL, NULL};

    m1.left = &m2;
    m1.right = &m3;
    m2.left = &m4;
    m4.left = &m5;

    printf("%s\n", isBalanced(&m1) ? "balanced" : "not balanced");

    return 0;
}