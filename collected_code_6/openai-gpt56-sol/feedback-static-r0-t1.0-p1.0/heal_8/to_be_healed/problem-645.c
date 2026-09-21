#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    if (line == NULL || capacity == NULL ||
        (*line == NULL && *capacity != 0)) {
        return -1;
    }

    size_t length = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            return -1;
        }

        size_t required = length + 2;

        if (required > *capacity) {
            size_t new_capacity = *capacity == 0 ? 64 : *capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_line = realloc(*line, new_capacity);

            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (*capacity < length + 1) {
        char *new_line = realloc(*line, length + 1);

        if (new_line == NULL) {
            return -1;
        }

        *line = new_line;
        *capacity = length + 1;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *token = NULL;
    size_t capacity = 0;

    if (read_line(&token, &capacity) != 0 ||
        token[0] == '\0' || token[0] == '-') {
        free(token);
        return -1;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(token);
        return -1;
    }

    *value = (size_t)parsed;
    free(token);
    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *token = NULL;
    size_t capacity = 0;

    if (read_line(&token, &capacity) != 0 || token[0] == '\0') {
        free(token);
        return -1;
    }

    char *end = NULL;
    errno = 0;
    intmax_t parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return -1;
    }

    *value = (int64_t)parsed;
    free(token);
    return 0;
}

static int multiply_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((left == -1 && right == INT64_MIN) ||
        (right == -1 && left == INT64_MIN)) {
        return -1;
    }

    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return -1;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return -1;
        }
    }

    *result = left * right;
    return 0;
}

static int product_at_index(const int64_t *tuples, size_t tuple_count,
                            size_t tuple_size, size_t k, int64_t *result)
{
    if (tuples == NULL || result == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        return -1;
    }

    int64_t product = 1;

    for (size_t i = 0; i < tuple_count; ++i) {
        int64_t next_product;
        size_t index = i * tuple_size + k;

        if (multiply_int64(product, tuples[index], &next_product) != 0) {
            return -2;
        }

        product = next_product;
    }

    *result = product;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t tuple_size;
    size_t k;

    if (read_size(&tuple_count) != 0 ||
        read_size(&tuple_size) != 0 ||
        read_size(&k) != 0 ||
        tuple_count == 0 ||
        tuple_size == 0 ||
        k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = tuple_count * tuple_size;

    if (element_count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *tuples = malloc(element_count * sizeof(*tuples));

    if (tuples == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (read_int64(&tuples[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t product;
    int status = product_at_index(
        tuples, tuple_count, tuple_size, k, &product
    );

    free(tuples);

    if (status == -2) {
        fputs("Product overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}