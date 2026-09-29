#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    size_t count;
    int occupied;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t capacity;
} Map;

static size_t hash_int(int value, size_t capacity)
{
    unsigned int x = (unsigned int)value;
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return (size_t)x % capacity;
}

static int map_init(Map *map, size_t item_count)
{
    size_t capacity = 16;

    if (map == NULL || item_count > (SIZE_MAX - 1U) / 2U) {
        return 0;
    }

    while (capacity < (item_count * 2U) + 1U) {
        if (capacity > SIZE_MAX / 2U) {
            return 0;
        }
        capacity *= 2U;
    }

    if (capacity > SIZE_MAX / sizeof(*map->entries)) {
        return 0;
    }

    map->entries = calloc(capacity, sizeof(*map->entries));
    if (map->entries == NULL) {
        map->capacity = 0;
        return 0;
    }

    map->capacity = capacity;
    return 1;
}

static void map_destroy(Map *map)
{
    if (map != NULL) {
        free(map->entries);
        map->entries = NULL;
        map->capacity = 0;
    }
}

static int map_increment(Map *map, int key)
{
    size_t index;
    size_t probes;

    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return 0;
    }

    index = hash_int(key, map->capacity);

    for (probes = 0; probes < map->capacity; ++probes) {
        MapEntry *entry = &map->entries[index];

        if (!entry->occupied) {
            entry->key = key;
            entry->count = 1;
            entry->occupied = 1;
            return 1;
        }

        if (entry->key == key) {
            if (entry->count == SIZE_MAX) {
                return 0;
            }
            ++entry->count;
            return 1;
        }

        index = (index + 1U) % map->capacity;
    }

    return 0;
}

static int map_take(Map *map, int key)
{
    size_t index;
    size_t probes;

    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return 0;
    }

    index = hash_int(key, map->capacity);

    for (probes = 0; probes < map->capacity; ++probes) {
        MapEntry *entry = &map->entries[index];

        if (!entry->occupied) {
            return 0;
        }

        if (entry->key == key) {
            if (entry->count == 0) {
                return 0;
            }
            --entry->count;
            return 1;
        }

        index = (index + 1U) % map->capacity;
    }

    return 0;
}

static int count_same_pairs(const int *first, size_t first_length,
                            const int *second, size_t second_length,
                            size_t *result)
{
    Map map = {NULL, 0};
    size_t count = 0;
    size_t i;

    if (result == NULL ||
        (first == NULL && first_length != 0) ||
        (second == NULL && second_length != 0)) {
        return 0;
    }

    if (!map_init(&map, first_length)) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (!map_increment(&map, first[i])) {
            map_destroy(&map);
            return 0;
        }
    }

    for (i = 0; i < second_length; ++i) {
        if (map_take(&map, second[i])) {
            if (count == SIZE_MAX) {
                map_destroy(&map);
                return 0;
            }
            ++count;
        }
    }

    map_destroy(&map);
    *result = count;
    return 1;
}

int main(void)
{
    const int first[] = {1, 2, 2, 3, 4};
    const int second[] = {2, 2, 2, 3, 5};
    size_t pair_count;

    if (!count_same_pairs(first, sizeof(first) / sizeof(first[0]),
                          second, sizeof(second) / sizeof(second[0]),
                          &pair_count)) {
        fputs("Failed to count pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pair_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}