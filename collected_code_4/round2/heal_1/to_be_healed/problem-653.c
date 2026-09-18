#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    char *value;
    struct node *next;
} Node;

typedef struct {
    char *key;
    Node *values;
} Pair;

typedef struct {
    Pair *pairs;
    size_t size;
    size_t capacity;
} Map;

Map *createMap() {
    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;

    map->pairs = malloc(sizeof(Pair) * 2);
    if (!map->pairs) {
        free(map);
        return NULL;
    }

    map->size = 0;
    map->capacity = 2;
    return map;
}

bool addPair(Map *map, const char *key, const char* value) {
    if (map->size == map->capacity) {
        Pair *newPairs = realloc(map->pairs, sizeof(Pair) * map->capacity * 2);
        if (!newPairs) return false;

        map->pairs = newPairs;
        map->capacity *= 2;
    }

    Pair *pair = &map->pairs[map->size++];
    pair->key = strdup(key);
    if (!pair->key) return false;

    Node *node = malloc(sizeof(Node));
    if (!node) {
        free(pair->key);
        return false;
    }
    node->value = strdup(value);
    if (!node->value) {
        free(node);
        free(pair->key);
        return false;
    }
    node->next = NULL;
    pair->values = node;

    return true;
}

void deleteMap(Map *map) {
    for (size_t i = 0; i < map->size; i++) {
        Pair *pair = &map->pairs[i];
        /* Possible weaknesses found:
         *  double-'free' of '*pair.key' [CWE-415] [-Wanalyzer-double-free]
         */
        free(pair->key);
        /* Possible weaknesses found:
         *  use of uninitialized value '*pair.values' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        Node *node = pair->values;
        while (node) {
            Node *nextNode = node->next;
            free(node->value);
            free(node);
            node = nextNode;
        }
    }
    free(map->pairs);
    free(map);
}

int main() {
    Map *map = createMap();
    if (!map) return 1;

    addPair(map, "key1", "value1");
    addPair(map, "key2", "value2");

    deleteMap(map);
    return 0;
}