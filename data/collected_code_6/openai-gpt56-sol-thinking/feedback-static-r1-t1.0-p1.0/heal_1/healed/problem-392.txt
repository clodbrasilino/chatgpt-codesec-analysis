#include <ctype.h>
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

typedef enum {
    INPUT_LEADING,
    INPUT_SIGN,
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

static bool memo_init(Memo *memo)
{
    const size_t initial_capacity = 64;

    if (memo == NULL) {
        return false;
    }

    memo->entries = NULL;
    memo->capacity = 0;
    memo->size = 0;

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
    memo->capacity = 0;
    memo->size = 0;
}

static bool memo_get(const Memo *memo, uint64_t key, uint64_t *value)
{
    size_t index;

    if (memo == NULL || value == NULL || memo->entries == NULL ||
        memo->capacity == 0) {
        return false;
    }

    index = (size_t)hash_key(key) & (memo->capacity - 1);

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
    size_t old_capacity;
    size_t new_capacity;
    MemoEntry *new_entries;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return false;
    }

    if (memo->capacity > SIZE_MAX / 2) {
        return false;
    }

    old_capacity = memo->capacity;
    new_capacity = old_capacity * 2;

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = calloc(new_capacity, sizeof(*new_entries));

    if (new_entries == NULL) {
        return false;
    }

    for (size_t i = 0; i < old_capacity; ++i) {
        if (memo->entries[i].occupied) {
            size_t index =
                (size_t)hash_key(memo->entries[i].key) & (new_capacity - 1);

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
    size_t index;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return false;
    }

    index = (size_t)hash_key(key) & (memo->capacity - 1);

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

        index = (size_t)hash_key(key) & (memo->capacity - 1);

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
    uint64_t half;
    uint64_t third;
    uint64_t quarter;
    uint64_t fifth;
    uint64_t sum;

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
    Memo memo;
    bool success;

    if (result == NULL || !memo_init(&memo)) {
        return false;
    }

    success = calculate_maximum_sum(n, &memo, result);
    memo_destroy(&memo);
    return success;
}

static bool read_input(uint64_t *number)
{
    InputState state = INPUT_LEADING;
    uint64_t value = 0;
    bool has_digit = false;
    int input;

    if (number == NULL) {
        return false;
    }

    while ((input = fgetc(stdin)) != EOF) {
        unsigned char character = (unsigned char)input;

        if (character == '\n') {
            break;
        }

        switch (state) {
        case INPUT_LEADING:
            if (isspace(character)) {
                continue;
            }

            if (character == '+') {
                state = INPUT_SIGN;
                continue;
            }

            if (character == '-') {
                return false;
            }

            if (!isdigit(character)) {
                return false;
            }

            state = INPUT_DIGITS;
            break;

        case INPUT_SIGN:
            if (!isdigit(character)) {
                return false;
            }

            state = INPUT_DIGITS;
            break;

        case INPUT_DIGITS:
            if (!isdigit(character)) {
                if (!isspace(character)) {
                    return false;
                }

                state = INPUT_TRAILING;
                continue;
            }
            break;

        case INPUT_TRAILING:
            if (!isspace(character)) {
                return false;
            }
            continue;
        }

        if (state == INPUT_DIGITS) {
            uint64_t digit = (uint64_t)(character - (unsigned char)'0');

            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                return false;
            }

            value = value * UINT64_C(10) + digit;
            has_digit = true;
        }
    }

    if (ferror(stdin) || !has_digit) {
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