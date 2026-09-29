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

    if (a->key < b->key) {
        return -1;
    }
    if (a->key > b->key) {
        return 1;
    }
    return 0;
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

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;
    int too_long = 0;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = 1;
        }
        ch = getchar();
    }

    if (too_long) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

static int read_int64(int64_t *value)
{
    enum { TOKEN_CAPACITY = 129 };
    char token[TOKEN_CAPACITY];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(token, sizeof(token)) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_count(size_t *count)
{
    enum { TOKEN_CAPACITY = 129 };
    char token[TOKEN_CAPACITY];
    char *end;
    uintmax_t parsed;

    if (count == NULL || read_token(token, sizeof(token)) != 0) {
        return -1;
    }

    if (token[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX ||
        (size_t)parsed > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }

    *count = (size_t)parsed;
    return 0;
}

static int input_exhausted(void)
{
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return 1;
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