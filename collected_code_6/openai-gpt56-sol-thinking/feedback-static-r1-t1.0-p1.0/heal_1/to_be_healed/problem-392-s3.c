#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint64_t key;
    uint64_t value;
    bool used;
} MemoEntry;

typedef struct {
    MemoEntry *entries;
    size_t capacity;
    size_t size;
} Memo;

typedef enum {
    READ_OK,
    READ_END,
    READ_INVALID,
    READ_ERROR
} ReadStatus;

static size_t hash_uint64(uint64_t value)
{
    value ^= value >> 30;
    value *= UINT64_C(0xbf58476d1ce4e5b9);
    value ^= value >> 27;
    value *= UINT64_C(0x94d049bb133111eb);
    value ^= value >> 31;
    return (size_t)value;
}

static bool memo_init(Memo *memo)
{
    const size_t initial_capacity = 256;

    if (memo == NULL ||
        initial_capacity > SIZE_MAX / sizeof(*memo->entries)) {
        return false;
    }

    memo->entries = calloc(initial_capacity, sizeof(*memo->entries));
    if (memo->entries == NULL) {
        memo->capacity = 0;
        memo->size = 0;
        return false;
    }

    memo->capacity = initial_capacity;
    memo->size = 0;
    return true;
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

static bool memo_get(const Memo *memo, uint64_t key, uint64_t *value)
{
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL || value == NULL) {
        return false;
    }

    index = hash_uint64(key) & (memo->capacity - 1);
    start = index;

    do {
        if (!memo->entries[index].used) {
            return false;
        }

        if (memo->entries[index].key == key) {
            *value = memo->entries[index].value;
            return true;
        }

        index = (index + 1) & (memo->capacity - 1);
    } while (index != start);

    return false;
}

static bool memo_resize(Memo *memo)
{
    MemoEntry *new_entries;
    size_t new_capacity;
    size_t i;

    if (memo == NULL || memo->entries == NULL ||
        memo->capacity > SIZE_MAX / 2) {
        return false;
    }

    new_capacity = memo->capacity * 2;
    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = calloc(new_capacity, sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    for (i = 0; i < memo->capacity; ++i) {
        if (memo->entries[i].used) {
            size_t index = hash_uint64(memo->entries[i].key) &
                           (new_capacity - 1);

            while (new_entries[index].used) {
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
    size_t index;

    if (memo == NULL || memo->entries == NULL) {
        return false;
    }

    if (memo->size >= memo->capacity - memo->capacity / 4) {
        if (!memo_resize(memo)) {
            return false;
        }
    }

    index = hash_uint64(key) & (memo->capacity - 1);

    while (memo->entries[index].used) {
        if (memo->entries[index].key == key) {
            memo->entries[index].value = value;
            return true;
        }

        index = (index + 1) & (memo->capacity - 1);
    }

    memo->entries[index].key = key;
    memo->entries[index].value = value;
    memo->entries[index].used = true;
    ++memo->size;
    return true;
}

static bool compute_max_sum(uint64_t n, Memo *memo, uint64_t *result)
{
    uint64_t parts[4];
    uint64_t sum = 0;
    uint64_t cached;
    size_t i;

    if (memo == NULL || result == NULL) {
        return false;
    }

    if (n <= 5) {
        *result = n;
        return true;
    }

    if (memo_get(memo, n, &cached)) {
        *result = cached;
        return true;
    }

    if (!compute_max_sum(n / 2, memo, &parts[0]) ||
        !compute_max_sum(n / 3, memo, &parts[1]) ||
        !compute_max_sum(n / 4, memo, &parts[2]) ||
        !compute_max_sum(n / 5, memo, &parts[3])) {
        return false;
    }

    for (i = 0; i < 4; ++i) {
        if (UINT64_MAX - sum < parts[i]) {
            return false;
        }
        sum += parts[i];
    }

    if (sum < n) {
        sum = n;
    }

    if (!memo_put(memo, n, sum)) {
        return false;
    }

    *result = sum;
    return true;
}

bool max_sum(uint64_t n, uint64_t *result)
{
    Memo memo;
    bool success;

    if (result == NULL || !memo_init(&memo)) {
        return false;
    }

    success = compute_max_sum(n, &memo, result);
    memo_destroy(&memo);
    return success;
}

static bool is_whitespace(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static ReadStatus read_uint64(FILE *stream, uint64_t *value)
{
    uint64_t parsed = 0;
    int ch;
    bool invalid = false;

    if (stream == NULL || value == NULL) {
        return READ_ERROR;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != EOF && is_whitespace(ch));

    if (ch == EOF) {
        return ferror(stream) ? READ_ERROR : READ_END;
    }

    while (ch != EOF && !is_whitespace(ch)) {
        if (ch < '0' || ch > '9') {
            invalid = true;
        } else if (!invalid) {
            uint64_t digit = (uint64_t)(ch - '0');

            if (parsed > (UINT64_MAX - digit) / 10) {
                invalid = true;
            } else {
                parsed = parsed * 10 + digit;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        return READ_ERROR;
    }

    if (invalid) {
        return READ_INVALID;
    }

    *value = parsed;
    return READ_OK;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    ReadStatus status;

    for (;;) {
        status = read_uint64(stdin, &n);

        if (status == READ_END) {
            break;
        }

        if (status != READ_OK || !max_sum(n, &result)) {
            return EXIT_FAILURE;
        }

        if (printf("%llu\n", (unsigned long long)result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}