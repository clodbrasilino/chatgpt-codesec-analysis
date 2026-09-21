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
    if (memo == NULL || capacity == 0U ||
        capacity > SIZE_MAX / sizeof(*memo->entries)) {
        return 0;
    }

    memo->entries = calloc(capacity, sizeof(*memo->entries));
    if (memo->entries == NULL) {
        memo->capacity = 0U;
        memo->size = 0U;
        return 0;
    }

    memo->capacity = capacity;
    memo->size = 0U;
    return 1;
}

static void memo_destroy(Memo *memo)
{
    if (memo != NULL) {
        free(memo->entries);
        memo->entries = NULL;
        memo->capacity = 0U;
        memo->size = 0U;
    }
}

static int memo_insert_raw(Memo *memo, uint64_t key, uint64_t value)
{
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U) {
        return 0;
    }

    index = (size_t)(hash_u64(key) % memo->capacity);
    start = index;

    do {
        Entry *entry = &memo->entries[index];

        if (entry->occupied == 0U) {
            entry->key = key;
            entry->value = value;
            entry->occupied = 1U;
            ++memo->size;
            return 1;
        }

        if (entry->key == key) {
            entry->value = value;
            return 1;
        }

        index = index + 1U;
        if (index == memo->capacity) {
            index = 0U;
        }
    } while (index != start);

    return 0;
}

static int memo_resize(Memo *memo)
{
    Memo resized = { NULL, 0U, 0U };
    size_t new_capacity;
    size_t i;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U ||
        memo->capacity > SIZE_MAX / 2U) {
        return 0;
    }

    new_capacity = memo->capacity * 2U;

    if (new_capacity > SIZE_MAX / sizeof(*memo->entries) ||
        !memo_init(&resized, new_capacity)) {
        return 0;
    }

    for (i = 0U; i < memo->capacity; ++i) {
        if (memo->entries[i].occupied != 0U &&
            !memo_insert_raw(&resized, memo->entries[i].key,
                             memo->entries[i].value)) {
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

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U ||
        value == NULL) {
        return 0;
    }

    index = (size_t)(hash_u64(key) % memo->capacity);
    start = index;

    do {
        const Entry *entry = &memo->entries[index];

        if (entry->occupied == 0U) {
            return 0;
        }

        if (entry->key == key) {
            *value = entry->value;
            return 1;
        }

        index = index + 1U;
        if (index == memo->capacity) {
            index = 0U;
        }
    } while (index != start);

    return 0;
}

static int memo_put(Memo *memo, uint64_t key, uint64_t value)
{
    uint64_t existing;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0U) {
        return 0;
    }

    if (memo_get(memo, key, &existing)) {
        return memo_insert_raw(memo, key, value);
    }

    if (memo->size >= memo->capacity / 2U && !memo_resize(memo)) {
        return 0;
    }

    return memo_insert_raw(memo, key, value);
}

static int checked_add(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || right > UINT64_MAX - left) {
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

    if (n == 0U) {
        *result = 0U;
        return 1;
    }

    if (memo_get(memo, n, result)) {
        return 1;
    }

    if (!maximum_sum(n / 2U, memo, &a) ||
        !maximum_sum(n / 3U, memo, &b) ||
        !maximum_sum(n / 4U, memo, &c) ||
        !maximum_sum(n / 5U, memo, &d) ||
        !checked_add(a, b, &sum) ||
        !checked_add(sum, c, &sum) ||
        !checked_add(sum, d, &sum)) {
        return 0;
    }

    *result = sum > n ? sum : n;
    return memo_put(memo, n, *result);
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 64U;
    size_t length = 0U;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (fgets(buffer + length, (int)(capacity - length), stdin) == NULL) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return 0;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        if (length > SIZE_MAX - 2U) {
            free(buffer);
            return 0;
        }

        if (length + 2U > capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
        buffer[length] = '\0';
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    Memo memo = { NULL, 0U, 0U };
    uint64_t n;
    uint64_t result;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!memo_init(&memo, 64U)) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!maximum_sum(n, &memo, &result)) {
        memo_destroy(&memo);
        fputs("Computation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        memo_destroy(&memo);
        return EXIT_FAILURE;
    }

    memo_destroy(&memo);
    return EXIT_SUCCESS;
}