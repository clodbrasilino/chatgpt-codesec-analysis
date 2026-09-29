#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::key' is never used. [unusedStructMember]
     */
    char *key;
    /* Possible weaknesses found:
     *  struct member 'Node::value' is never used. [unusedStructMember]
     */
    void *value;
    struct Node *next;
} Node;

typedef struct Dictionary {
    Node **buckets;
    int size;
} Dictionary;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int dictionary_depth(Dictionary *dict) {
    if (!dict || !dict->buckets) return 0;

    int depth = 0;
    for (int i = 0; i < dict->size; ++i) {
        Node *current = dict->buckets[i];
        int current_depth = 0;
        while (current) {
            current_depth++;
            current = current->next;
        }
        depth = max(depth, current_depth);
    }
    return depth;
}

int main() {
    Dictionary dict = {NULL, 0};
    // Example usage
    printf("Depth: %d\n", dictionary_depth(&dict));
    return 0;
}