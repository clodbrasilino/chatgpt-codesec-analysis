#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if(!node) {
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

int max(int a, int b) {
    return (a >= b)? a: b;
}

int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

int isBalanced(struct Node *root) {
    int lh;
    int rh;

    if(root == NULL)
        return 1;

    lh = height(root->left);
    rh = height(root->right);

    if( abs(lh-rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;

    return 0;
}

int main() {
    struct Node *root = newNode(1);
    if(root == NULL) {
        printf("Memory not allocated.\n");
        return 0;
    }
    root->left = newNode(2);
    root->right = newNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    if(isBalanced(root))
        printf("Tree is balanced\n");
    else
        printf("Tree is not balanced\n");

    return 0;
}