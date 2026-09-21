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

static int is_input_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int discard_token_tail(int ch)
{
    while (ch != EOF && !is_input_space(ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_token(char **token)
{
    enum { MAXIMUM_LENGTH = 1024 };
    char *buffer;
    size_t length = 0;
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
    } while (is_input_space(ch));

    buffer = malloc((size_t)MAXIMUM_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !is_input_space(ch)) {
        if (length == (size_t)MAXIMUM_LENGTH) {
            int status = discard_token_tail(ch);
            free(buffer);
            return status == 0 ? -1 : status;
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
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return -1;
    }

    *value = (size_t)parsed;
    free(token);
    return 0;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return -1;
    }

    *value = (int64_t)parsed;
    free(token);
    return 0;
}

static int checked_add(uint64_t *total, uint64_t value)
{
    if (total == NULL || value > UINT64_MAX - *total) {
        return -1;
    }

    *total += value;
    return 0;
}

static int checked_multiply(uint64_t left, uint64_t right, uint64_t *result)
{
    if (result == NULL || (right != 0 && left > UINT64_MAX / right)) {
        return -1;
    }

    *result = left * right;
    return 0;
}

static size_t lower_bound_tuple(const Tuple *tuples, size_t count,
                                const Tuple *target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (compare_tuples(&tuples[middle], target) < 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static size_t upper_bound_tuple(const Tuple *tuples, size_t count,
                                const Tuple *target)
{
    size_t low = 0;
    size_t high = count;

    while (low < high) {
        size_t middle = low + (high - low) / 2;

        if (compare_tuples(&tuples[middle], target) <= 0) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

    return low;
}

static int count_bidirectional_pairs(Tuple *tuples, size_t count,
                                     uint64_t *result)
{
    uint64_t total = 0;
    size_t index = 0;

    if (result == NULL || (count != 0 && tuples == NULL)) {
        return -1;
    }

#if SIZE_MAX > UINT64_MAX
    if (count > UINT64_MAX) {
        return -1;
    }
#endif

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

        frequency = (uint64_t)(next - index);

        if (tuples[index].first == tuples[index].second) {
            uint64_t product;

            if (checked_multiply(frequency, frequency - 1, &product) != 0 ||
                checked_add(&total, product / 2) != 0) {
                return -1;
            }
        } else if (tuples[index].first < tuples[index].second) {
            Tuple reverse;
            size_t first;
            size_t last;
            uint64_t reverse_frequency;
            uint64_t product;

            reverse.first = tuples[index].second;
            reverse.second = tuples[index].first;

            first = lower_bound_tuple(tuples, count, &reverse);
            last = upper_bound_tuple(tuples, count, &reverse);
            reverse_frequency = (uint64_t)(last - first);

            if (checked_multiply(frequency, reverse_frequency, &product) != 0 ||
                checked_add(&total, product) != 0) {
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