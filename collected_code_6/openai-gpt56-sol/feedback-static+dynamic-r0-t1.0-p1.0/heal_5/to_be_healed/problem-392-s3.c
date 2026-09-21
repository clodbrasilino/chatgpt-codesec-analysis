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

        index = (index + 1U == map->capacity) ? 0U : index + 1U;
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
                index = (index + 1U == expanded.capacity) ? 0U : index + 1U;
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

        index = (index + 1U == map->capacity) ? 0U : index + 1U;
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

        index = (index + 1U == map->capacity) ? 0U : index + 1U;
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
    enum { INPUT_SIZE = 128 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[INPUT_SIZE];
    char *end;
    uintmax_t parsed;
    size_t length;

    if (value == NULL || fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }

    length = 0U;
    while (length < sizeof(line) && line[length] != '\0') {
        ++length;
    }

    if (length == sizeof(line)) {
        return 0;
    }

    if (length == 0U || line[length - 1U] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            }
            return 0;
        }

        if (ferror(stdin)) {
            return 0;
        }
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno == ERANGE || end == line || parsed > UINT64_MAX) {
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
        return 0;
    }

    *value = (uint64_t)parsed;
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