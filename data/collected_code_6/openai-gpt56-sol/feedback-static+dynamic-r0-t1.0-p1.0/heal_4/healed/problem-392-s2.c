#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t key;
    uint64_t value;
    unsigned char used;
} Entry;

typedef struct {
    Entry *entries;
    size_t capacity;
    size_t size;
} HashMap;

static uint64_t hash_uint64(uint64_t value)
{
    value ^= value >> 30;
    value *= UINT64_C(0xbf58476d1ce4e5b9);
    value ^= value >> 27;
    value *= UINT64_C(0x94d049bb133111eb);
    value ^= value >> 31;
    return value;
}

static int map_init(HashMap *map, size_t capacity)
{
    if (map == NULL) {
        return 0;
    }

    map->entries = NULL;
    map->capacity = 0;
    map->size = 0;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(*map->entries)) {
        return 0;
    }

    map->entries = calloc(capacity, sizeof(*map->entries));
    if (map->entries == NULL) {
        return 0;
    }

    map->capacity = capacity;
    return 1;
}

static void map_destroy(HashMap *map)
{
    if (map != NULL) {
        free(map->entries);
        map->entries = NULL;
        map->capacity = 0;
        map->size = 0;
    }
}

static int map_find(const HashMap *map, uint64_t key, uint64_t *value)
{
    size_t index;
    size_t probes;

    if (map == NULL || value == NULL || map->entries == NULL ||
        map->capacity == 0) {
        return 0;
    }

    index = (size_t)(hash_uint64(key) % map->capacity);

    for (probes = 0; probes < map->capacity; ++probes) {
        const Entry *entry = &map->entries[index];

        if (entry->used == 0U) {
            return 0;
        }

        if (entry->key == key) {
            *value = entry->value;
            return 1;
        }

        index = (index + 1U) % map->capacity;
    }

    return 0;
}

static int map_insert_raw(HashMap *map, uint64_t key, uint64_t value)
{
    size_t index;
    size_t probes;

    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return 0;
    }

    index = (size_t)(hash_uint64(key) % map->capacity);

    for (probes = 0; probes < map->capacity; ++probes) {
        Entry *entry = &map->entries[index];

        if (entry->used == 0U) {
            entry->key = key;
            entry->value = value;
            entry->used = 1U;
            ++map->size;
            return 1;
        }

        if (entry->key == key) {
            entry->value = value;
            return 1;
        }

        index = (index + 1U) % map->capacity;
    }

    return 0;
}

static int map_resize(HashMap *map)
{
    HashMap replacement;
    size_t new_capacity;
    size_t i;

    if (map == NULL || map->entries == NULL || map->capacity == 0 ||
        map->capacity > SIZE_MAX / 2U) {
        return 0;
    }

    new_capacity = map->capacity * 2U;

    if (new_capacity > SIZE_MAX / sizeof(*map->entries) ||
        !map_init(&replacement, new_capacity)) {
        return 0;
    }

    for (i = 0; i < map->capacity; ++i) {
        if (map->entries[i].used != 0U &&
            !map_insert_raw(&replacement, map->entries[i].key,
                            map->entries[i].value)) {
            map_destroy(&replacement);
            return 0;
        }
    }

    free(map->entries);
    *map = replacement;
    return 1;
}

static int map_insert(HashMap *map, uint64_t key, uint64_t value)
{
    uint64_t ignored;
    size_t resize_threshold;

    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return 0;
    }

    if (map_find(map, key, &ignored)) {
        return map_insert_raw(map, key, value);
    }

    resize_threshold = map->capacity - map->capacity / 4U;

    if (map->size >= resize_threshold && !map_resize(map)) {
        return 0;
    }

    return map_insert_raw(map, key, value);
}

static int add_checked(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || right > UINT64_MAX - left) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int max_sum(uint64_t n, HashMap *memo, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t sum;

    if (memo == NULL || result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = 0U;
        return 1;
    }

    if (map_find(memo, n, result)) {
        return 1;
    }

    if (!max_sum(n / 2U, memo, &a) ||
        !max_sum(n / 3U, memo, &b) ||
        !max_sum(n / 4U, memo, &c) ||
        !max_sum(n / 5U, memo, &d)) {
        return 0;
    }

    if (!add_checked(a, b, &sum) ||
        !add_checked(sum, c, &sum) ||
        !add_checked(sum, d, &sum)) {
        return 0;
    }

    *result = sum > n ? sum : n;
    return map_insert(memo, n, *result);
}

static int discard_line(FILE *stream)
{
    int ch;

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stream);
}

static int read_uint64(uint64_t *value)
{
    char buffer[256];
    size_t length;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] != '\n' && buffer[length] == '\0') {
        if (!feof(stdin) && !discard_line(stdin)) {
            return 0;
        }
        if (!feof(stdin)) {
            return 0;
        }
    }

    buffer[length] = '\0';
    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return 0;
    }

    parsed = 0;
    end = start;

    while (isdigit((unsigned char)*end)) {
        unsigned int digit = (unsigned int)(*end - '0');

        if (parsed > (UINT64_MAX - digit) / UINTMAX_C(10)) {
            return 0;
        }

        parsed = parsed * UINTMAX_C(10) + digit;
        ++end;
    }

    while (isspace((unsigned char)*end)) {
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
    HashMap memo = { NULL, 0, 0 };
    uint64_t n;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!map_init(&memo, 128U)) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!max_sum(n, &memo, &result)) {
        fputs("Computation failed\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output failed\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    map_destroy(&memo);
    return status;
}