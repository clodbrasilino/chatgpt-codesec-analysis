#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int multiply_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return 0;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int c;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int product_of_non_repeated(const int64_t array[], size_t length,
                                   int64_t *product)
{
    int64_t result = 1;
    int found = 0;

    if ((array == NULL && length != 0) || product == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int repeated = 0;

        for (size_t j = 0; j < length; ++j) {
            if (i != j && array[i] == array[j]) {
                repeated = 1;
                break;
            }
        }

        if (!repeated) {
            if (!multiply_checked(result, array[i], &result)) {
                return 0;
            }
            found = 1;
        }
    }

    if (!found) {
        return 0;
    }

    *product = result;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t product;

    if (!read_size(&length)) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        fputs("The array must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Unable to allocate array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!product_of_non_repeated(array, length, &product)) {
        fputs("No unique elements or product overflow.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", product);
    free(array);
    return EXIT_SUCCESS;
}