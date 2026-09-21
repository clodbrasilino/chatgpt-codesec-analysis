#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static uint64_t hash_key(uint64_t key)
{
    key ^= key >> 30;
    key *= UINT64_C(0xbf58476d1ce4e5b9);
    key ^= key >> 27;
    key *= UINT64_C(0x94d049bb133111eb);
    key ^= key >> 31;
    return key;
}

static bool memo_init(Memo *memo)
{
    if (memo == NULL) {
        return false;
    }

    memo->capacity = 64;
    memo->size = 0;

    if (memo->capacity > SIZE_MAX / sizeof(*memo->entries)) {
        memo->entries = NULL;
        memo->capacity = 0;
        return false;
    }

    memo->entries = calloc(memo->capacity, sizeof(*memo->entries));
    if (memo->entries == NULL) {
        memo->capacity = 0;
        return false;
    }

    return true;
}

static void memo_destroy(Memo *memo)
{
    if (memo == NULL) {
        return;
    }

    free(memo->entries);
    memo->entries = NULL;
    memo->capacity = 0;
    memo->size = 0;
}

static bool memo_get(const Memo *memo, uint64_t key, uint64_t *value)
{
    if (memo == NULL || memo->entries == NULL ||
        memo->capacity == 0 || value == NULL) {
        return false;
    }

    size_t index =
        (size_t)(hash_key(key) & (uint64_t)(memo->capacity - 1));

    while (memo->entries[index].occupied) {
        if (memo->entries[index].key == key) {
            *value = memo->entries[index].value;
            return true;
        }

        index = (index + 1) & (memo->capacity - 1);
    }

    return false;
}

static bool memo_rehash(Memo *memo)
{
    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return false;
    }

    if (memo->capacity > SIZE_MAX / 2) {
        return false;
    }

    size_t new_capacity = memo->capacity * 2;

    if (new_capacity > SIZE_MAX / sizeof(*memo->entries)) {
        return false;
    }

    MemoEntry *new_entries = calloc(new_capacity, sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    for (size_t i = 0; i < memo->capacity; ++i) {
        if (!memo->entries[i].occupied) {
            continue;
        }

        size_t index =
            (size_t)(hash_key(memo->entries[i].key) &
                     (uint64_t)(new_capacity - 1));

        while (new_entries[index].occupied) {
            index = (index + 1) & (new_capacity - 1);
        }

        new_entries[index] = memo->entries[i];
    }

    free(memo->entries);
    memo->entries = new_entries;
    memo->capacity = new_capacity;
    return true;
}

static bool memo_put(Memo *memo, uint64_t key, uint64_t value)
{
    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return false;
    }

    size_t index =
        (size_t)(hash_key(key) & (uint64_t)(memo->capacity - 1));

    while (memo->entries[index].occupied) {
        if (memo->entries[index].key == key) {
            memo->entries[index].value = value;
            return true;
        }

        index = (index + 1) & (memo->capacity - 1);
    }

    if (memo->size >= memo->capacity - memo->capacity / 3) {
        if (!memo_rehash(memo)) {
            return false;
        }

        index = (size_t)(hash_key(key) &
                         (uint64_t)(memo->capacity - 1));

        while (memo->entries[index].occupied) {
            index = (index + 1) & (memo->capacity - 1);
        }
    }

    memo->entries[index].key = key;
    memo->entries[index].value = value;
    memo->entries[index].occupied = true;
    ++memo->size;
    return true;
}

static bool checked_add(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || right > UINT64_MAX - left) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool calculate_maximum_sum(uint64_t n, Memo *memo, uint64_t *result)
{
    if (memo == NULL || result == NULL) {
        return false;
    }

    if (n < 2) {
        *result = n;
        return true;
    }

    if (memo_get(memo, n, result)) {
        return true;
    }

    uint64_t half;
    uint64_t third;
    uint64_t quarter;
    uint64_t fifth;
    uint64_t sum;

    if (!calculate_maximum_sum(n / 2, memo, &half) ||
        !calculate_maximum_sum(n / 3, memo, &third) ||
        !calculate_maximum_sum(n / 4, memo, &quarter) ||
        !calculate_maximum_sum(n / 5, memo, &fifth) ||
        !checked_add(half, third, &sum) ||
        !checked_add(sum, quarter, &sum) ||
        !checked_add(sum, fifth, &sum)) {
        return false;
    }

    *result = sum > n ? sum : n;
    return memo_put(memo, n, *result);
}

static bool find_maximum_sum(uint64_t n, uint64_t *result)
{
    if (result == NULL) {
        return false;
    }

    Memo memo;

    if (!memo_init(&memo)) {
        return false;
    }

    bool success = calculate_maximum_sum(n, &memo, result);
    memo_destroy(&memo);
    return success;
}

static bool read_input(uint64_t *number)
{
    if (number == NULL) {
        return false;
    }

    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF || ch == '-') {
        return false;
    }

    if (ch == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return false;
        }
    }

    if (!isdigit((unsigned char)ch)) {
        return false;
    }

    uint64_t value = 0;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (value > (UINT64_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isdigit((unsigned char)ch));

    while (ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            return false;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        return false;
    }

    *number = value;
    return true;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (!read_input(&number)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!find_maximum_sum(number, &result)) {
        fprintf(stderr, "Unable to calculate result\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}