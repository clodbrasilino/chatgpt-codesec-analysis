#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pair {
    char *key;
    char *value;
} Pair;

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct Bucket {
    char *key;
    Node *head;
    struct Bucket *next;
} Bucket;

typedef struct HashMap {
    Bucket **buckets;
    size_t capacity;
    size_t size;
} HashMap;

static size_t hash_string(const char *str) {
    size_t hash = 5381;
    unsigned char c;
    while ((c = (unsigned char)*str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static char *dup_string(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char *copy = malloc(len);
    if (copy) memcpy(copy, str, len);
    return copy;
}

static Node *node_create(const char *value) {
    Node *node = malloc(sizeof(*node));
    if (!node) return NULL;
    node->value = dup_string(value);
    if (!node->value) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

static Bucket *bucket_create(const char *key, const char *value) {
    Bucket *bucket = malloc(sizeof(*bucket));
    if (!bucket) return NULL;
    bucket->key = dup_string(key);
    if (!bucket->key) {
        free(bucket);
        return NULL;
    }
    bucket->head = node_create(value);
    if (!bucket->head) {
        free(bucket->key);
        free(bucket);
        return NULL;
    }
    bucket->next = NULL;
    return bucket;
}

static int bucket_add(Bucket *bucket, const char *value) {
    Node *node = node_create(value);
    if (!node) return -1;
    if (!bucket->head) {
        bucket->head = node;
    } else {
        Node *cur = bucket->head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    return 0;
}

HashMap *hashmap_create(size_t capacity) {
    HashMap *map = malloc(sizeof(*map));
    if (!map) return NULL;
    if (capacity == 0) capacity = 16;
    map->buckets = calloc(capacity, sizeof(Bucket *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    map->capacity = capacity;
    map->size = 0;
    return map;
}

int hashmap_insert(HashMap *map, const char *key, const char *value) {
    if (!map || !key || !value) return -1;
    size_t idx = hash_string(key) % map->capacity;
    Bucket *bucket = map->buckets[idx];
    while (bucket) {
        if (strcmp(bucket->key, key) == 0) {
            return bucket_add(bucket, value);
        }
        bucket = bucket->next;
    }
    Bucket *new_bucket = bucket_create(key, value);
    if (!new_bucket) return -1;
    new_bucket->next = map->buckets[idx];
    map->buckets[idx] = new_bucket;
    map->size++;
    return 0;
}

static void node_free(Node *node) {
    while (node) {
        Node *next = node->next;
        free(node->value);
        free(node);
        node = next;
    }
}

static void bucket_free(Bucket *bucket) {
    while (bucket) {
        Bucket *next = bucket->next;
        free(bucket->key);
        node_free(bucket->head);
        free(bucket);
        bucket = next;
    }
}

void hashmap_free(HashMap *map) {
    if (!map) return;
    for (size_t i = 0; i < map->capacity; i++) {
        bucket_free(map->buckets[i]);
    }
    free(map->buckets);
    free(map);
}

HashMap *group_pairs(Pair *pairs, size_t count) {
    if (!pairs && count > 0) return NULL;
    HashMap *map = hashmap_create(16);
    if (!map) return NULL;
    for (size_t i = 0; i < count; i++) {
        if (hashmap_insert(map, pairs[i].key, pairs[i].value) != 0) {
            hashmap_free(map);
            return NULL;
        }
    }
    return map;
}

int main(void) {
    Pair pairs[] = {
        {"a", "1"},
        {"b", "2"},
        {"a", "3"},
        {"c", "4"},
        {"b", "5"}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    HashMap *map = group_pairs(pairs, count);
    if (!map) return EXIT_FAILURE;
    for (size_t i = 0; i < map->capacity; i++) {
        Bucket *bucket = map->buckets[i];
        while (bucket) {
            printf("%s:", bucket->key);
            for (Node *node = bucket->head; node; node = node->next) {
                printf(" %s", node->value);
            }
            printf("\n");
            bucket = bucket->next;
        }
    }
    hashmap_free(map);
    return EXIT_SUCCESS;
}