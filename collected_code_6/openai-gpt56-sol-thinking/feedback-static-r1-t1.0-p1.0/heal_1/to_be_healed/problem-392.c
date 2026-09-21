#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
    memo->capacity = 64;
    memo->size = 0;
    memo->entries = calloc(memo->capacity, sizeof(*memo->entries));
    return memo->entries != NULL;
}

static void memo_destroy(Memo *memo)
{
    free(memo->entries);
    memo->entries = NULL;
    memo->capacity = 0;
    memo->size = 0;
}

static bool memo_get(const Memo *memo, uint64_t key, uint64_t *value)
{
    size_t index = (size_t)(hash_key(key) & (uint64_t)(memo->capacity - 1));

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
    if (memo->capacity > SIZE_MAX / 2) {
        return false;
    }

    size_t new_capacity = memo->capacity * 2;
    MemoEntry *new_entries = calloc(new_capacity, sizeof(*new_entries));

    if (new_entries == NULL) {
        return false;
    }

    for (size_t i = 0; i < memo->capacity; ++i) {
        if (memo->entries[i].occupied) {
            size_t index = (size_t)(hash_key(memo->entries[i].key) &
                                    (uint64_t)(new_capacity - 1));

            while (new_entries[index].occupied) {
                index = (index + 1) & (new_capacity - 1);
            }

            new_entries[index] = memo->entries[i];
        }
    }

    free(memo->entries);
    memo->entries = new_entries;
    memo->capacity = new_capacity;
    return true;
}

static bool memo_put(Memo *memo, uint64_t key, uint64_t value)
{
    if (memo->size >= memo->capacity - memo->capacity / 3) {
        if (!memo_rehash(memo)) {
            return false;
        }
    }

    size_t index = (size_t)(hash_key(key) & (uint64_t)(memo->capacity - 1));

    while (memo->entries[index].occupied) {
        if (memo->entries[index].key == key) {
            memo->entries[index].value = value;
            return true;
        }
        index = (index + 1) & (memo->capacity - 1);
    }

    memo->entries[index].key = key;
    memo->entries[index].value = value;
    memo->entries[index].occupied = true;
    ++memo->size;
    return true;
}

static bool checked_add(uint64_t left, uint64_t right, uint64_t *result)
{
    if (UINT64_MAX - left < right) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool calculate_maximum_sum(uint64_t n, Memo *memo, uint64_t *result)
{
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        return false;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return false;
    }

    errno = 0;
    char *end;
    uintmax_t value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *number = (uint64_t)value;
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