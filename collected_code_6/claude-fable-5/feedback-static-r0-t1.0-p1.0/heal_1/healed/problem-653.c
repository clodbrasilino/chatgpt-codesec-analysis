#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LENGTH 1024U

typedef struct Pair {
    const char *key;
    int value;
} Pair;

typedef struct Entry {
    char *key;
    int *values;
    size_t count;
    size_t capacity;
} Entry;

typedef struct Map {
    Entry *entries;
    size_t count;
    size_t capacity;
} Map;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strnlen(src, MAX_KEY_LENGTH);
    if (len == MAX_KEY_LENGTH) {
        return NULL;
    }
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static int map_init(Map *map)
{
    if (map == NULL) {
        return -1;
    }
    map->count = 0U;
    map->capacity = 4U;
    map->entries = malloc(map->capacity * sizeof(Entry));
    if (map->entries == NULL) {
        map->capacity = 0U;
        return -1;
    }
    return 0;
}

static void map_destroy(Map *map)
{
    size_t i;

    if (map == NULL) {
        return;
    }
    for (i = 0U; i < map->count; i++) {
        free(map->entries[i].key);
        free(map->entries[i].values);
    }
    free(map->entries);
    map->entries = NULL;
    map->count = 0U;
    map->capacity = 0U;
}

static Entry *map_find(Map *map, const char *key)
{
    size_t i;

    for (i = 0U; i < map->count; i++) {
        if (strncmp(map->entries[i].key, key, MAX_KEY_LENGTH) == 0) {
            return &map->entries[i];
        }
    }
    return NULL;
}

static Entry *map_add_entry(Map *map, const char *key)
{
    Entry *entry;
    char *key_copy;
    int *values;

    if (map->count == map->capacity) {
        size_t new_capacity;
        Entry *resized;

        if (map->capacity > (SIZE_MAX / sizeof(Entry)) / 2U) {
            return NULL;
        }
        new_capacity = map->capacity * 2U;
        resized = realloc(map->entries, new_capacity * sizeof(Entry));
        if (resized == NULL) {
            return NULL;
        }
        map->entries = resized;
        map->capacity = new_capacity;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return NULL;
    }

    values = malloc(4U * sizeof(int));
    if (values == NULL) {
        free(key_copy);
        return NULL;
    }

    entry = &map->entries[map->count];
    entry->key = key_copy;
    entry->values = values;
    entry->count = 0U;
    entry->capacity = 4U;
    map->count++;
    return entry;
}

static int entry_append(Entry *entry, int value)
{
    if (entry->count == entry->capacity) {
        size_t new_capacity;
        int *resized;

        if (entry->capacity > (SIZE_MAX / sizeof(int)) / 2U) {
            return -1;
        }
        new_capacity = entry->capacity * 2U;
        resized = realloc(entry->values, new_capacity * sizeof(int));
        if (resized == NULL) {
            return -1;
        }
        entry->values = resized;
        entry->capacity = new_capacity;
    }
    entry->values[entry->count] = value;
    entry->count++;
    return 0;
}

static int group_pairs(Map *map, const Pair *pairs, size_t pair_count)
{
    size_t i;

    if (map == NULL || (pairs == NULL && pair_count > 0U)) {
        return -1;
    }

    for (i = 0U; i < pair_count; i++) {
        Entry *entry;

        if (pairs[i].key == NULL) {
            return -1;
        }
        if (strnlen(pairs[i].key, MAX_KEY_LENGTH) == MAX_KEY_LENGTH) {
            return -1;
        }
        entry = map_find(map, pairs[i].key);
        if (entry == NULL) {
            entry = map_add_entry(map, pairs[i].key);
            if (entry == NULL) {
                return -1;
            }
        }
        if (entry_append(entry, pairs[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

static void map_print(const Map *map)
{
    size_t i;
    size_t j;

    if (map == NULL) {
        return;
    }
    for (i = 0U; i < map->count; i++) {
        printf("%s: [", map->entries[i].key);
        for (j = 0U; j < map->entries[i].count; j++) {
            printf("%d", map->entries[i].values[j]);
            if (j + 1U < map->entries[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    Map map;
    const Pair pairs[] = {
        { "apple", 1 },
        { "banana", 2 },
        { "apple", 3 },
        { "cherry", 4 },
        { "banana", 5 },
        { "apple", 6 }
    };
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);

    if (map_init(&map) != 0) {
        fprintf(stderr, "Failed to initialize map\n");
        return EXIT_FAILURE;
    }

    if (group_pairs(&map, pairs, pair_count) != 0) {
        fprintf(stderr, "Failed to group pairs\n");
        map_destroy(&map);
        return EXIT_FAILURE;
    }

    map_print(&map);
    map_destroy(&map);
    return EXIT_SUCCESS;
}