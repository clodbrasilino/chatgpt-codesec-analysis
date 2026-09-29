#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
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

int find_depth(Dictionary *dict, int index) {
    if (index >= dict->size) return 0;
    Node *current = dict->buckets[index];
    int depth = 0;
    while (current != NULL) {
        depth = max(depth, 1 + find_depth(dict, (int)(intptr_t)current->value));
        current = current->next;
    }
    return depth;
}

int dictionary_depth(Dictionary *dict) {
    int max_depth = 0;
    for (int i = 0; i < dict->size; ++i) {
        max_depth = max(max_depth, find_depth(dict, i));
    }
    return max_depth;
}

int main() {
    Dictionary dict = {NULL, 0};
    // Assume the dictionary is properly initialized and populated here
    int depth = dictionary_depth(&dict);
    printf("Dictionary depth: %d\n", depth);
    return 0;
}