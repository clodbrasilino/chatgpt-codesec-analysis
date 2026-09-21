#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
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
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            free(buffer);
            return -1;
        }
    } while (isspace((unsigned char)ch));

    for (;;) {
        if (length == capacity - 1) {
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
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
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
    int result = -1;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    result = 0;

cleanup:
    free(token);
    return result;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int result = -1;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    result = 0;

cleanup:
    free(token);
    return result;
}

static int has_extra_input(void)
{
    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }

        if (!isspace((unsigned char)ch)) {
            return 1;
        }
    }
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum;
    int extra_input;

    if (read_size_value(&count) != 0 ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));

    if (tuples == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64_value(&tuples[i].key) != 0 ||
            read_int64_value(&tuples[i].value) != 0) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    extra_input = has_extra_input();

    if (extra_input != 0) {
        fputs(extra_input > 0 ? "Invalid input\n" : "Input error\n", stderr);
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