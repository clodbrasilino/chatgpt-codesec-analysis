#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100
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
    for (int i = 0; i < MAX_CHILDREN && dictionary->children[i] != NULL; i++) {
        int depth = findDictionaryDepth(dictionary->children[i]);
        if (depth > maxDepth) {
            maxDepth = depth;
        }
    }
    return maxDepth + 1;
}

int main() {
    Node* dictionary = (Node*)malloc(sizeof(Node));
    strncpy(dictionary->key, "root", MAX_KEY_LENGTH - 1);
    dictionary->key[MAX_KEY_LENGTH - 1] = '\0';

    Node* child1 = (Node*)malloc(sizeof(Node));
    strncpy(child1->key, "child1", MAX_KEY_LENGTH - 1);
    child1->key[MAX_KEY_LENGTH - 1] = '\0';

    Node* child2 = (Node*)malloc(sizeof(Node));
    strncpy(child2->key, "child2", MAX_KEY_LENGTH - 1);
    child2->key[MAX_KEY_LENGTH - 1] = '\0';

    dictionary->children[0] = child1;
    dictionary->children[1] = child2;
    for(int i = 2; i < MAX_CHILDREN; i++){
        dictionary->children[i] = NULL;
    }
    
    child1->children[0] = NULL;
    child2->children[0] = NULL;

    int depth = findDictionaryDepth(dictionary);
    printf("Depth of the dictionary: %d\n", depth);

    return 0;
}