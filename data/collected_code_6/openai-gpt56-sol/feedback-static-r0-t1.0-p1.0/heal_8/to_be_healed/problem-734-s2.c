#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int is_horizontal_space(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\v' || ch == '\f';
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (is_horizontal_space(*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    while (is_horizontal_space(*end)) {
        ++end;
    }

    if (*end != '\0') {
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
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (is_horizontal_space(*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (is_horizontal_space(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int checked_mul_int64(int64_t left, int64_t right, int64_t *result)
{
    uint64_t left_magnitude;
    uint64_t right_magnitude;
    uint64_t limit;
    uint64_t product;
    int negative;

    if (result == NULL) {
        return 0;
    }

    negative = (left < 0) != (right < 0);
    left_magnitude = left < 0
        ? (uint64_t)(-(left + 1)) + UINT64_C(1)
        : (uint64_t)left;
    right_magnitude = right < 0
        ? (uint64_t)(-(right + 1)) + UINT64_C(1)
        : (uint64_t)right;

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    if (left_magnitude != 0 && right_magnitude > limit / left_magnitude) {
        return 0;
    }

    product = left_magnitude * right_magnitude;

    if (negative) {
        if (product == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)product;
        }
    } else {
        *result = (int64_t)product;
    }

    return 1;
}

static int sum_of_subarray_products(const int64_t *array, size_t length,
                                    int64_t *result)
{
    int64_t ending_sum = 0;
    int64_t total_sum = 0;

    if (array == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int64_t product_sum;
        int64_t new_ending_sum;
        int64_t new_total_sum;

        if (!checked_mul_int64(array[i], ending_sum, &product_sum) ||
            !checked_add_int64(array[i], product_sum, &new_ending_sum) ||
            !checked_add_int64(total_sum, new_ending_sum, &new_total_sum)) {
            return 0;
        }

        ending_sum = new_ending_sum;
        total_sum = new_total_sum;
    }

    *result = total_sum;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t result;

    if (!read_size(&length) || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!sum_of_subarray_products(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}