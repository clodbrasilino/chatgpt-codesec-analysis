#include <ctype.h>
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
} Memo;

static uint64_t hash_u64(uint64_t value)
{
    value ^= value >> 30;
    value *= UINT64_C(0xbf58476d1ce4e5b9);
    value ^= value >> 27;
    value *= UINT64_C(0x94d049bb133111eb);
    value ^= value >> 31;
    return value;
}

static int memo_init(Memo *memo, size_t capacity)
{
    if (memo == NULL || capacity == 0 ||
        capacity > SIZE_MAX / sizeof(*memo->entries)) {
        return 0;
    }

    memo->entries = calloc(capacity, sizeof(*memo->entries));
    if (memo->entries == NULL) {
        memo->capacity = 0;
        memo->size = 0;
        return 0;
    }

    memo->capacity = capacity;
    memo->size = 0;
    return 1;
}

static void memo_destroy(Memo *memo)
{
    if (memo != NULL) {
        free(memo->entries);
        memo->entries = NULL;
        memo->capacity = 0;
        memo->size = 0;
    }
}

static int memo_insert_raw(Memo *memo, uint64_t key, uint64_t value)
{
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return 0;
    }

    index = (size_t)(hash_u64(key) % memo->capacity);
    start = index;

    do {
        Entry *entry = &memo->entries[index];

        if (!entry->occupied) {
            entry->key = key;
            entry->value = value;
            entry->occupied = 1;
            ++memo->size;
            return 1;
        }

        if (entry->key == key) {
            entry->value = value;
            return 1;
        }

        ++index;
        if (index == memo->capacity) {
            index = 0;
        }
    } while (index != start);

    return 0;
}

static int memo_resize(Memo *memo)
{
    Memo resized = { NULL, 0, 0 };
    size_t new_capacity;
    size_t i;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0 ||
        memo->capacity > SIZE_MAX / 2) {
        return 0;
    }

    new_capacity = memo->capacity * 2;

    if (new_capacity > SIZE_MAX / sizeof(*memo->entries) ||
        !memo_init(&resized, new_capacity)) {
        return 0;
    }

    for (i = 0; i < memo->capacity; ++i) {
        const Entry *entry = &memo->entries[i];

        if (entry->occupied &&
            !memo_insert_raw(&resized, entry->key, entry->value)) {
            memo_destroy(&resized);
            return 0;
        }
    }

    free(memo->entries);
    *memo = resized;
    return 1;
}

static int memo_get(const Memo *memo, uint64_t key, uint64_t *value)
{
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0 ||
        value == NULL) {
        return 0;
    }

    index = (size_t)(hash_u64(key) % memo->capacity);
    start = index;

    do {
        const Entry *entry = &memo->entries[index];

        if (!entry->occupied) {
            return 0;
        }

        if (entry->key == key) {
            *value = entry->value;
            return 1;
        }

        ++index;
        if (index == memo->capacity) {
            index = 0;
        }
    } while (index != start);

    return 0;
}

static int memo_put(Memo *memo, uint64_t key, uint64_t value)
{
    uint64_t existing;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return 0;
    }

    if (memo_get(memo, key, &existing)) {
        return memo_insert_raw(memo, key, value);
    }

    if (memo->size >= memo->capacity / 2 && !memo_resize(memo)) {
        return 0;
    }

    return memo_insert_raw(memo, key, value);
}

static int checked_add(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || left > UINT64_MAX - right) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int maximum_sum(uint64_t n, Memo *memo, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t sum;

    if (memo == NULL || result == NULL) {
        return 0;
    }

    if (n == 0) {
        *result = 0;
        return 1;
    }

    if (memo_get(memo, n, result)) {
        return 1;
    }

    if (!maximum_sum(n / 2, memo, &a) ||
        !maximum_sum(n / 3, memo, &b) ||
        !maximum_sum(n / 4, memo, &c) ||
        !maximum_sum(n / 5, memo, &d) ||
        !checked_add(a, b, &sum) ||
        !checked_add(sum, c, &sum) ||
        !checked_add(sum, d, &sum)) {
        return 0;
    }

    *result = sum > n ? sum : n;
    return memo_put(memo, n, *result);
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
    size_t length;
    int ch;

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (buffer[length] == '\0' && !feof(stdin)) {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return 0;
        }

        return 0;
    }

    start = buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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
    Memo memo = { NULL, 0, 0 };
    uint64_t n;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!memo_init(&memo, 64)) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!maximum_sum(n, &memo, &result)) {
        fputs("Computation failed\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    memo_destroy(&memo);
    return status;
}