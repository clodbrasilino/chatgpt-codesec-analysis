#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

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

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool ended;
} InputReader;

typedef enum {
    INPUT_OK,
    INPUT_END,
    INPUT_ERROR
} InputStatus;

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
    size_t start;

    if (memo == NULL || memo->entries == NULL ||
        memo->capacity == 0 || value == NULL) {
        return false;
    }

    index = hash_uint64(key) & (memo->capacity - 1);
    start = index;

    do {
        const MemoEntry *entry = &memo->entries[index];

        if (!entry->used) {
            return false;
        }

        if (entry->key == key) {
            *value = entry->value;
            return true;
        }

        index = (index + 1) & (memo->capacity - 1);
    } while (index != start);

    return false;
}

static bool memo_resize(Memo *memo)
{
    MemoEntry *new_entries;
    size_t old_capacity;
    size_t new_capacity;
    size_t i;

    if (memo == NULL || memo->entries == NULL ||
        memo->capacity == 0 || memo->capacity > SIZE_MAX / 2) {
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

    for (i = 0; i < old_capacity; ++i) {
        size_t index;

        if (!memo->entries[i].used) {
            continue;
        }

        index = hash_uint64(memo->entries[i].key) & (new_capacity - 1);

        while (new_entries[index].used) {
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
    size_t index;
    size_t start;

    if (memo == NULL || memo->entries == NULL || memo->capacity == 0) {
        return false;
    }

    index = hash_uint64(key) & (memo->capacity - 1);
    start = index;

    do {
        if (!memo->entries[index].used) {
            break;
        }

        if (memo->entries[index].key == key) {
            memo->entries[index].value = value;
            return true;
        }

        index = (index + 1) & (memo->capacity - 1);
    } while (index != start);

    if (memo->size >= memo->capacity - memo->capacity / 4) {
        if (!memo_resize(memo)) {
            return false;
        }

        index = hash_uint64(key) & (memo->capacity - 1);

        while (memo->entries[index].used) {
            index = (index + 1) & (memo->capacity - 1);
        }
    } else if (memo->entries[index].used) {
        return false;
    }

    memo->entries[index].key = key;
    memo->entries[index].value = value;
    memo->entries[index].used = true;
    ++memo->size;

    return true;
}

static bool compute_max_sum(uint64_t n, Memo *memo, uint64_t *result)
{
    static const uint64_t divisors[] = {
        UINT64_C(2),
        UINT64_C(3),
        UINT64_C(4),
        UINT64_C(5)
    };
    uint64_t cached;
    uint64_t sum = 0;
    size_t i;

    if (memo == NULL || result == NULL) {
        return false;
    }

    if (n <= UINT64_C(5)) {
        *result = n;
        return true;
    }

    if (memo_get(memo, n, &cached)) {
        *result = cached;
        return true;
    }

    for (i = 0; i < sizeof(divisors) / sizeof(divisors[0]); ++i) {
        uint64_t part;

        if (!compute_max_sum(n / divisors[i], memo, &part)) {
            return false;
        }

        if (part > UINT64_MAX - sum) {
            return false;
        }

        sum += part;
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

static bool max_sum(uint64_t n, uint64_t *result)
{
    Memo memo;
    bool success;

    if (result == NULL) {
        return false;
    }

    if (n <= UINT64_C(5)) {
        *result = n;
        return true;
    }

    if (!memo_init(&memo)) {
        return false;
    }

    success = compute_max_sum(n, &memo, result);
    memo_destroy(&memo);

    return success;
}

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->ended = false;

    return true;
}

static InputStatus input_reader_get(InputReader *reader, int *ch)
{
    if (reader == NULL || reader->stream == NULL || ch == NULL) {
        return INPUT_ERROR;
    }

    if (reader->position == reader->length) {
        size_t count;

        if (reader->ended) {
            return INPUT_END;
        }

        count = fread(reader->buffer, 1, sizeof(reader->buffer),
                      reader->stream);

        if (count == 0) {
            if (ferror(reader->stream)) {
                return INPUT_ERROR;
            }

            reader->ended = true;
            return INPUT_END;
        }

        reader->position = 0;
        reader->length = count;
    }

    *ch = (int)reader->buffer[reader->position];
    ++reader->position;

    return INPUT_OK;
}

static bool is_whitespace(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static ReadStatus read_uint64(InputReader *reader, uint64_t *value)
{
    uint64_t parsed = 0;
    InputStatus input_status;
    bool invalid = false;
    int ch;

    if (reader == NULL || value == NULL) {
        return READ_ERROR;
    }

    do {
        input_status = input_reader_get(reader, &ch);

        if (input_status == INPUT_ERROR) {
            return READ_ERROR;
        }

        if (input_status == INPUT_END) {
            return READ_END;
        }
    } while (is_whitespace(ch));

    for (;;) {
        if (ch < '0' || ch > '9') {
            invalid = true;
        } else if (!invalid) {
            uint64_t digit = (uint64_t)(ch - '0');

            if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
                invalid = true;
            } else {
                parsed = parsed * UINT64_C(10) + digit;
            }
        }

        input_status = input_reader_get(reader, &ch);

        if (input_status == INPUT_ERROR) {
            return READ_ERROR;
        }

        if (input_status == INPUT_END || is_whitespace(ch)) {
            break;
        }
    }

    if (invalid) {
        return READ_INVALID;
    }

    *value = parsed;
    return READ_OK;
}

int main(void)
{
    InputReader reader;
    uint64_t n;
    uint64_t result;

    if (!input_reader_init(&reader, stdin)) {
        return EXIT_FAILURE;
    }

    for (;;) {
        ReadStatus status = read_uint64(&reader, &n);

        if (status == READ_END) {
            break;
        }

        if (status != READ_OK) {
            return EXIT_FAILURE;
        }

        if (!max_sum(n, &result)) {
            return EXIT_FAILURE;
        }

        if (printf("%" PRIu64 "\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}