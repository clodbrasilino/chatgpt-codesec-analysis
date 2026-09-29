#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *key;
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

int dictionary_depth(Dictionary *dict, int index, int current_depth) {
    if (index >= dict->size) {
        return 0;
    }
    Node *node = dict->buckets[index];
    int depth = 0;
    while (node != NULL) {
        depth = max(depth, dictionary_depth(dict, index + 1, current_depth + 1));
        node = node->next;
    }
    return max(current_depth, depth);
}

int main() {
    Dictionary dict;
    dict.size = 10;
    dict.buckets = (Node **)calloc(dict.size, sizeof(Node *));
    
    // Example: Adding some nodes to the dictionary
    Node *node1 = (Node *)malloc(sizeof(Node));
    node1->key = "key1";
    node1->value = NULL;
    node1->next = NULL;
    dict.buckets[0] = node1;

    Node *node2 = (Node *)malloc(sizeof(Node));
    node2->key = "key2";
    node2->value = NULL;
    node2->next = NULL;
    dict.buckets[1] = node2;

    Node *node3 = (Node *)malloc(sizeof(Node));
    node3->key = "key3";
    node3->value = NULL;
    node3->next = node1;
    dict.buckets[2] = node3;

    int depth = dictionary_depth(&dict, 0, 0);
    printf("Depth of the dictionary: %d\n", depth);

    // Free allocated memory
    for (int i = 0; i < dict.size; i++) {
        Node *node = dict.buckets[i];
        while (node != NULL) {
            Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(dict.buckets);

    return 0;
}