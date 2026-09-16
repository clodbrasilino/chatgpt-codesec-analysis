#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    Pair key;
    size_t count;
    int occupied;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t capacity;
} PairMap;

static size_t hash_pair(Pair pair)
{
    uint64_t x = (uint32_t)pair.first;
    uint64_t y = (uint32_t)pair.second;

    x ^= x >> 16;
    x *= UINT64_C(0x7feb352d);
    x ^= x >> 15;
    x *= UINT64_C(0x846ca68b);
    x ^= x >> 16;

    y ^= y >> 16;
    y *= UINT64_C(0x7feb352d);
    y ^= y >> 15;
    y *= UINT64_C(0x846ca68b);
    y ^= y >> 16;

    return (size_t)(x ^ (y + UINT64_C(0x9e3779b97f4a7c15) + (x << 6) + (x >> 2)));
}

static int pairs_equal(Pair left, Pair right)
{
    return left.first == right.first && left.second == right.second;
}

static int next_capacity(size_t required, size_t *capacity)
{
    size_t result = 8U;

    if (capacity == NULL || required > SIZE_MAX / 2U) {
        return 0;
    }

    required *= 2U;
    while (result < required) {
        if (result > SIZE_MAX / 2U) {
            return 0;
        }
        result *= 2U;
    }

    *capacity = result;
    return 1;
}

static int map_init(PairMap *map, size_t expected_entries)
{
    size_t capacity;

    if (map == NULL || !next_capacity(expected_entries, &capacity)) {
        return 0;
    }

    map->entries = calloc(capacity, sizeof(*map->entries));
    if (map->entries == NULL) {
        map->capacity = 0U;
        return 0;
    }

    map->capacity = capacity;
    return 1;
}

static void map_destroy(PairMap *map)
{
    if (map != NULL) {
        free(map->entries);
        map->entries = NULL;
        map->capacity = 0U;
    }
}

static int map_increment(PairMap *map, Pair key)
{
    size_t index;
    size_t attempts;

    if (map == NULL || map->entries == NULL || map->capacity == 0U) {
        return 0;
    }

    index = hash_pair(key) & (map->capacity - 1U);

    for (attempts = 0U; attempts < map->capacity; ++attempts) {
        MapEntry *entry = &map->entries[index];

        if (!entry->occupied) {
            entry->key = key;
            entry->count = 1U;
            entry->occupied = 1;
            return 1;
        }

        if (pairs_equal(entry->key, key)) {
            if (entry->count == SIZE_MAX) {
                return 0;
            }
            ++entry->count;
            return 1;
        }

        index = (index + 1U) & (map->capacity - 1U);
    }

    return 0;
}

static size_t map_get(const PairMap *map, Pair key)
{
    size_t index;
    size_t attempts;

    if (map == NULL || map->entries == NULL || map->capacity == 0U) {
        return 0U;
    }

    index = hash_pair(key) & (map->capacity - 1U);

    for (attempts = 0U; attempts < map->capacity; ++attempts) {
        const MapEntry *entry = &map->entries[index];

        if (!entry->occupied) {
            return 0U;
        }

        if (pairs_equal(entry->key, key)) {
            return entry->count;
        }

        index = (index + 1U) & (map->capacity - 1U);
    }

    return 0U;
}

static int count_same_pairs(const Pair *first_list,
                            size_t first_length,
                            const Pair *second_list,
                            size_t second_length,
                            size_t *result)
{
    PairMap map = {NULL, 0U};
    size_t total = 0U;
    size_t i;

    if (result == NULL ||
        (first_list == NULL && first_length != 0U) ||
        (second_list == NULL && second_length != 0U)) {
        return 0;
    }

    if (!map_init(&map, first_length)) {
        return 0;
    }

    for (i = 0U; i < first_length; ++i) {
        if (!map_increment(&map, first_list[i])) {
            map_destroy(&map);
            return 0;
        }
    }

    for (i = 0U; i < second_length; ++i) {
        size_t matches = map_get(&map, second_list[i]);

        if (matches > SIZE_MAX - total) {
            map_destroy(&map);
            return 0;
        }
        total += matches;
    }

    map_destroy(&map);
    *result = total;
    return 1;
}

int main(void)
{
    const Pair first_list[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}};
    const Pair second_list[] = {{1, 2}, {5, 6}, {1, 2}, {7, 8}};
    size_t count;

    if (!count_same_pairs(first_list,
                          sizeof(first_list) / sizeof(first_list[0]),
                          second_list,
                          sizeof(second_list) / sizeof(second_list[0]),
                          &count)) {
        fputs("Failed to count pairs\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}