#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    READ_TOKEN_OK = 0,
    READ_TOKEN_EOF = 1,
    READ_TOKEN_ERROR = -1
};

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_token(char **token)
{
    enum { INITIAL_CAPACITY = 32 };
    const size_t maximum_length = 1024U * 1024U;
    const size_t maximum_capacity = maximum_length + 1U;
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    char *buffer = NULL;
    int ch;

    if (token == NULL) {
        return READ_TOKEN_ERROR;
    }

    *token = NULL;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            return ferror(stdin) ? READ_TOKEN_ERROR : READ_TOKEN_EOF;
        }

        if (!is_space(ch)) {
            break;
        }
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_TOKEN_ERROR;
    }

    for (;;) {
        if (length == maximum_length) {
            free(buffer);
            return READ_TOKEN_ERROR;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *resized;

            if (capacity >= maximum_capacity) {
                free(buffer);
                return READ_TOKEN_ERROR;
            }

            if (capacity > maximum_capacity / 2U) {
                new_capacity = maximum_capacity;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required ||
                new_capacity <= capacity ||
                new_capacity > maximum_capacity) {
                free(buffer);
                return READ_TOKEN_ERROR;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return READ_TOKEN_ERROR;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        ch = fgetc(stdin);
        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return READ_TOKEN_ERROR;
            }
            break;
        }

        if (is_space(ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return READ_TOKEN_OK;
}

static int read_size_t_value(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int result = -1;

    if (value == NULL || read_token(&token) != READ_TOKEN_OK) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == 0 &&
        end != token &&
        *end == '\0' &&
        token[0] != '-' &&
        parsed <= SIZE_MAX) {
        *value = (size_t)parsed;
        result = 0;
    }

    free(token);
    return result;
}

static int read_int64_value(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int result = -1;

    if (value == NULL || read_token(&token) != READ_TOKEN_OK) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == 0 &&
        end != token &&
        *end == '\0' &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX) {
        *value = (int64_t)parsed;
        result = 0;
    }

    free(token);
    return result;
}

static int multiply_int64_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (left == 0 || right == 0) {
        *result = 0;
        return 0;
    }

    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return -1;
        }
    } else {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return -1;
        }
    }

    *result = left * right;
    return 0;
}

static int multiply_kth_elements(const int64_t *tuples,
                                 size_t tuple_count,
                                 size_t tuple_size,
                                 size_t k,
                                 int64_t *product)
{
    int64_t result = 1;

    if (tuples == NULL ||
        product == NULL ||
        tuple_count == 0 ||
        tuple_size == 0 ||
        k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        int64_t next_result;
        size_t index = i * tuple_size + k;

        if (multiply_int64_checked(result, tuples[index], &next_result) != 0) {
            return -2;
        }

        result = next_result;
    }

    *product = result;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t tuple_size;
    size_t k;
    size_t element_count;
    int64_t *tuples = NULL;
    int64_t product;
    int operation_result;
    int status = EXIT_FAILURE;

    if (read_size_t_value(&tuple_count) != 0 ||
        read_size_t_value(&tuple_size) != 0 ||
        read_size_t_value(&k) != 0 ||
        tuple_count == 0 ||
        tuple_size == 0 ||
        k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    element_count = tuple_count * tuple_size;

    if (element_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(element_count * sizeof(*tuples));
    if (tuples == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (read_int64_value(&tuples[i]) != 0) {
            fputs("Invalid tuple data\n", stderr);
            goto cleanup;
        }
    }

    operation_result = multiply_kth_elements(
        tuples, tuple_count, tuple_size, k, &product);

    if (operation_result == -1) {
        fputs("Invalid arguments\n", stderr);
        goto cleanup;
    }

    if (operation_result == -2) {
        fputs("Product overflow\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", product) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}