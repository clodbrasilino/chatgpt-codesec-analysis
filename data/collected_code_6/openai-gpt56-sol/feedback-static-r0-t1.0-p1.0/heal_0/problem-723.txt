#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    return (size_t)(x ^ (y + UINT64_C(0x9e3779b97f4a7c15) +
                         (x << 6) + (x >> 2)));
}

static int pair_equal(Pair left, Pair right)
{
    return left.first == right.first && left.second == right.second;
}

static size_t next_power_of_two(size_t value)
{
    size_t result = 1;

    while (result < value) {
        if (result > SIZE_MAX / 2) {
            return 0;
        }
        result *= 2;
    }

    return result;
}

static int map_create(PairMap *map, size_t expected_entries)
{
    size_t requested;

    if (map == NULL) {
        return 0;
    }

    map->entries = NULL;
    map->capacity = 0;

    if (expected_entries > (SIZE_MAX - 1) / 2) {
        return 0;
    }

    requested = expected_entries * 2 + 1;
    if (requested < 8) {
        requested = 8;
    }

    map->capacity = next_power_of_two(requested);
    if (map->capacity == 0 ||
        map->capacity > SIZE_MAX / sizeof(*map->entries)) {
        map->capacity = 0;
        return 0;
    }

    map->entries = calloc(map->capacity, sizeof(*map->entries));
    if (map->entries == NULL) {
        map->capacity = 0;
        return 0;
    }

    return 1;
}

static void map_destroy(PairMap *map)
{
    if (map != NULL) {
        free(map->entries);
        map->entries = NULL;
        map->capacity = 0;
    }
}

static int map_increment(PairMap *map, Pair key)
{
    size_t index;
    size_t probes;

    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return 0;
    }

    index = hash_pair(key) & (map->capacity - 1);

    for (probes = 0; probes < map->capacity; ++probes) {
        MapEntry *entry = &map->entries[index];

        if (!entry->occupied) {
            entry->key = key;
            entry->count = 1;
            entry->occupied = 1;
            return 1;
        }

        if (pair_equal(entry->key, key)) {
            if (entry->count == SIZE_MAX) {
                return 0;
            }
            ++entry->count;
            return 1;
        }

        index = (index + 1) & (map->capacity - 1);
    }

    return 0;
}

static size_t *map_find(PairMap *map, Pair key)
{
    size_t index;
    size_t probes;

    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return NULL;
    }

    index = hash_pair(key) & (map->capacity - 1);

    for (probes = 0; probes < map->capacity; ++probes) {
        MapEntry *entry = &map->entries[index];

        if (!entry->occupied) {
            return NULL;
        }

        if (pair_equal(entry->key, key)) {
            return &entry->count;
        }

        index = (index + 1) & (map->capacity - 1);
    }

    return NULL;
}

static int count_same_pairs(const Pair *first_list, size_t first_length,
                            const Pair *second_list, size_t second_length,
                            size_t *result)
{
    PairMap map;
    size_t total = 0;
    size_t i;

    if (result == NULL ||
        (first_list == NULL && first_length != 0) ||
        (second_list == NULL && second_length != 0)) {
        return 0;
    }

    *result = 0;

    if (!map_create(&map, first_length)) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (!map_increment(&map, first_list[i])) {
            map_destroy(&map);
            return 0;
        }
    }

    for (i = 0; i < second_length; ++i) {
        size_t *count = map_find(&map, second_list[i]);

        if (count != NULL && *count > 0) {
            if (total == SIZE_MAX) {
                map_destroy(&map);
                return 0;
            }
            ++total;
            --(*count);
        }
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
        fputs("Failed to count matching pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}