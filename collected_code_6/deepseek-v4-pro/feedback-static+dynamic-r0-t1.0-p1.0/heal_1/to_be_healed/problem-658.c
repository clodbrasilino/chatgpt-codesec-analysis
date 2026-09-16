#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1024

typedef struct Node {
    void *key;
    int count;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[TABLE_SIZE];
    size_t key_size;
    unsigned long (*hash)(const void *key, size_t size);
    int (*compare)(const void *a, const void *b, size_t size);
} HashTable;

static unsigned long default_hash(const void *key, size_t size) {
    const unsigned char *bytes = (const unsigned char *)key;
    unsigned long hash = 5381;
    size_t i;
    for (i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + bytes[i];
    }
    return hash;
}

static int default_compare(const void *a, const void *b, size_t size) {
    return memcmp(a, b, size) == 0;
}

static HashTable *create_table(size_t key_size, unsigned long (*hash_fn)(const void *, size_t), int (*compare_fn)(const void *, const void *, size_t)) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL) {
        return NULL;
    }
    memset(table->buckets, 0, sizeof(table->buckets));
    table->key_size = key_size;
    table->hash = hash_fn ? hash_fn : default_hash;
    table->compare = compare_fn ? compare_fn : default_compare;
    return table;
}

static void destroy_table(HashTable *table) {
    int i;
    if (table == NULL) {
        return;
    }
    for (i = 0; i < TABLE_SIZE; i++) {
        Node *node = table->buckets[i];
        while (node != NULL) {
            Node *next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }
    free(table);
}

static int increment_count(HashTable *table, const void *key) {
    unsigned long hash_value;
    unsigned int index;
    Node *node;

    if (table == NULL || key == NULL) {
        return -1;
    }

    hash_value = table->hash(key, table->key_size);
    index = (unsigned int)(hash_value % TABLE_SIZE);

    node = table->buckets[index];
    while (node != NULL) {
        if (table->compare(node->key, key, table->key_size)) {
            node->count++;
            return node->count;
        }
        node = node->next;
    }

    node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return -1;
    }

    node->key = malloc(table->key_size);
    if (node->key == NULL) {
        free(node);
        return -1;
    }

    memcpy(node->key, key, table->key_size);
    node->count = 1;
    node->next = table->buckets[index];
    table->buckets[index] = node;
    return 1;
}

static int get_max_count(HashTable *table, void *out_key, int *out_count) {
    int i;
    int max_count = 0;
    Node *max_node = NULL;

    if (table == NULL || out_key == NULL || out_count == NULL) {
        return -1;
    }

    for (i = 0; i < TABLE_SIZE; i++) {
        Node *node = table->buckets[i];
        while (node != NULL) {
            if (node->count > max_count) {
                max_count = node->count;
                max_node = node;
            }
            node = node->next;
        }
    }

    if (max_node == NULL) {
        return -1;
    }

    memcpy(out_key, max_node->key, table->key_size);
    *out_count = max_node->count;
    return 0;
}

void *find_max_occurrence(const void *array, size_t array_length, size_t item_size, int *max_count) {
    HashTable *table;
    const unsigned char *bytes;
    size_t i;
    void *result;

    if (array == NULL || array_length == 0 || item_size == 0 || max_count == NULL) {
        return NULL;
    }

    table = create_table(item_size, NULL, NULL);
    if (table == NULL) {
        return NULL;
    }

    bytes = (const unsigned char *)array;
    for (i = 0; i < array_length; i++) {
        if (increment_count(table, bytes + i * item_size) < 0) {
            destroy_table(table);
            return NULL;
        }
    }

    result = malloc(item_size);
    if (result == NULL) {
        destroy_table(table);
        return NULL;
    }

    if (get_max_count(table, result, max_count) != 0) {
        free(result);
        destroy_table(table);
        return NULL;
    }

    destroy_table(table);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'numbers' can be declared as const array [constVariable]
     */
    int numbers[] = {1, 3, 2, 3, 4, 3, 2, 1, 3, 5};
    int max_count = 0;
    int *result = (int *)find_max_occurrence(numbers, 10, sizeof(int), &max_count);

    if (result != NULL) {
        printf("Maximum occurring item: %d (occurs %d times)\n", *result, max_count);
        free(result);
    } else {
        printf("No result found\n");
    }

    return 0;
}