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
        } else {
            break;
        }
    }
    return maxDepth + 1;
}

void initNode(Node* node, const char* key, int childrenSize) {
    assert(key != NULL);
    strncpy(node->key, key, MAX_KEY_LENGTH - 1);
    node->key[MAX_KEY_LENGTH - 1] = '\0';

    for(int i = 0; i < MAX_CHILDREN; i++){
        node->children[i] = NULL;
    }
}

int main() {
    Node* dictionary = (Node*)malloc(sizeof(Node));
    initNode(dictionary, "root", MAX_CHILDREN);

    Node* child1 = (Node*)malloc(sizeof(Node));
    initNode(child1, "child1", 1);

    Node* child2 = (Node*)malloc(sizeof(Node));
    initNode(child2, "child2", 1);

    dictionary->children[0] = child1;
    dictionary->children[1] = child2;

    int depth = findDictionaryDepth(dictionary);
    printf("Depth of the dictionary: %d\n", depth);

    // At this stage as a best practice, don't forget to free memory
    free(child2);
    free(child1);
    free(dictionary);

    return 0;
}