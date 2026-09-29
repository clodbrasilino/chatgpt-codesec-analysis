#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    int* keys;
    int key_count;
    int key_capacity;
} UniqueKeysForValue;

typedef struct {
    UniqueKeysForValue* entries;
    int count;
    int capacity;
} ResultMap;

void init_result_map(ResultMap* map) {
    if (!map) return;
    map->capacity = 10;
    map->count = 0;
    map->entries = (UniqueKeysForValue*)malloc(map->capacity * sizeof(UniqueKeysForValue));
    if (!map->entries) {
        exit(EXIT_FAILURE);
    }
}

void free_result_map(ResultMap* map) {
    if (!map || !map->entries) return;
    for (int i = 0; i < map->count; ++i) {
        free(map->entries[i].keys);
    }
    free(map->entries);
    map->entries = NULL;
    map->capacity = 0;
    map->count = 0;
}

int is_key_present(const int* keys, int count, int key) {
    if (!keys) return 0;
    for (int i = 0; i < count; ++i) {
        if (keys[i] == key) return 1;
    }
    return 0;
}

void add_key_to_entry(UniqueKeysForValue* entry, int key) {
    if (!entry) return;
    if (is_key_present(entry->keys, entry->key_count, key)) return;

    if (entry->key_count == entry->key_capacity) {
        int new_capacity = entry->key_capacity == 0 ? 10 : entry->key_capacity * 2;
        int* new_keys = (int*)realloc(entry->keys, new_capacity * sizeof(int));
        if (!new_keys) {
            exit(EXIT_FAILURE);
        }
        entry->keys = new_keys;
        entry->key_capacity = new_capacity;
    }
    entry->keys[entry->key_count++] = key;
}

void add_tuple(ResultMap* map, int key, int value) {
    if (!map || !map->entries) return;

    for (int i = 0; i < map->count; ++i) {
        if (map->entries[i].value == value) {
            add_key_to_entry(&map->entries[i], key);
            return;
        }
    }

    if (map->count == map->capacity) {
        int new_capacity = map->capacity * 2;
        UniqueKeysForValue* new_entries = (UniqueKeysForValue*)realloc(map->entries, new_capacity * sizeof(UniqueKeysForValue));
        if (!new_entries) {
            exit(EXIT_FAILURE);
        }
        map->entries = new_entries;
        map->capacity = new_capacity;
    }

    UniqueKeysForValue* new_entry = &map->entries[map->count++];
    new_entry->value = value;
    new_entry->key_count = 0;
    new_entry->key_capacity = 10;
    new_entry->keys = (int*)malloc(new_entry->key_capacity * sizeof(int));
    if (!new_entry->keys) {
        exit(EXIT_FAILURE);
    }

    add_key_to_entry(new_entry, key);
}

void count_unique_keys(const Tuple* tuples, int tuple_count, ResultMap* map) {
    if (!tuples || !map) return;
    for (int i = 0; i < tuple_count; ++i) {
        add_tuple(map, tuples[i].key, tuples[i].value);
    }
}

int main(void) {
    Tuple tuples[] = {
        {1, 100},
        {2, 100},
        {1, 100},
        {3, 200},
        {4, 200},
        {4, 200},
        {5, 300}
    };
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    ResultMap map;
    init_result_map(&map);

    count_unique_keys(tuples, tuple_count, &map);

    for (int i = 0; i < map.count; ++i) {
        printf("Value: %d, Unique Keys Count: %d\n", map.entries[i].value, map.entries[i].key_count);
    }

    free_result_map(&map);

    return 0;
}