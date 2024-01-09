#include <stdio.h>

typedef struct Node {
    char key[100];
    struct Node* children[100];
} Node;

int findDictionaryDepth(Node* dictionary) {
    if (dictionary == NULL) {
        return 0;
    }

    int maxDepth = 0;
    for (int i = 0; dictionary->children[i] != NULL; i++) {
        int depth = findDictionaryDepth(dictionary->children[i]);
        if (depth > maxDepth) {
            maxDepth = depth;
        }
    }

    return maxDepth + 1;
}

int main() {
    Node* dictionary = (Node*)malloc(sizeof(Node));
    strcpy(dictionary->key, "root");

    Node* child1 = (Node*)malloc(sizeof(Node));
    strcpy(child1->key, "child1");

    Node* child2 = (Node*)malloc(sizeof(Node));
    strcpy(child2->key, "child2");

    dictionary->children[0] = child1;
    dictionary->children[1] = child2;
    dictionary->children[2] = NULL;

    child1->children[0] = NULL;
    child2->children[0] = NULL;

    int depth = findDictionaryDepth(dictionary);
    printf("Depth of the dictionary: %d\n", depth);

    return 0;
}