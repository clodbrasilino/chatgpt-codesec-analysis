#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int key;
    size_t value;
    int occupied;
} HashEntry;

static size_t hash_int(int key, size_t capacity) {
    return (size_t)key % capacity;
}

HashEntry* create_table(size_t capacity) {
    HashEntry* table = (HashEntry*)calloc(capacity, sizeof(HashEntry));
    return table;
}

int insert(HashEntry* table, size_t capacity, int key, size_t value) {
    size_t idx = hash_int(key, capacity);
    size_t start = idx;
    while (table[idx].occupied) {
        if (table[idx].key == key) {
            table[idx].value = value;
            return 0;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) return -1;
    }
    table[idx].key = key;
    table[idx].value = value;
    table[idx].occupied = 1;
    return 0;
}

int lookup(HashEntry* table, size_t capacity, int key, size_t* value) {
    size_t idx = hash_int(key, capacity);
    size_t start = idx;
    while (table[idx].occupied) {
        if (table[idx].key == key) {
            *value = table[idx].value;
            return 0;
        }
        idx = (idx + 1) % capacity;
        if (idx == start) break;
    }
    return -1;
}

void free_table(HashEntry* table) {
    free(table);
}

int main() {
    size_t capacity = 10;
    HashEntry* table = create_table(capacity);
    if (!table) return 1;

    insert(table, capacity, 42, 100);
    insert(table, capacity, 7, 200);

    size_t val;
    if (lookup(table, capacity, 42, &val) == 0) {
        printf("Key 42: %zu\n", val);
    } else {
        printf("Key 42 not found\n");
    }

    if (lookup(table, capacity, 999, &val) == 0) {
        printf("Key 999: %zu\n", val);
    } else {
        printf("Key 999 not found\n");
    }

    free_table(table);
    return 0;
}