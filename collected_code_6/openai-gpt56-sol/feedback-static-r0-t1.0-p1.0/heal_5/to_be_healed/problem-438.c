#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;

    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }
    return 0;
}

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (is_space(ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (ch == EOF || is_space(ch)) {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size_value(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64_value(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int size_to_uint64(size_t value, uint64_t *result)
{
#if SIZE_MAX > UINT64_MAX
    if (value > UINT64_MAX) {
        return -1;
    }
#endif

    *result = (uint64_t)value;
    return 0;
}

static int checked_add(uint64_t *total, uint64_t value)
{
    if (value > UINT64_MAX - *total) {
        return -1;
    }

    *total += value;
    return 0;
}

static int checked_multiply(uint64_t left, uint64_t right, uint64_t *result)
{
    if (right != 0 && left > UINT64_MAX / right) {
        return -1;
    }

    *result = left * right;
    return 0;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count,
                                     uint64_t *result)
{
    uint64_t total = 0;
    size_t index = 0;

    if (result == NULL || (count != 0 && tuples == NULL)) {
        return -1;
    }

    if (count > 1) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    while (index < count) {
        size_t next = index + 1;
        uint64_t frequency;

        while (next < count &&
               compare_tuples(&tuples[index], &tuples[next]) == 0) {
            ++next;
        }

        /* Possible weaknesses found:
         *  Condition 'size_to_uint64(next-index,&frequency)!=0' is always false [knownConditionTrueFalse]
         *  Condition 'size_to_uint64(next-index,&frequency)!=0' is always false
         *  Calling function 'size_to_uint64' returns 0
         */
        if (size_to_uint64(next - index, &frequency) != 0) {
            return -1;
        }

        if (tuples[index].first == tuples[index].second) {
            uint64_t addend;
            uint64_t left = frequency / 2;
            uint64_t right = frequency - 1;

            if ((frequency & UINT64_C(1)) != 0) {
                left = frequency;
                right = (frequency - 1) / 2;
            }

            if (checked_multiply(left, right, &addend) != 0 ||
                checked_add(&total, addend) != 0) {
                return -1;
            }
        } else if (tuples[index].first < tuples[index].second) {
            Tuple reverse = {
                tuples[index].second,
                tuples[index].first
            };
            size_t low = 0;
            size_t high = count;
            size_t first;
            size_t last;
            uint64_t reverse_frequency;
            uint64_t addend;

            while (low < high) {
                size_t middle = low + (high - low) / 2;

                if (compare_tuples(&tuples[middle], &reverse) < 0) {
                    low = middle + 1;
                } else {
                    high = middle;
                }
            }
            first = low;

            low = first;
            high = count;

            while (low < high) {
                size_t middle = low + (high - low) / 2;

                if (compare_tuples(&tuples[middle], &reverse) <= 0) {
                    low = middle + 1;
                } else {
                    high = middle;
                }
            }
            last = low;

            /* Possible weaknesses found:
             *  Condition 'size_to_uint64(last-first,&reverse_frequency)!=0' is always false
             *  Condition 'size_to_uint64(last-first,&reverse_frequency)!=0' is always false [knownConditionTrueFalse]
             *  Calling function 'size_to_uint64' returns 0
             */
            if (size_to_uint64(last - first, &reverse_frequency) != 0 ||
                checked_multiply(frequency, reverse_frequency, &addend) != 0 ||
                checked_add(&total, addend) != 0) {
                return -1;
            }
        }

        index = next;
    }

    *result = total;
    return 0;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t result;

    if (read_size_value(&count) != 0) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Tuple count is too large\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64_value(&tuples[i].first) != 0 ||
            read_int64_value(&tuples[i].second) != 0) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (count_bidirectional_pairs(tuples, count, &result) != 0) {
        fprintf(stderr, "Unable to count pairs\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fprintf(stderr, "Output failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}