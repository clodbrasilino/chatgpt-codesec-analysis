#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strchr'
  */

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
    if (map == NULL || capacity == 0 ||
        capacity > SIZE_MAX / sizeof(*map->entries)) {
        return 0;
    }

    map->entries = calloc(capacity, sizeof(*map->entries));
    if (map->entries == NULL) {
        map->capacity = 0;
        map->size = 0;
        return 0;
    }

    map->capacity = capacity;
    map->size = 0;
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
        if (map->entries[index].used == 0U) {
            return 0;
        }

        if (map->entries[index].key == key) {
            *value = map->entries[index].value;
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
        if (map->entries[index].used == 0U) {
            map->entries[index].key = key;
            map->entries[index].value = value;
            map->entries[index].used = 1U;
            ++map->size;
            return 1;
        }

        if (map->entries[index].key == key) {
            map->entries[index].value = value;
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
    if (new_capacity > SIZE_MAX / sizeof(*map->entries)) {
        return 0;
    }

    if (!map_init(&replacement, new_capacity)) {
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
    if (map == NULL || map->entries == NULL || map->capacity == 0) {
        return 0;
    }

    if (map->size >= map->capacity - map->capacity / 4U &&
        !map_resize(map)) {
        return 0;
    }

    return map_insert_raw(map, key, value);
}

static int add_checked(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || UINT64_MAX - left < right) {
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

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strchr'
     *  implicit declaration of function 'strchr' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strchr' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);
    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        return 0;
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
    HashMap memo;
    uint64_t n;
    uint64_t result;

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
        map_destroy(&memo);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output failed\n", stderr);
        map_destroy(&memo);
        return EXIT_FAILURE;
    }

    map_destroy(&memo);
    return EXIT_SUCCESS;
}