#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char key;
    struct Node* next;
    struct Node* child;
} Node;

Node* createNode(char key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
        return NULL;
        
    newNode->key = key;
    newNode->next = NULL;
    newNode->child = NULL;
    return newNode;
}

int findDepth(Node* root) {
    if (root == NULL)
        return 0;

    int maxDepth = 0;
    Node* current = root->child;
    while (current != NULL) {
        int childDepth = findDepth(current);
        if (childDepth > maxDepth)
            maxDepth = childDepth;
        current = current->next;
    }

    return maxDepth + 1;
}

int main() {
    Node* root = createNode('a');
    if(root == NULL)
        return 1;
        
    root->child = createNode('b');
    if(root->child == NULL)
        return 1;

    root->child->next = createNode('c');
    if(root->child->next == NULL)
        return 1;

    root->child->next->child = createNode('d');
    if(root->child->next->child == NULL)
        return 1;

    printf("Depth: %d\n", findDepth(root));

    return 0;
}
