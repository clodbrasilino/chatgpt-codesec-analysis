#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    uint64_t key;
    uint64_t value;
    bool occupied;
} MemoEntry;

typedef struct {
    MemoEntry *entries;
    size_t capacity;
    size_t size;
} Memo;

static size_t hash_value(uint64_t value, size_t capacity)
{
    value ^= value >> 30;
    value *= UINT64_C(0xbf58476d1ce4e5b9);
    value ^= value >> 27;
    value *= UINT64_C(0x94d049bb133111eb);
    value ^= value >> 31;

    return (size_t)value & (capacity - 1U);
}

static bool memo_initialize(Memo *memo)
{
    const size_t initial_capacity = 1024U;

    if (memo == NULL) {
        return false;
    }

    memo->entries = NULL;
    memo->capacity = 0U;
    memo->size = 0U;

    if (initial_capacity > SIZE_MAX / sizeof(*memo->entries)) {
        return false;
    }

    memo->entries = calloc(initial_capacity, sizeof(*memo->entries));
    if (memo->entries == NULL) {
        return false;
    }

    memo->capacity = initial_capacity;
    return true;
}

static void memo_destroy(Memo *memo)
{
    if (memo == NULL) {
        return;
    }

    free(memo->entries);
    memo->entries = NULL;
    memo->capacity = 0U;
    memo->size = 0U;
}

static bool memo_get(const Memo *memo, uint64_t key, uint64_t *value)
{
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL ||
        memo->capacity == 0U || value == NULL) {
        return false;
    }

    index = hash_value(key, memo->capacity);
    start = index;

    do {
        const MemoEntry *entry = &memo->entries[index];

        if (!entry->occupied) {
            return false;
        }

        if (entry->key == key) {
            *value = entry->value;
            return true;
        }

        index = (index + 1U) & (memo->capacity - 1U);
    } while (index != start);

    return false;
}

static void memo_insert_unchecked(Memo *memo, uint64_t key, uint64_t value)
{
    size_t index = hash_value(key, memo->capacity);

    while (memo->entries[index].occupied) {
        if (memo->entries[index].key == key) {
            memo->entries[index].value = value;
            return;
        }

        index = (index + 1U) & (memo->capacity - 1U);
    }

    memo->entries[index].key = key;
    memo->entries[index].value = value;
    memo->entries[index].occupied = true;
    ++memo->size;
}

static bool memo_grow(Memo *memo)
{
    MemoEntry *new_entries;
    MemoEntry *old_entries;
    size_t old_capacity;
    size_t new_capacity;
    size_t index;

    if (memo == NULL || memo->entries == NULL ||
        memo->capacity == 0U || memo->capacity > SIZE_MAX / 2U) {
        return false;
    }

    new_capacity = memo->capacity * 2U;

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = calloc(new_capacity, sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    old_entries = memo->entries;
    old_capacity = memo->capacity;

    memo->entries = new_entries;
    memo->capacity = new_capacity;
    memo->size = 0U;

    for (index = 0U; index < old_capacity; ++index) {
        if (old_entries[index].occupied) {
            memo_insert_unchecked(
                memo,
                old_entries[index].key,
                old_entries[index].value
            );
        }
    }

    free(old_entries);
    return true;
}

static bool memo_put(Memo *memo, uint64_t key, uint64_t value)
{
    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U) {
        return false;
    }

    if (memo->size >= memo->capacity / 2U) {
        if (!memo_grow(memo)) {
            return false;
        }
    }

    memo_insert_unchecked(memo, key, value);
    return true;
}

static bool maximum_sum_recursive(uint64_t n, Memo *memo, uint64_t *result)
{
    static const uint64_t divisors[] = {
        UINT64_C(2),
        UINT64_C(3),
        UINT64_C(4),
        UINT64_C(5)
    };
    uint64_t sum = UINT64_C(0);
    uint64_t term;
    size_t index;

    if (memo == NULL || result == NULL) {
        return false;
    }

    if (n == UINT64_C(0)) {
        *result = UINT64_C(0);
        return true;
    }

    if (memo_get(memo, n, result)) {
        return true;
    }

    for (index = 0U; index < sizeof(divisors) / sizeof(divisors[0]); ++index) {
        if (!maximum_sum_recursive(n / divisors[index], memo, &term)) {
            return false;
        }

        if (term > UINT64_MAX - sum) {
            return false;
        }

        sum += term;
    }

    *result = sum > n ? sum : n;
    return memo_put(memo, n, *result);
}

static bool maximum_sum(uint64_t n, uint64_t *result)
{
    Memo memo;
    bool success;

    if (result == NULL) {
        return false;
    }

    if (!memo_initialize(&memo)) {
        return false;
    }

    success = maximum_sum_recursive(n, &memo, result);
    memo_destroy(&memo);

    return success;
}

static bool read_input(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    const unsigned char *cursor;
    uint64_t parsed = UINT64_C(0);
    size_t length;
    bool have_digit = false;

    if (value == NULL) {
        return false;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    if (ferror(stdin)) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length == 0U) {
        return false;
    }

    if (buffer[length - 1U] != '\n' && !feof(stdin)) {
        return false;
    }

    cursor = (const unsigned char *)buffer;

    while (*cursor != '\0' && isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor == '+') {
        ++cursor;
    }

    while (*cursor >= (unsigned char)'0' &&
           *cursor <= (unsigned char)'9') {
        uint64_t digit = (uint64_t)(*cursor - (unsigned char)'0');

        if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        parsed = parsed * UINT64_C(10) + digit;
        have_digit = true;
        ++cursor;
    }

    if (!have_digit) {
        return false;
    }

    while (*cursor != '\0' && isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        return false;
    }

    *value = parsed;
    return true;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (!read_input(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!maximum_sum(n, &result)) {
        fputs("Unable to calculate result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}