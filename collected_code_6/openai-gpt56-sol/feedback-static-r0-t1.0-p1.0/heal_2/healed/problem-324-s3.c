#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int discard_token(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        ch = getchar();
    }

    return ch;
}

static int read_token(char **token)
{
    char *buffer;
    size_t capacity = 32;
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        discard_token(ch);
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == capacity - 1) {
            char *expanded;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                discard_token(ch);
                return 0;
            }

            new_capacity = capacity * 2;
            expanded = realloc(buffer, new_capacity);
            if (expanded == NULL) {
                free(buffer);
                discard_token(ch);
                return 0;
            }

            buffer = expanded;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    valid = token[0] != '-' &&
            errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(token);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    valid = errno != ERANGE &&
            end != token &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(token);
    return valid;
}

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int sum_alternate_chains(const Tuple *tuples, size_t count,
                                int64_t *first_chain_sum,
                                int64_t *second_chain_sum)
{
    int64_t first_sum = 0;
    int64_t second_sum = 0;

    if (first_chain_sum == NULL ||
        second_chain_sum == NULL ||
        (count != 0 && tuples == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t first_value;
        int64_t second_value;

        if ((i & 1U) == 0U) {
            first_value = tuples[i].first;
            second_value = tuples[i].second;
        } else {
            first_value = tuples[i].second;
            second_value = tuples[i].first;
        }

        if (!add_checked(first_sum, first_value, &first_sum) ||
            !add_checked(second_sum, second_value, &second_sum)) {
            return 0;
        }
    }

    *first_chain_sum = first_sum;
    *second_chain_sum = second_sum;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t first_chain_sum;
    int64_t second_chain_sum;

    if (!read_size(&count)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&tuples[i].first) ||
            !read_int64(&tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!sum_alternate_chains(tuples, count,
                              &first_chain_sum, &second_chain_sum)) {
        fputs("Unable to calculate sums\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 " %" PRId64 "\n",
               first_chain_sum, second_chain_sum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}