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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= size) {
            do {
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[64];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    if (buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[64];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
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

    if (first_chain_sum == NULL || second_chain_sum == NULL ||
        (count > 0 && tuples == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t first_value;
        int64_t second_value;

        if ((i & 1U) == 0) {
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

    printf("%" PRId64 " %" PRId64 "\n",
           first_chain_sum, second_chain_sum);

    free(tuples);
    return EXIT_SUCCESS;
}