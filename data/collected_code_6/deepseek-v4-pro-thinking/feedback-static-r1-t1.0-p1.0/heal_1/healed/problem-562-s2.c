#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int key;
    size_t value;
    int occupied;
} HashEntry;

typedef struct {
    HashEntry *entries;
    size_t capacity;
    size_t size;
} HashTable;

enum {
    HASH_EMPTY = 0,
    HASH_OCCUPIED = 1,
    HASH_DELETED = 2
};

static size_t hash_int(int key, size_t capacity) {
    size_t h = (size_t)(unsigned int)key;
    h ^= h >> 16;
    return h % capacity;
}

static HashTable *hash_table_create(size_t capacity) {
    HashTable *table = malloc(sizeof(*table));
    if (!table) {
        return NULL;
    }
    if (capacity == 0) {
        capacity = 16;
    }
    table->entries = calloc(capacity, sizeof(HashEntry));
    if (!table->entries) {
        free(table);
        return NULL;
    }
    table->capacity = capacity;
    table->size = 0;
    return table;
}

static void hash_table_destroy(HashTable *table) {
    if (!table) {
        return;
    }
    free(table->entries);
    free(table);
}

static int hash_table_resize(HashTable *table, size_t new_capacity) {
    HashEntry *new_entries;
    size_t i;
    if (!table || new_capacity < table->size) {
        return -1;
    }
    new_entries = calloc(new_capacity, sizeof(HashEntry));
    if (!new_entries) {
        return -1;
    }
    for (i = 0; i < table->capacity; i++) {
        if (table->entries[i].occupied == HASH_OCCUPIED) {
            size_t index = hash_int(table->entries[i].key, new_capacity);
            size_t j = 0;
            while (j < new_capacity) {
                size_t idx = (index + j) % new_capacity;
                if (new_entries[idx].occupied == HASH_EMPTY) {
                    new_entries[idx] = table->entries[i];
                    break;
                }
                j++;
            }
            if (j == new_capacity) {
                free(new_entries);
                return -1;
            }
        }
    }
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return 0;
}

static int hash_table_insert(HashTable *table, int key, size_t value) {
    size_t index;
    size_t i;
    size_t first_deleted;
    if (!table) {
        return -1;
    }
    if (table->size >= table->capacity - table->capacity / 4) {
        size_t new_capacity;
        if (table->capacity > ((size_t)-1) / 2) {
            return -1;
        }
        new_capacity = table->capacity * 2;
        if (hash_table_resize(table, new_capacity) != 0) {
            return -1;
        }
    }
    index = hash_int(key, table->capacity);
    first_deleted = table->capacity;
    for (i = 0; i < table->capacity; i++) {
        size_t idx = (index + i) % table->capacity;
        if (table->entries[idx].occupied == HASH_OCCUPIED && table->entries[idx].key == key) {
            table->entries[idx].value = value;
            return 0;
        }
        if (table->entries[idx].occupied == HASH_DELETED && first_deleted == table->capacity) {
            first_deleted = idx;
        }
        if (table->entries[idx].occupied == HASH_EMPTY) {
            size_t target = (first_deleted != table->capacity) ? first_deleted : idx;
            table->entries[target].key = key;
            table->entries[target].value = value;
            table->entries[target].occupied = HASH_OCCUPIED;
            table->size++;
            return 0;
        }
    }
    return -1;
}

static int hash_table_lookup(HashTable *table, int key, size_t *value) {
    size_t index;
    size_t i;
    if (!table || table->capacity == 0) {
        return 0;
    }
    index = hash_int(key, table->capacity);
    for (i = 0; i < table->capacity; i++) {
        size_t idx = (index + i) % table->capacity;
        if (table->entries[idx].occupied == HASH_EMPTY) {
            return 0;
        }
        if (table->entries[idx].occupied == HASH_OCCUPIED && table->entries[idx].key == key) {
            if (value) {
                *value = table->entries[idx].value;
            }
            return 1;
        }
    }
    return 0;
}

static int hash_table_delete(HashTable *table, int key) {
    size_t index;
    size_t i;
    if (!table || table->capacity == 0) {
        return -1;
    }
    index = hash_int(key, table->capacity);
    for (i = 0; i < table->capacity; i++) {
        size_t idx = (index + i) % table->capacity;
        if (table->entries[idx].occupied == HASH_EMPTY) {
            return 0;
        }
        if (table->entries[idx].occupied == HASH_OCCUPIED && table->entries[idx].key == key) {
            table->entries[idx].occupied = HASH_DELETED;
            table->size--;
            return 1;
        }
    }
    return 0;
}

int main(void) {
    HashTable *table = hash_table_create(8);
    size_t value;
    if (!table) {
        fprintf(stderr, "Failed to create hash table\n");
        return EXIT_FAILURE;
    }
    hash_table_insert(table, 10, 100);
    hash_table_insert(table, 20, 200);
    hash_table_insert(table, 30, 300);
    hash_table_insert(table, 10, 111);
    if (hash_table_lookup(table, 10, &value)) {
        printf("10 -> %zu\n", value);
    } else {
        printf("10 not found\n");
    }
    if (hash_table_lookup(table, 20, &value)) {
        printf("20 -> %zu\n", value);
    }
    hash_table_delete(table, 20);
    if (!hash_table_lookup(table, 20, &value)) {
        printf("20 deleted\n");
    }
    hash_table_destroy(table);
    return 0;
}