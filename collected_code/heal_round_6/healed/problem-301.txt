#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_KEY_LENGTH 101
#define MAX_CHILDREN 100

typedef struct Node {
    char key[MAX_KEY_LENGTH];
    struct Node* children[MAX_CHILDREN];
} Node;

int findDictionaryDepth(Node* dictionary) {
    if (dictionary == NULL) {
        return 0;
    }
    int maxDepth = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (dictionary->children[i] != NULL){
            int depth = findDictionaryDepth(dictionary->children[i]);
            if (depth > maxDepth) {
                maxDepth = depth;
            }
        }
    }
    return maxDepth + 1;
}

void initNode(Node* node, const char* key) {
    assert(key != NULL);
    size_t len = strnlen(key, MAX_KEY_LENGTH - 1);
    strncpy(node->key, key, len);
    node->key[len] = '\0';

    for(int i = 0; i < MAX_CHILDREN; i++){
        node->children[i] = NULL;
    }
}

int main() {
    Node* dictionary = (Node*)malloc(sizeof(Node));
    assert(dictionary != NULL);
    initNode(dictionary, "root");

    Node* child1 = (Node*)malloc(sizeof(Node));
    assert(child1 != NULL);
    initNode(child1, "child1");

    Node* child2 = (Node*)malloc(sizeof(Node));
    assert(child2 != NULL);
    initNode(child2, "child2");

    dictionary->children[0] = child1;
    dictionary->children[1] = child2;

    int depth = findDictionaryDepth(dictionary);
    printf("Depth of the dictionary: %d\n", depth);

    free(child2);
    free(child1);
    free(dictionary);

    return 0;
}