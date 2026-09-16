#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    int value;
    int unique_key_count;
    int *keys;
    size_t keys_capacity;
} ValueEntry;

typedef struct {
    ValueEntry *entries;
    size_t count;
    size_t capacity;
} ValueMap;

static int value_map_init(ValueMap *map)
{
    if (map == NULL) {
        return -1;
    }
    map->count = 0;
    map->capacity = 8;
    map->entries = malloc(map->capacity * sizeof(ValueEntry));
    if (map->entries == NULL) {
        map->capacity = 0;
        return -1;
    }
    return 0;
}

static void value_map_destroy(ValueMap *map)
{
    size_t i;
    if (map == NULL) {
        return;
    }
    for (i = 0; i < map->count; i++) {
        free(map->entries[i].keys);
        map->entries[i].keys = NULL;
    }
    free(map->entries);
    map->entries = NULL;
    map->count = 0;
    map->capacity = 0;
}

static ValueEntry *find_or_create_entry(ValueMap *map, int value)
{
    size_t i;
    ValueEntry *entry;

    for (i = 0; i < map->count; i++) {
        if (map->entries[i].value == value) {
            return &map->entries[i];
        }
    }

    if (map->count == map->capacity) {
        size_t new_capacity = map->capacity * 2;
        ValueEntry *tmp = realloc(map->entries, new_capacity * sizeof(ValueEntry));
        if (tmp == NULL) {
            return NULL;
        }
        map->entries = tmp;
        map->capacity = new_capacity;
    }

    entry = &map->entries[map->count];
    entry->value = value;
    entry->unique_key_count = 0;
    entry->keys_capacity = 4;
    entry->keys = malloc(entry->keys_capacity * sizeof(int));
    if (entry->keys == NULL) {
        return NULL;
    }
    map->count++;
    return entry;
}

static int entry_add_key(ValueEntry *entry, int key)
{
    int i;

    for (i = 0; i < entry->unique_key_count; i++) {
        if (entry->keys[i] == key) {
            return 0;
        }
    }

    if ((size_t)entry->unique_key_count == entry->keys_capacity) {
        size_t new_capacity = entry->keys_capacity * 2;
        int *tmp = realloc(entry->keys, new_capacity * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        entry->keys = tmp;
        entry->keys_capacity = new_capacity;
    }

    entry->keys[entry->unique_key_count] = key;
    entry->unique_key_count++;
    return 0;
}

static int count_unique_keys(const Pair *pairs, size_t n, ValueMap *map)
{
    size_t i;

    if (pairs == NULL || map == NULL) {
        return -1;
    }

    if (value_map_init(map) != 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        ValueEntry *entry = find_or_create_entry(map, pairs[i].value);
        if (entry == NULL) {
            value_map_destroy(map);
            return -1;
        }
        if (entry_add_key(entry, pairs[i].key) != 0) {
            value_map_destroy(map);
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Pair pairs[] = {
        {1, 100},
        {2, 100},
        {1, 100},
        {3, 200},
        {4, 200},
        {3, 200},
        {5, 300}
    };
    size_t n = sizeof(pairs) / sizeof(pairs[0]);
    ValueMap map;
    size_t i;

    if (count_unique_keys(pairs, n, &map) != 0) {
        fprintf(stderr, "Error: failed to count unique keys\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < map.count; i++) {
        if (printf("Value %d has %d unique key(s)\n",
                   map.entries[i].value,
                   map.entries[i].unique_key_count) < 0) {
            value_map_destroy(&map);
            return EXIT_FAILURE;
        }
    }

    value_map_destroy(&map);
    return EXIT_SUCCESS;
}