#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
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

typedef enum {
    INPUT_LEADING,
    INPUT_AFTER_SIGN,
    INPUT_DIGITS,
    INPUT_TRAILING
} InputState;

static uint64_t hash_key(uint64_t key)
{
    key ^= key >> 30;
    key *= UINT64_C(0xbf58476d1ce4e5b9);
    key ^= key >> 27;
    key *= UINT64_C(0x94d049bb133111eb);
    key ^= key >> 31;
    return key;
}

static size_t memo_index(uint64_t key, size_t capacity)
{
    return (size_t)hash_key(key) & (capacity - 1);
}

static bool memo_init(Memo *memo)
{
    if (memo == NULL) {
        return false;
    }

    memo->entries = NULL;
    memo->capacity = 64;
    memo->size = 0;

    if (memo->capacity > SIZE_MAX / sizeof(*memo->entries)) {
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

    size_t index = memo_index(key, memo->capacity);

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

        size_t index = memo_index(memo->entries[i].key, new_capacity);

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

    size_t index = memo_index(key, memo->capacity);

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

        index = memo_index(key, memo->capacity);

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

static bool calculate_maximum_sum(uint64_t number, Memo *memo, uint64_t *result)
{
    if (memo == NULL || result == NULL) {
        return false;
    }

    if (number < 2) {
        *result = number;
        return true;
    }

    if (memo_get(memo, number, result)) {
        return true;
    }

    uint64_t half;
    uint64_t third;
    uint64_t quarter;
    uint64_t fifth;
    uint64_t sum;

    if (!calculate_maximum_sum(number / 2, memo, &half) ||
        !calculate_maximum_sum(number / 3, memo, &third) ||
        !calculate_maximum_sum(number / 4, memo, &quarter) ||
        !calculate_maximum_sum(number / 5, memo, &fifth) ||
        !checked_add(half, third, &sum) ||
        !checked_add(sum, quarter, &sum) ||
        !checked_add(sum, fifth, &sum)) {
        return false;
    }

    *result = sum > number ? sum : number;

    return memo_put(memo, number, *result);
}

static bool find_maximum_sum(uint64_t number, uint64_t *result)
{
    if (result == NULL) {
        return false;
    }

    Memo memo;

    if (!memo_init(&memo)) {
        return false;
    }

    bool success = calculate_maximum_sum(number, &memo, result);
    memo_destroy(&memo);

    return success;
}

static bool read_input(uint64_t *number)
{
    if (number == NULL) {
        return false;
    }

    unsigned char buffer[256];
    InputState state = INPUT_LEADING;
    uint64_t value = 0;
    size_t count;

    while ((count = fread(buffer, 1, sizeof(buffer), stdin)) != 0) {
        for (size_t i = 0; i < count; ++i) {
            unsigned char ch = buffer[i];
            bool digit = ch >= (unsigned char)'0' &&
                         ch <= (unsigned char)'9';

            switch (state) {
            case INPUT_LEADING:
                if (isspace((int)ch)) {
                    continue;
                }

                if (ch == (unsigned char)'+') {
                    state = INPUT_AFTER_SIGN;
                    continue;
                }

                if (!digit) {
                    return false;
                }

                state = INPUT_DIGITS;
                break;

            case INPUT_AFTER_SIGN:
                if (!digit) {
                    return false;
                }

                state = INPUT_DIGITS;
                break;

            case INPUT_DIGITS:
                if (!digit) {
                    if (!isspace((int)ch)) {
                        return false;
                    }

                    state = INPUT_TRAILING;
                    continue;
                }
                break;

            case INPUT_TRAILING:
                if (!isspace((int)ch)) {
                    return false;
                }

                continue;

            default:
                return false;
            }

            unsigned int digit_value =
                (unsigned int)(ch - (unsigned char)'0');

            if (value > (UINT64_MAX - digit_value) / UINT64_C(10)) {
                return false;
            }

            value = value * UINT64_C(10) + digit_value;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    if (state != INPUT_DIGITS && state != INPUT_TRAILING) {
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
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_maximum_sum(number, &result)) {
        fputs("Unable to calculate result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}