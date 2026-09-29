#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>

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

    if (memo == NULL ||
        initial_capacity > SIZE_MAX / sizeof(*memo->entries)) {
        return false;
    }

    memo->entries = calloc(initial_capacity, sizeof(*memo->entries));
    if (memo->entries == NULL) {
        memo->capacity = 0U;
        memo->size = 0U;
        return false;
    }

    memo->capacity = initial_capacity;
    memo->size = 0U;
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

static bool memo_insert_unchecked(Memo *memo, uint64_t key, uint64_t value)
{
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U) {
        return false;
    }

    index = hash_value(key, memo->capacity);
    start = index;

    do {
        MemoEntry *entry = &memo->entries[index];

        if (!entry->occupied) {
            entry->key = key;
            entry->value = value;
            entry->occupied = true;
            ++memo->size;
            return true;
        }

        if (entry->key == key) {
            entry->value = value;
            return true;
        }

        index = (index + 1U) & (memo->capacity - 1U);
    } while (index != start);

    return false;
}

static bool memo_grow(Memo *memo)
{
    MemoEntry *new_entries;
    MemoEntry *old_entries;
    size_t old_capacity;
    size_t old_size;
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
    old_size = memo->size;

    memo->entries = new_entries;
    memo->capacity = new_capacity;
    memo->size = 0U;

    for (index = 0U; index < old_capacity; ++index) {
        if (old_entries[index].occupied &&
            !memo_insert_unchecked(memo,
                                   old_entries[index].key,
                                   old_entries[index].value)) {
            free(new_entries);
            memo->entries = old_entries;
            memo->capacity = old_capacity;
            memo->size = old_size;
            return false;
        }
    }

    free(old_entries);
    return true;
}

static bool memo_put(Memo *memo, uint64_t key, uint64_t value)
{
    uint64_t existing_value;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U) {
        return false;
    }

    if (memo_get(memo, key, &existing_value)) {
        return memo_insert_unchecked(memo, key, value);
    }

    if (memo->size >= memo->capacity / 2U && !memo_grow(memo)) {
        return false;
    }

    return memo_insert_unchecked(memo, key, value);
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

    for (index = 0U;
         index < sizeof(divisors) / sizeof(divisors[0]);
         ++index) {
        uint64_t term;

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
    uint64_t computed;
    bool success;

    if (result == NULL) {
        return false;
    }

    if (!memo_initialize(&memo)) {
        return false;
    }

    success = maximum_sum_recursive(n, &memo, &computed);
    memo_destroy(&memo);

    if (!success) {
        return false;
    }

    *result = computed;
    return true;
}

static bool is_decimal_digit(unsigned char character)
{
    return character >= (unsigned char)'0' &&
           character <= (unsigned char)'9';
}

static bool is_horizontal_whitespace(unsigned char character)
{
    return character == (unsigned char)' ' ||
           character == (unsigned char)'\t' ||
           character == (unsigned char)'\v' ||
           character == (unsigned char)'\f' ||
           character == (unsigned char)'\r';
}

static bool read_input(uint64_t *value)
{
    enum InputState {
        INPUT_LEADING,
        INPUT_AFTER_PLUS,
        INPUT_DIGITS,
        INPUT_TRAILING
    };

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    enum InputState state = INPUT_LEADING;
    uint64_t parsed = UINT64_C(0);
    bool complete = false;

    if (value == NULL) {
        return false;
    }

    while (!complete) {
        size_t count = fread(buffer, 1U, sizeof(buffer), stdin);
        size_t index;

        for (index = 0U; index < count; ++index) {
            unsigned char current = buffer[index];

            if (current == (unsigned char)'\n') {
                complete = true;
                break;
            }

            switch (state) {
            case INPUT_LEADING:
                if (is_horizontal_whitespace(current)) {
                    continue;
                }

                if (current == (unsigned char)'+') {
                    state = INPUT_AFTER_PLUS;
                    continue;
                }

                if (!is_decimal_digit(current)) {
                    return false;
                }

                state = INPUT_DIGITS;
                break;

            case INPUT_AFTER_PLUS:
                if (!is_decimal_digit(current)) {
                    return false;
                }

                state = INPUT_DIGITS;
                break;

            case INPUT_DIGITS:
                if (is_decimal_digit(current)) {
                    break;
                }

                if (is_horizontal_whitespace(current)) {
                    state = INPUT_TRAILING;
                    continue;
                }

                return false;

            case INPUT_TRAILING:
                if (!is_horizontal_whitespace(current)) {
                    return false;
                }

                continue;
            }

            if (state == INPUT_DIGITS) {
                uint64_t digit =
                    (uint64_t)(current - (unsigned char)'0');

                if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
                    return false;
                }

                parsed = parsed * UINT64_C(10) + digit;
            }
        }

        if (complete) {
            break;
        }

        if (count < sizeof(buffer)) {
            if (ferror(stdin) != 0) {
                return false;
            }

            if (feof(stdin) != 0) {
                break;
            }
        }
    }

    if (state != INPUT_DIGITS && state != INPUT_TRAILING) {
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