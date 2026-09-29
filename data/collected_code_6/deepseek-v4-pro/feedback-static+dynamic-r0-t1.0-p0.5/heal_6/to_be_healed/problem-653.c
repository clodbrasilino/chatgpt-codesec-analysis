#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
} Map;

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Map *create_map(size_t size) {
    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;
    map->size = size;
    map->buckets = calloc(size, sizeof(Node *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    return map;
}

void map_put(Map *map, const char *key, int value) {
    if (!map || !key) return;
    unsigned long index = hash(key) % map->size;
    Node *current = map->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    if (key_len >= SIZE_MAX) {
        free(new_node);
        return;
    }
    /* Possible weaknesses found:
     *  alloc_size is assigned 'key_len+1' here.
     */
    size_t alloc_size = key_len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<key_len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<key_len' is always false
     */
    if (alloc_size < key_len) {
        free(new_node);
        return;
    }
    new_node->key = malloc(alloc_size);
    if (!new_node->key) {
        free(new_node);
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->key, key, alloc_size);
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

Node *map_get(Map *map, const char *key) {
    if (!map || !key) return NULL;
    unsigned long index = hash(key) % map->size;
    Node *current = map->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void free_map(Map *map) {
    if (!map) return;
    for (size_t i = 0; i < map->size; i++) {
        Node *current = map->buckets[i];
        while (current) {
            Node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(map->buckets);
    free(map);
}

typedef struct {
    char *key;
    int value;
} Pair;

typedef struct {
    Node **buckets;
    size_t size;
} GroupedMap;

static void cleanup_buckets(Node **buckets, size_t size) {
    if (!buckets) return;
    for (size_t j = 0; j < size; j++) {
        Node *current = buckets[j];
        while (current) {
            Node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
}

GroupedMap *group_pairs(Pair *pairs, size_t count, size_t map_size) {
    if (!pairs || count == 0 || map_size == 0) return NULL;
    GroupedMap *grouped = malloc(sizeof(GroupedMap));
    if (!grouped) return NULL;
    grouped->size = map_size;
    grouped->buckets = calloc(map_size, sizeof(Node *));
    if (!grouped->buckets) {
        free(grouped);
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        if (!pairs[i].key) {
            cleanup_buckets(grouped->buckets, map_size);
            free(grouped->buckets);
            free(grouped);
            return NULL;
        }
        unsigned long index = hash(pairs[i].key) % map_size;
        Node *new_node = malloc(sizeof(Node));
        if (!new_node) {
            cleanup_buckets(grouped->buckets, map_size);
            free(grouped->buckets);
            free(grouped);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_len = strlen(pairs[i].key);
        if (key_len >= SIZE_MAX) {
            free(new_node);
            cleanup_buckets(grouped->buckets, map_size);
            free(grouped->buckets);
            free(grouped);
            return NULL;
        }
        /* Possible weaknesses found:
         *  alloc_size is assigned 'key_len+1' here.
         */
        size_t alloc_size = key_len + 1;
        /* Possible weaknesses found:
         *  Condition 'alloc_size<key_len' is always false [knownConditionTrueFalse]
         *  Condition 'alloc_size<key_len' is always false
         */
        if (alloc_size < key_len) {
            free(new_node);
            cleanup_buckets(grouped->buckets, map_size);
            free(grouped->buckets);
            free(grouped);
            return NULL;
        }
        new_node->key = malloc(alloc_size);
        if (!new_node->key) {
            free(new_node);
            cleanup_buckets(grouped->buckets, map_size);
            free(grouped->buckets);
            free(grouped);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->key, pairs[i].key, alloc_size);
        new_node->value = pairs[i].value;
        new_node->next = grouped->buckets[index];
        grouped->buckets[index] = new_node;
    }
    return grouped;
}

void free_grouped_map(GroupedMap *map) {
    if (!map) return;
    cleanup_buckets(map->buckets, map->size);
    free(map->buckets);
    free(map);
}

int main(void) {
    Pair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"cherry", 4},
        {"banana", 5},
        {"date", 6}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    size_t map_size = 10;
    GroupedMap *grouped = group_pairs(pairs, count, map_size);
    if (!grouped) {
        fprintf(stderr, "Failed to group pairs\n");
        return 1;
    }
    for (size_t i = 0; i < grouped->size; i++) {
        Node *current = grouped->buckets[i];
        while (current) {
            printf("%s: %d\n", current->key, current->value);
            current = current->next;
        }
    }
    free_grouped_map(grouped);
    return 0;
}