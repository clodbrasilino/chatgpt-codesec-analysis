#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

enum { MAXIMUM_TOKEN_LENGTH = 1024 };

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

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0') {
            if (buffer[i++] == '\n') {
                return 1;
            }
        }
    }

    return !ferror(stdin);
}

static int read_token(char **token)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAXIMUM_TOKEN_LENGTH + 2];
    size_t start = 0;
    size_t end = 0;
    size_t length;
    char *buffer;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    while (input[start] != '\0' &&
           isspace((unsigned char)input[start])) {
        ++start;
    }

    if (input[start] == '\0') {
        return 0;
    }

    end = start;
    while (input[end] != '\0' &&
           !isspace((unsigned char)input[end])) {
        ++end;
    }

    if (input[end] == '\0' && end - start > MAXIMUM_TOKEN_LENGTH) {
        discard_line();
        return 0;
    }

    length = end - start;
    if (length == 0 || length > MAXIMUM_TOKEN_LENGTH) {
        return 0;
    }

    while (input[end] != '\0') {
        if (!isspace((unsigned char)input[end])) {
            return 0;
        }
        ++end;
    }

    buffer = malloc(length + 1);
    if (buffer == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        buffer[i] = input[start + i];
    }
    buffer[length] = '\0';

    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || !isdigit((unsigned char)buffer[0])) {
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
    char *buffer = NULL;
    char *end = NULL;
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

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int product_of_non_repeated(int64_t *array, size_t length,
                                   int64_t *product)
{
    int64_t result = 1;
    int found = 0;
    size_t i = 0;

    if (array == NULL || length == 0 || product == NULL) {
        return 0;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    while (i < length) {
        size_t next = i + 1;

        while (next < length && array[next] == array[i]) {
            ++next;
        }

        if (next == i + 1) {
            if (!multiply_checked(result, array[i], &result)) {
                return 0;
            }
            found = 1;
        }

        i = next;
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

    if (printf("%" PRId64 "\n", product) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}