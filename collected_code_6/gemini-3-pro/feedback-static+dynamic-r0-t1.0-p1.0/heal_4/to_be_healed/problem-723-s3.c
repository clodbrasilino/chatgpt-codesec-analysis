#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    size_t size;
} HashMap;

/* Possible weaknesses found:
 *  to match this '{'
 */
HashMap* create_hashmap(size_t size) {
    if (size == 0) return NULL;
    
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    
    map->size = size;
    map->buckets = (Node**)calloc(size, sizeof(Node*));
    /* Possible weaknesses found:
     *  to match this '{'
     *  Unmatched '{'. Configuration: ''. [syntaxError]
     */
    if (!map->buckets) {
        /* Possible weaknesses found:
         *  expected declaration or statement at end of input
         *  expected '}'
         */
        free(map);