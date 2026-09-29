#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    int64_t key;
    int64_t value;
} Tuple;

static int compare_tuples(const void *lhs, const void *rhs)
{
    const Tuple *a = lhs;
    const Tuple *b = rhs;

    return (a->key > b->key) - (a->key < b->key);
}

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return -1;
    }

    *result = a + b;
    return 0;
}

static int maximum_aggregate(Tuple *tuples, size_t count, int64_t *maximum)
{
    int64_t current_sum;
    int64_t maximum_sum;

    if (tuples == NULL || maximum == NULL || count == 0) {
        return -1;
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);

    current_sum = tuples[0].value;
    maximum_sum = current_sum;

    for (size_t i = 1; i < count; ++i) {
        if (tuples[i].key == tuples[i - 1].key) {
            if (add_checked(current_sum, tuples[i].value, &current_sum) != 0) {
                return -1;
            }
        } else {
            if (current_sum > maximum_sum) {
                maximum_sum = current_sum;
            }
            current_sum = tuples[i].value;
        }
    }

    if (current_sum > maximum_sum) {
        maximum_sum = current_sum;
    }

    *maximum = maximum_sum;
    return 0;
}

static int read_token(char **token)
{
    enum { MAX_TOKEN_LENGTH = 128 };
    char buffer[MAX_TOKEN_LENGTH + 1];
    size_t length = 0;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length == MAX_TOKEN_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';

    *token = malloc(length + 1);
    if (*token == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= length; ++i) {
        (*token)[i] = buffer[i];
    }

    return 0;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end;
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

static int read_count(size_t *count)
{
    char *token = NULL;
    char *end;
    uintmax_t parsed;

    if (count == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '-') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX ||
        (size_t)parsed > SIZE_MAX / sizeof(Tuple)) {
        free(token);
        return -1;
    }

    *count = (size_t)parsed;
    free(token);
    return 0;
}

static int input_exhausted(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    size_t count;
    int64_t maximum;
    Tuple *tuples;

    if (read_count(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&tuples[i].key) != 0 ||
            read_int64(&tuples[i].value) != 0) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!input_exhausted()) {
        fputs("Invalid input\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (maximum_aggregate(tuples, count, &maximum) != 0) {
        fputs("Unable to calculate maximum aggregate\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}