#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    int ch;
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && is_space(ch));

    if (ch == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !is_space(ch)) {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
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

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int multiply_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (left == 0 || right == 0) {
        *result = 0;
        return 0;
    }

    if (left == -1) {
        if (right == INT64_MIN) {
            return -1;
        }
        *result = -right;
        return 0;
    }

    if (right == -1) {
        if (left == INT64_MIN) {
            return -1;
        }
        *result = -left;
        return 0;
    }

    if (left > 0) {
        if (right > 0) {
            if (left > INT64_MAX / right) {
                return -1;
            }
        } else if (right < INT64_MIN / left) {
            return -1;
        }
    } else {
        /* Possible weaknesses found:
         *  Assuming that condition 'right>0' is not redundant
         */
        if (right > 0) {
            if (left < INT64_MIN / right) {
                return -1;
            }
        /* Possible weaknesses found:
         *  Either the condition 'right>0' is redundant or there is division by zero at line 171. [zerodivcond]
         *  Division by zero
         */
        } else if (left < INT64_MAX / right) {
            return -1;
        }
    }

    *result = left * right;
    return 0;
}

static int product_at_index(const int64_t *tuples, size_t tuple_count,
                            size_t tuple_size, size_t k, int64_t *result)
{
    int64_t product = 1;

    if (tuples == NULL || result == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        return -1;
    }

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
    size_t element_count;
    int64_t *tuples;
    int64_t product;
    int status;

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

    element_count = tuple_count * tuple_size;

    if (element_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(element_count * sizeof(*tuples));
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

    status = product_at_index(tuples, tuple_count, tuple_size, k, &product);
    free(tuples);

    if (status == -2) {
        fputs("Product overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", product);
    return EXIT_SUCCESS;
}