#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_KEY_LENGTH 101
#define MAX_CHILDREN 100

typedef struct Node {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t len = strlen(key);
    len = len < MAX_KEY_LENGTH - 1 ? len : MAX_KEY_LENGTH - 1;
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
     */
    memcpy(node->key, key, len);
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