#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t key;
    uint64_t value;
    unsigned char occupied;
} Entry;

typedef struct {
    Entry *entries;
    size_t capacity;
    size_t size;
} HashMap;

static uint64_t hash_value(uint64_t value)
{
    value ^= value >> 30;
    value *= UINT64_C(0xbf58476d1ce4e5b9);
    value ^= value >> 27;
    value *= UINT64_C(0x94d049bb133111eb);
    return value ^ (value >> 31);
}

static int map_init(HashMap *map, size_t capacity)
{
    if (map == NULL || capacity == 0U ||
        capacity > SIZE_MAX / sizeof(*map->entries)) {
        return 0;
    }

    map->entries = calloc(capacity, sizeof(*map->entries));
    if (map->entries == NULL) {
        map->capacity = 0U;
        map->size = 0U;
        return 0;
    }

    map->capacity = capacity;
    map->size = 0U;
    return 1;
}

static void map_destroy(HashMap *map)
{
    if (map != NULL) {
        free(map->entries);
        map->entries = NULL;
        map->capacity = 0U;
        map->size = 0U;
    }
}

static int map_get(const HashMap *map, uint64_t key, uint64_t *value)
{
    size_t index;

    if (map == NULL || value == NULL || map->entries == NULL ||
        map->capacity == 0U) {
        return 0;
    }

    index = (size_t)(hash_value(key) % map->capacity);

    for (size_t probes = 0U; probes < map->capacity; ++probes) {
        const Entry *entry = &map->entries[index];

        if (entry->occupied == 0U) {
            return 0;
        }

        if (entry->key == key) {
            *value = entry->value;
            return 1;
        }

        ++index;
        if (index == map->capacity) {
            index = 0U;
        }
    }

    return 0;
}

static int map_resize(HashMap *map)
{
    HashMap expanded = {NULL, 0U, 0U};
    size_t new_capacity;

    if (map == NULL || map->entries == NULL || map->capacity == 0U ||
        map->capacity > SIZE_MAX / 2U) {
        return 0;
    }

    new_capacity = map->capacity * 2U;
    if (!map_init(&expanded, new_capacity)) {
        return 0;
    }

    for (size_t i = 0U; i < map->capacity; ++i) {
        if (map->entries[i].occupied != 0U) {
            size_t index =
                (size_t)(hash_value(map->entries[i].key) % expanded.capacity);

            while (expanded.entries[index].occupied != 0U) {
                ++index;
                if (index == expanded.capacity) {
                    index = 0U;
                }
            }

            expanded.entries[index] = map->entries[i];
            ++expanded.size;
        }
    }

    free(map->entries);
    *map = expanded;
    return 1;
}

static int map_put(HashMap *map, uint64_t key, uint64_t value)
{
    size_t index;

    if (map == NULL || map->entries == NULL || map->capacity == 0U) {
        return 0;
    }

    index = (size_t)(hash_value(key) % map->capacity);

    for (size_t probes = 0U; probes < map->capacity; ++probes) {
        Entry *entry = &map->entries[index];

        if (entry->occupied == 0U) {
            break;
        }

        if (entry->key == key) {
            entry->value = value;
            return 1;
        }

        ++index;
        if (index == map->capacity) {
            index = 0U;
        }
    }

    if (map->size >= map->capacity - map->capacity / 4U) {
        if (!map_resize(map)) {
            return 0;
        }
        index = (size_t)(hash_value(key) % map->capacity);
    }

    for (size_t probes = 0U; probes < map->capacity; ++probes) {
        Entry *entry = &map->entries[index];

        if (entry->occupied == 0U) {
            entry->key = key;
            entry->value = value;
            entry->occupied = 1U;
            ++map->size;
            return 1;
        }

        if (entry->key == key) {
            entry->value = value;
            return 1;
        }

        ++index;
        if (index == map->capacity) {
            index = 0U;
        }
    }

    return 0;
}

static int checked_add(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || right > UINT64_MAX - left) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int maximum_sum(uint64_t n, HashMap *memo, uint64_t *result)
{
    uint64_t half;
    uint64_t third;
    uint64_t quarter;
    uint64_t fifth;
    uint64_t sum;

    if (memo == NULL || result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = 0U;
        return 1;
    }

    if (map_get(memo, n, result)) {
        return 1;
    }

    if (!maximum_sum(n / 2U, memo, &half) ||
        !maximum_sum(n / 3U, memo, &third) ||
        !maximum_sum(n / 4U, memo, &quarter) ||
        !maximum_sum(n / 5U, memo, &fifth)) {
        return 0;
    }

    if (!checked_add(half, third, &sum) ||
        !checked_add(sum, quarter, &sum) ||
        !checked_add(sum, fifth, &sum)) {
        return 0;
    }

    *result = sum > n ? sum : n;
    return map_put(memo, n, *result);
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(line);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(line);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 32U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    return 0;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
        if (ch == '\n') {
            break;
        }
    }

    line[length] = '\0';

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    HashMap memo = {NULL, 0U, 0U};
    uint64_t n;
    uint64_t result;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!map_init(&memo, 1024U)) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!maximum_sum(n, &memo, &result)) {
        map_destroy(&memo);
        fputs("Computation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        map_destroy(&memo);
        return EXIT_FAILURE;
    }

    map_destroy(&memo);
    return EXIT_SUCCESS;
}